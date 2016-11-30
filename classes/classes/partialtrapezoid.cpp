#include "partialtrapezoid.h"

PartialTrapezoid::PartialTrapezoid(HDC &hdc, HWND &hwnd) : FilledTrapezoid(hdc, hwnd) {
	inner = new FilledTrapezoid(hdc, hwnd);
	proxy = new FilledTrapezoid_Proxy(*inner);
}

PartialTrapezoid::~PartialTrapezoid() {
	delete inner;
}

void PartialTrapezoid::Draw() {
	size_t i;
	try {
		BorderCheck();
	}
	catch (int e) {
		throw;
	}
	proxy->UpdateColour(GetPixel(hdc, (points[0].x + points[1].x) / 2,
									  (points[0].y + points[3].y) / 2));
	SelectPen(hdc, basePen);
	SelectBrush(hdc, baseBrush);
	Polygon(hdc, points, 4);
	for (i = 0; i < count_of_p; i++) {
		if (!(this->PointInside(proxy->GetPoint(i))))
			throw EXC_P_TR_VL_WRONG;
	}
	inner->Draw();
}

void PartialTrapezoid::Setter(std::istream &st) {
	st >> pen_type >> pen_width >> brush_type;
	if ((this->LoadC(&pen, st))    ||
		(this->LoadC(&brush, st))  ||
		(this->LoadP(st)) ||
		(proxy->LoadP(st)))
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
	this->SaveP(st);
	proxy->SaveP(st);
}

bool PartialTrapezoid::HasColour(COLORREF c) {
	return (c == pen || c == brush);
}

bool PartialTrapezoid::PointInsideF(POINT p) {
	bool b1, b2, b3, res;
	if (inner->PointInside(p))
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

void PartialTrapezoid::Move(int x, int y) {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x += x;
		points[i].y += y;
	}
	inner->Move(x, y);
}

void PartialTrapezoid::Resize(float new_size) {
	size_t i;
	if (new_size < 0)
		throw EXC_CANT_CONTAIN;
	points[0].x *= new_size;
	points[0].y *= new_size;
	points[2].y *= new_size;
	points[3].x *= new_size;
	points[3].y *= new_size;
	proxy->Resize(new_size);
}

void PartialTrapezoid::Rotate(float an) {
	size_t i;
	double angle = an / 57.3, x, y;
	POINT def_centre;
	def_centre.x = points[0].x;
	def_centre.y = points[0].y;
	for (i = 0; i < count_of_p; ++i) {
		x = def_centre.x + (points[i].x - def_centre.x) * std::cos(angle) - (points[i].y - def_centre.y) * std::sin(angle);
		y = def_centre.y + (points[i].y - def_centre.y) * std::cos(angle) + (points[i].x - def_centre.x) * std::sin(angle);
		points[i].x = x;
		points[i].y = y;
	}
	proxy->Rotate(angle);
}