#include "contourtrapezoid.h"

ContourTrapezoid::ContourTrapezoid(HDC &hdc, HWND hwnd) : Drawable(4, hdc) {
	pen_type = 0;
	pen_width = 5;
	pen = RGB(0, 0, 0);
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
			throw;
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
	st >> pen_type >> pen_width;
	if (this->LoadC(&pen, st))
		throw EXC_C_TR_VL_WRONG;
	if (this->LoadP(st, &points))
		throw EXC_C_TR_VL_WRONG;
	basePen = CreatePen(pen_type, pen_width, pen);
}

void ContourTrapezoid::Getter(std::ostream &st) {
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WR_FAIL;
	st << pen_type << ' ' << pen_width << '\n';
	this->SaveC(pen, st);
	this->SaveP(st, points);
}

void ContourTrapezoid::BorderCheck() {
	RECT rt;
	size_t i;
	GetClientRect(hwnd_i, &rt);
	for (i = 0; i < count_of_p; ++i) {
		if (points[i].x < 0 || points[i].x > rt.right ||
			points[i].y < 0 || points[i].y > rt.bottom)
			throw EXC_OOB;
	}
}

bool ContourTrapezoid::PointInside(POINT p) {
	bool b1, b2, b3, res;
	b1 = Signum(p, points[0], points[1]) < 0.0f;
	b2 = Signum(p, points[1], points[3]) < 0.0f;
	b3 = Signum(p, points[3], points[0]) < 0.0f;
	res = ((b1 == b2) && (b2 == b3));
	b1 = Signum(p, points[1], points[2]) < 0.0f;
	b2 = Signum(p, points[2], points[3]) < 0.0f;
	b3 = Signum(p, points[3], points[1]) < 0.0f;
	return res || ((b1 == b2) && (b2 == b3));
}

double ContourTrapezoid::Signum(POINT p1, POINT p2, POINT p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool ContourTrapezoid::HasColour(COLORREF c) {
	return (pen == c);
}

char ContourTrapezoid::GetType() const {
	return 'c';
}

void ContourTrapezoid::SaveC(COLORREF &cl, std::ostream &st) {
	st << (int)GetRValue(cl) << ' ' << (int)GetGValue(cl) << ' '
		<< (int)GetBValue(cl) << '\n';
	st.flush();
}

void ContourTrapezoid::SaveP(std::ostream &st, POINT *p) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st << p[i].x << ' ' << p[i].y << '\n';
	}
	st.flush();
}

bool ContourTrapezoid::LoadP(std::istream &st, POINT **p) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st >> (*p)[i].x >> (*p)[i].y;
	}
	st.get();
	//check data
	if (((*p)[2].y - (*p)[3].y) &&
		((*p)[0].y - (*p)[1].y)) {
		if (((*p)[2].x - (*p)[3].x) /
			((*p)[2].y - (*p)[3].y) !=
			((*p)[0].x - (*p)[1].x) /
			((*p)[0].y - (*p)[1].y))
			return true;
	}
	else if ((*p)[2].y - (*p)[3].y !=
		(*p)[0].y - (*p)[1].y)
		return true;
	return false;
}

bool ContourTrapezoid::LoadC(COLORREF *cl, std::istream &st) {
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		return true;
	*cl = RGB(r, g, b);
	return false;
}

void ContourTrapezoid::Move(int x, int y) {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x += x;
		points[i].y += y;
	}
}