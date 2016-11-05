#include "partialtrapezoid.h"
//#include "commonfunc.h"

PartialTrapezoid::PartialTrapezoid(HDC &hdc, HWND &hwnd) : FilledTrapezoid(hdc, hwnd) {
	in_points = new POINT[4];
	hbgBrush = 0;
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
	if (hbgBrush == 0)
		hbgBrush = CreateSolidBrush(GetPixel(hdc, 0, 0));
	SelectPen(hdc, basePen);
	SelectBrush(hdc, baseBrush);
	Polygon(hdc, points, 4);
	SelectPen(hdc, hbgBrush);
	Polygon(hdc, in_points, 4);
}

void PartialTrapezoid::Setter(std::istream &st) {
	st >> pen_type >> pen_width >> brush_type;
	if ((this->LoadC(&pen, st)) ||
		(this->LoadC(&brush, st)) ||
		(this->LoadP(st, &points)) ||
		(this->LoadP(st, &in_points)))
		throw EXC_P_TR_VL_WRONG;
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
}

void PartialTrapezoid::Getter(std::ostream &st) {
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WR_FAIL;
	st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
	this->SaveC(pen, st);
	this->SaveC(brush, st);
	this->SaveP(st, points);
	this->SaveP(st, in_points);
}

bool PartialTrapezoid::HasColour(COLORREF c) {
	return (c == pen || c == brush);
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