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
	int red, green, blue;
	st >> red >> green >> blue;
	if (red < 0 || red > 255 ||
		green < 0 || green > 255 ||
		blue < 0 || blue > 255)
		throw EXCEPTION_WRONG_VALUES;
	else bgc = RGB(red, green, blue);
}

void Background::Getter(std::ofstream &st) {
	try {
		st << (int)GetRValue(bgc) << ' ' << (int)GetGValue(bgc)
			<< ' ' << (int)GetBValue(bgc) << '\n' << '\n';
	}
	catch (void) {
		throw EXCEPTION_WRONG_VALUES;
	}
}

void Background::Update(HWND hwnd) {
	GetClientRect(hwnd, &rt);
	points[0].x = rt.left - 10;
	points[0].y = rt.top - 10;
	points[1].x = rt.right + 10;
	points[1].y = rt.bottom + 10;
}