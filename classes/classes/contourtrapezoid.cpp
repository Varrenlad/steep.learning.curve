#include "contourtrapezoid.h"
#include "commondata.h"

ContourTrapezoid::ContourTrapezoid(HDC &hdc, HWND hwnd) : Drawable(4, hdc) {
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
	MoveToEx(hdc, points[0].x, points[0].y, NULL);
	LineTo(hdc, points[1].x, points[1].y);
	LineTo(hdc, points[2].x, points[2].y);
	LineTo(hdc, points[3].x, points[3].y);
	LineTo(hdc, points[0].x, points[0].y);
	DeletePen(basePen);
}

void ContourTrapezoid::Setter(std::istream &st) { ///Four points, no less
	int i;
	st >> pen_type >> pen_width;
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_C_TR_VL_WRONG;
	else pen = RGB(r, g, b);
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

void ContourTrapezoid::Getter(std::ostream &st) {
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