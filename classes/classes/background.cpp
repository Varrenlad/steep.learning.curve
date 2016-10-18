#include "background.h"
#include "commondata.h"

Background::Background(HDC &hdc, HWND hwnd) : Drawable(2, hdc)
{
	hwnd_i = hwnd;
};

Background::~Background() {
	DeleteBrush(baseBrush);
}

void Background::Draw() {
	Update(hwnd_i);
	Drawable::baseBrush = CreateSolidBrush(bgc);
	SelectBrush(hdc, Drawable::baseBrush);
	Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
	DeleteBrush(baseBrush);
}

void Background::Setter(std::ifstream &st) {
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_BG_VL_WRONG;
	else bgc = RGB(r, g, b);
}

void Background::Getter(std::ofstream &st) {
	try {
		st << (int)GetRValue(bgc) << ' ' << (int)GetGValue(bgc)
			<< ' ' << (int)GetBValue(bgc) << '\n' << '\n';
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