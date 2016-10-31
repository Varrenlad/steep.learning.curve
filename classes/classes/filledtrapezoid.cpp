#include "filledtrapezoid.h"
//#include "commonfunc.h"

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
			throw;
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
	try {
		this->IsCorrect(points);
	}
	catch (int e) {
		throw;
	}
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
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
		throw;
	}
}

const COLORREF FilledTrapezoid::GetPenColour() const {
	return pen;
}

const COLORREF FilledTrapezoid::GetBrushColour() const {
	return brush;
}

bool FilledTrapezoid::HasColour(COLORREF c) {
	return (pen == c || brush == c);
}

char FilledTrapezoid::GetType() const {
	return 'f';
}

HBRUSH* FilledTrapezoid::CreateBrush(COLORREF color, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(color);
	else
		*retval = CreateHatchBrush(type, color);
	return retval;
}