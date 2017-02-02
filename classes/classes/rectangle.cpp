#include "rectangle.h"

_Rectangle::_Rectangle(HDC &hdc_g, HWND &hwnd_g) : Drawable(2, hdc) {
	hdc = hdc_g;
	hwnd = hwnd_g;
	points[0].x = 0;
	points[0].y = 0;
	points[1].x = 10;
	points[1].y = 10;
	basePen = CreatePen(1, 5, RGB(255, 255, 255));
	baseBrush = CreateSolidBrush(RGB(0, 0, 0));
}

_Rectangle::~_Rectangle() {

}

void _Rectangle::Draw() {
	SelectPen(hdc, basePen);
	SelectBrush(hdc, baseBrush);
	Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
}

void _Rectangle::Save(std::ostream &st) {
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WRITE_FAIL;
	st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
	this->SaveC(pen, st);
	this->SaveC(brush, st);
	this->SaveP(st);
}

char _Rectangle::GetType() const {
	return 'r';
}

void _Rectangle::Load(std::istream &st) {
	st >> pen_type >> pen_width >> brush_type;
	if ((this->LoadC(&pen, st)) ||
		(this->LoadC(&brush, st)))
		throw EXC_READ_FAIL;
	try {
		this->LoadP(st);
	}
	catch (int e) {
		throw;
	}
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
}

void _Rectangle::SaveC(COLORREF &cl, std::ostream &st) {
	st << (int)GetRValue(cl) << ' ' << (int)GetGValue(cl) << ' '
		<< (int)GetBValue(cl) << '\n';
	st.flush();
}

void _Rectangle::SaveP(std::ostream &st) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st << points[i].x << ' ' << points[i].y << '\n';
	}
	st.flush();
}

void _Rectangle::LoadP(std::istream &st) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st >> (points)[i].x >> (points)[i].y;
	}
	st.get();
	//check data
	if (points[0].x > points[1].x ||
		points[0].y > points[1].y)
		throw EXC_WRONG_POINTS_R;
	if (std::abs(points[0].x - points[1].x) !=
		std::abs(points[0].y - points[1].y))
		throw EXC_WRONG_POINTS_R;
}

bool _Rectangle::LoadC(COLORREF *cl, std::istream &st) {
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		return true;
	*cl = RGB(r, g, b);
	return false;
}

void _Rectangle::CLoad(std::istream &st) {
	char c;
	//load types
	st >> pen_type >> pen_width >> brush_type;
	//load colours
	do {
		this->LoadC(&pen, st);
		this->LoadC(&brush, st);
		//show colours
		TextOutA(hdc, 0, 0, "Are the colours correct? Y\n; Pen, brush", 40);
		SelectBrush(hdc, pen);
		Rectangle(hdc, 50, 20, 60, 30);
		SelectBrush(hdc, brush);
		Rectangle(hdc, 60, 20, 70, 30); c;
		std::cin >> c;
		if (c != 'n' || c != 'N')
			c = 0;
	} while (c);
	//for each load and draw line
	for (size_t i = 0; i < count_of_p; ++i) {
		st >> (points)[i].x >> (points)[i].y;
		for (size_t i = 0; i < count_of_p; ++i) {
			Ellipse(hdc, points[i].x - pen_width, points[i].y - pen_width,
				points[i].x + pen_width, points[i].y + pen_width);
		}
		TextOutA(hdc, 0, 0, "Is the position correct? Y\n", 30);
		std::cin >> c;
		if (c == 'n' || c == 'N')
			--i;
		InvalidateRect(NULL, NULL, TRUE);
		Sleep(50);
	}
	//data verification
	if (points[0].x > points[1].x ||
		points[0].y > points[1].y)
		throw EXC_WRONG_POINTS_R;
	if (std::abs(points[0].x - points[1].x) !=
		std::abs(points[0].y - points[1].y))
		throw EXC_WRONG_POINTS_R;
	//remove all our helpers
	InvalidateRect(NULL, NULL, TRUE);
	Sleep(50);
}