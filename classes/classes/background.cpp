#include "background.h"

Background::Background(HDC &hdc, HWND hwnd) : Drawable(2, hdc) {
	brush = RGB(0,0,0);
	baseBrush = CreateSolidBrush(brush);
	hwnd_i = hwnd;
};

Background::~Background() {
	DeleteBrush(baseBrush);
}

void Background::Draw() {
	Update(hwnd_i);
	baseBrush = CreateSolidBrush(brush);
	SelectBrush(hdc, baseBrush);
	Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
	DeleteBrush(baseBrush);
}

void Background::Setter(std::istream &st) {
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_BG_VL_WRONG;
	else brush = RGB(r, g, b);
	st.get();
}

void Background::Getter(std::ostream &st) {
	try {
		st << (int)GetRValue(brush) << ' ' << (int)GetGValue(brush)
			<< ' ' << (int)GetBValue(brush) << '\n';
	}
	catch (int) {
		throw EXC_WR_FAIL;
	}
}

void Background::Update(HWND hwnd) {
	GetClientRect(hwnd, &rt);
	points[0].x = rt.left - 10;
	points[0].y = rt.top - 10;
	points[1].x = rt.right + 10;
	points[1].y = rt.bottom + 10;
}

bool Background::PointInside(POINT p) {
	return (p.x > points[0].x && p.x < points[1].x &&
			p.y > points[0].y && p.y < points[1].y);
}

bool Background::HasColour(COLORREF c) {
	return (brush == c);
}

const COLORREF Background::GetColour() const {
	return brush;
}

char Background::GetType() const {
	return 'b';
}

void Background::Move(int x, int y) {
	throw EXC_BG_VL_WRONG; //no sence in moving background, though we need it for the sake of architecture
}