#include "filledtrapezoid.h"
#include "commonfunc.h"
#include "commondata.h"

FilledTrapezoid::FilledTrapezoid(HDC &hdc, HWND hwnd) : ContourTrapezoid(hdc, hwnd) {
};

FilledTrapezoid::~FilledTrapezoid() {
	DeletePen(basePen);
	DeleteBrush(baseBrush);
}

void FilledTrapezoid::Draw() {
	try {
		BorderCheck();
	}
	catch (int e) {
		if (e == EXC_OOB)
			throw e;
	}
	SelectPen(hdc, basePen);
	SelectBrush(hdc, baseBrush);
	Polygon(hdc, points, 4);
}

void FilledTrapezoid::Setter(std::istream &st) { ///Four points, no less
	int i, r, g, b;
	st >> pen_type >> pen_width >> brush_type;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_F_TR_VL_WRONG;
	pen = RGB(r, g, b);
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_F_TR_VL_WRONG;
	brush = RGB(r, g, b);
	for (i = 0; i < count_of_p; ++i) {
		st >> points[i].x >> points[i].y;
	}
	if (this->points[2].y - this->points[3].y != 0 ||
		this->points[1].y - this->points[0].y)
		if ((this->points[2].x - this->points[3].x) /
			(this->points[2].y - this->points[3].y) !=
			(this->points[0].x - this->points[1].x) /
			(this->points[0].y - this->points[1].y))
			throw EXC_F_TR_VL_WRONG;

	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = CreateBrush(brush, brush_type);
}

void FilledTrapezoid::Getter(std::ostream &st) {
	int i;
	try {
		st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
		st << (int)GetRValue(pen) << ' ' << (int)GetGValue(pen) << ' '
			<< (int)GetBValue(pen) << '\n';
		st << (int)GetRValue(brush) << ' ' << (int)GetGValue(brush) << ' '
			<< (int)GetBValue(brush) << '\n';
		for (i = 0; i < count_of_p; ++i) {
			st << points[i].x << ' ' << points[i].y << '\n';
		}
		st << '\n';
	}
	catch (int e) {
		throw e;
	}
}

void FilledTrapezoid::Draw(FilledTrapezoid &ft) {
	int i;
	for (i = 0; i < count_of_p; ++i) {
		if ((GetPixel(hdc, points[i].x, points[i].y) != ft.GetPenColour()) &&
			(GetPixel(hdc, points[i].x, points[i].y) != ft.GetBrushColour()))
			throw EXC_F_TR_VL_WRONG;
	}
	this->Draw();
}

COLORREF FilledTrapezoid::GetPenColour() {
	return pen;
}

COLORREF FilledTrapezoid::GetBrushColour() {
	return brush;
}

void FilledTrapezoid::BorderCheck() {
	RECT rt;
	int i;
	GetClientRect(hwnd_i, &rt);
	for (i = 0; i < count_of_p; ++i) {
		if (points[i].x < 0 || points[i].x > rt.right ||
			points[i].y < 0 || points[i].y > rt.bottom)
			throw EXC_OOB;
	}
}