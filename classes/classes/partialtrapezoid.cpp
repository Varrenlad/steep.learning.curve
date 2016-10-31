#include "partialtrapezoid.h"
//#include "commonfunc.h"

PartialTrapezoid::PartialTrapezoid(HDC &hdc, HWND &hwnd) : FilledTrapezoid(hdc, hwnd) {
	bgBrush = RGB(0, 0, 0);
	hbgBrush = CreateSolidBrush(bgBrush);
}

PartialTrapezoid::PartialTrapezoid(Background &bg, HDC &hdc, HWND hwnd) : FilledTrapezoid(hdc, hwnd) {
	bgBrush = bg.GetColour();
	hbgBrush = CreateSolidBrush(bgBrush);
}

PartialTrapezoid::PartialTrapezoid(std::istream &st, HDC &hdc, HWND hwnd) : FilledTrapezoid(hdc, hwnd) {
	int r, g, b;
	st >> r >> g >> b;
	st.get();
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		throw EXC_F_TR_VL_WRONG;
	bgBrush = RGB(r, g, b);
	hbgBrush = CreateSolidBrush(bgBrush);
}

PartialTrapezoid::~PartialTrapezoid() {
}

void PartialTrapezoid::Draw() {
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
	SelectPen(hdc, hbgBrush);
	Polygon(hdc, in_points, 4);
}

void PartialTrapezoid::Setter(std::istream &st) {
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
	for (i = 0; i < count_of_p; ++i) {
		st >> in_points[i].x >> in_points[i].y;
	}
	try {
		this->IsCorrect(points);
		this->IsCorrect(in_points);
	}
	catch (int e) {
		throw;
	}
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
}

void PartialTrapezoid::Getter(std::ostream &st) {
	int i;
	try {
		st << (int)GetRValue(bgBrush) << ' ' << (int)GetGValue(bgBrush) << ' '
			<< (int)GetBValue(bgBrush) << '\n';
		st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
		st << (int)GetRValue(pen) << ' ' << (int)GetGValue(pen) << ' '
			<< (int)GetBValue(pen) << '\n';
		st << (int)GetRValue(brush) << ' ' << (int)GetGValue(brush) << ' '
			<< (int)GetBValue(brush) << '\n';
		for (i = 0; i < count_of_p; ++i) {
			st << points[i].x << ' ' << points[i].y << '\n';
		}
		for (i = 0; i < count_of_p; ++i) {
			st << in_points[i].x << ' ' << in_points[i].y << '\n';
		}
		st << '\n';
	}
	catch (int e) {
		throw;
	}
}

bool PartialTrapezoid::HasColour(COLORREF c) {
	return (c == pen || c == brush);
}

const COLORREF PartialTrapezoid::GetPenColour() const {
	return pen;
}

const COLORREF PartialTrapezoid::GetBrushColour() const {
	return brush;
}

bool PartialTrapezoid::PointInside(POINT p) {
	bool b1, b2, b3, res;
	b1 = Signum(p, in_points[0], in_points[1]) < 0.0f;
	b2 = Signum(p, in_points[1], in_points[3]) < 0.0f;
	b3 = Signum(p, in_points[3], in_points[0]) < 0.0f;
	res = ((b1 == b2) && (b2 == b3));
	b1 = Signum(p, in_points[1], in_points[2]) < 0.0f;
	b2 = Signum(p, in_points[2], in_points[3]) < 0.0f;
	b3 = Signum(p, in_points[3], in_points[1]) < 0.0f;
	if (res && ((b1 == b2) && (b2 == b3)))  
		return false; //if point is inside empty area
	b1 = Signum(p, points[0], points[1]) < 0.0f;
	b2 = Signum(p, points[1], points[3]) < 0.0f;
	b3 = Signum(p, points[3], points[0]) < 0.0f;
	res = ((b1 == b2) && (b2 == b3));
	b1 = Signum(p, points[1], points[2]) < 0.0f;
	b2 = Signum(p, points[2], points[3]) < 0.0f;
	b3 = Signum(p, points[3], points[1]) < 0.0f;
	return res && ((b1 == b2) && (b2 == b3));
}

char PartialTrapezoid::GetType() const {
	return 'p';
}