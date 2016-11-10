#include "filledtrapezoid.h"
//#include "commonfunc.h"

FilledTrapezoid::FilledTrapezoid(HDC &hdc, HWND hwnd) : ContourTrapezoid(hdc, hwnd) {
	brush_type = 0;
	brush = RGB(255, 255, 255);
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
	st >> pen_type >> pen_width >> brush_type;
	if ((this->LoadC(&pen, st))   || 
		(this->LoadC(&brush, st)) || 
		(this->LoadP(st, &points)))
		throw EXC_F_TR_VL_WRONG;
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
}

void FilledTrapezoid::Getter(std::ostream &st) {
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WR_FAIL;
	st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
	this->SaveC(pen, st);
	this->SaveC(brush, st);
	this->SaveP(st, points);
}

bool FilledTrapezoid::HasColour(COLORREF c) {
	return (pen == c || brush == c);
}

char FilledTrapezoid::GetType() const {
	return 'f';
}