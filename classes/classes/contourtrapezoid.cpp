#include "contourtrapezoid.h"
#include "commondata.h"

ContourTrapezoid::ContourTrapezoid(HDC &hdc, HWND hwnd) : Drawable(5, hdc) {
	hwnd_i = hwnd;
};

ContourTrapezoid::~ContourTrapezoid() {
	DeletePen(basePen);
}

void ContourTrapezoid::Draw() {
	try {
		BorderCheck();
	}
	catch (int e) {
		if (e == EXC_OOB)
			throw e;
	}
	SelectPen(hdc, basePen);
	Polyline(hdc, points, 5);
	DeletePen(basePen);
}

void ContourTrapezoid::Setter(std::ifstream &st) { ///Four points, no less
	int i;
	st >> pen_type >> pen_width;
	int red, green, blue;
	st >> red >> green >> blue;
	if (red < 0 || red > 255 ||
		green < 0 || green > 255 ||
		blue < 0 || blue > 255)
		throw EXC_C_TR_VL_WRONG;
	else pen = RGB(red, green, blue);
	for (i = 0; i < count_of_p - 1; ++i) {
		st >> points[i].x >> points[i].y;
	}
	if (this->points[2].y - this->points[3].y != 0 ||
		this->points[1].y - this->points[0].y)
		if ((this->points[2].x - this->points[3].x) /
			(this->points[2].y - this->points[3].y) !=
			(this->points[0].x - this->points[1].x) /
			(this->points[0].y - this->points[1].y))
			throw EXC_C_TR_VL_WRONG;
	points[4] = points[0];
	basePen = CreatePen(pen_type, pen_width, pen);
}

void ContourTrapezoid::Getter(std::ofstream &st) {
	int i;
	try {
		st << pen_type << ' ' << pen_width << '\n';
		st.flush();
		st << (int)GetRValue(pen) << ' ' << (int)GetGValue(pen) << ' '
			<< (int)GetBValue(pen) << '\n';
		st.flush();
		for (i = 0; i < count_of_p - 1; ++i) {
			st << points[i].x << ' ' << points[i].y << '\n';
			st.flush();
		}
	}
	catch (int e) {
		throw e;
	}
}

void ContourTrapezoid::BorderCheck() {
	RECT rt;
	int i;
	GetClientRect(hwnd_i, &rt);
	for (i = 0; i < count_of_p; ++i) {
		if (points[i].x < 0 || points[i].x > rt.right ||
			points[i].y < 0 || points[i].y > rt.bottom)
			throw EXC_OOB;
	}
}