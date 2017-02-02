#include "trapezoid.h"

Trapezoid::Trapezoid(HDC &hdc_g, HWND hwnd_g) : Drawable(4, hdc) {
	hdc = hdc_g;
	hwnd = hwnd_g;
	brush_type = 0;
	brush = RGB(0, 0, 0);
	baseBrush = CreateSolidBrush(brush);
};

Trapezoid::~Trapezoid() {
	DeletePen(basePen);
	DeleteBrush(baseBrush);
}

void Trapezoid::Draw() {
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

void Trapezoid::Load(std::istream &st) { ///Four points, no less
	st >> pen_type >> pen_width >> brush_type;
	if ((this->LoadC(&pen, st))   || 
		(this->LoadC(&brush, st)))
		throw EXC_READ_FAIL;
	try {
	this->LoadP(st);
	}
	catch (int e) {
		throw;
	}
	basePen = CreatePen(pen_type, pen_width, pen);
	baseBrush = *CreateBrush(brush, brush_type);
}

void Trapezoid::Save(std::ostream &st) {
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WRITE_FAIL;
	st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
	this->SaveC(pen, st);
	this->SaveC(brush, st);
	this->SaveP(st);
}

char Trapezoid::GetType() const {
	return 't';
}

void Trapezoid::SaveC(COLORREF &cl, std::ostream &st) {
	st << (int)GetRValue(cl) << ' ' << (int)GetGValue(cl) << ' '
		<< (int)GetBValue(cl) << '\n';
	st.flush();
}

void Trapezoid::SaveP(std::ostream &st) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st << points[i].x << ' ' << points[i].y << '\n';
	}
	st.flush();
}

void Trapezoid::LoadP(std::istream &st) const {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		st >> (points)[i].x >> (points)[i].y;
	}
	st.get();
	//check data
	if (((points)[2].y - (points)[3].y) &&
		((points)[0].y - (points)[1].y)) {
		if (((points)[2].x - (points)[3].x) /
			((points)[2].y - (points)[3].y) !=
			((points)[0].x - (points)[1].x) /
			((points)[0].y - (points)[1].y))
			throw EXC_WRONG_POINTS_T;
	}
	else if ((points)[2].y - (points)[3].y !=
		(points)[0].y - (points)[1].y)
		throw EXC_WRONG_POINTS_T;
}

bool Trapezoid::LoadC(COLORREF *cl, std::istream &st) {
	int r, g, b;
	st >> r >> g >> b;
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		return true;
	*cl = RGB(r, g, b);
	return false;
}

void Trapezoid::CLoad(std::istream &st) {
	char c;
	//load types
	st >> pen_type >> pen_width >> brush_type;
	//load colours
	do {
		this->LoadC(&pen, st);
		this->LoadC(&brush, st);
		//show colours
		TextOutA(hdc, 0, 0, "Are the colours correct? Y\n; Pen, brush", 40);
		SelectBrush(hdc, pen);
		Rectangle(hdc, 80, 20, 100, 40);
		SelectBrush(hdc, brush);
		Rectangle(hdc, 110, 20, 140, 40); c;
		std::cin >> c;
		if (c != 'n' || c != 'N')
			c = 0;
	} while (c);
	//for each load and draw line
	for (size_t i = 0; i < count_of_p; ++i) {
		st >> (points)[i].x >> (points)[i].y;
		if (count_of_p > 1)
			Polyline(hdc, points, count_of_p);
		else Ellipse(hdc, points[0].x - pen_width, points[0].y - pen_width,
			points[0].x + pen_width, points[0].y + pen_width);
		TextOutA(hdc, 0, 0, "Is the position correct? Y\n", 30);
		std::cin >> c;
		if (c == 'n' || c == 'N')
			--i;
		InvalidateRect(NULL, NULL, TRUE);
		Sleep(50);
	}
	//data verification
	if (((points)[2].y - (points)[3].y) &&
		((points)[0].y - (points)[1].y)) {
		if (((points)[2].x - (points)[3].x) /
			((points)[2].y - (points)[3].y) !=
			((points)[0].x - (points)[1].x) /
			((points)[0].y - (points)[1].y))
			throw EXC_WRONG_POINTS_T;
	}
	else if ((points)[2].y - (points)[3].y !=
		(points)[0].y - (points)[1].y)
		throw EXC_WRONG_POINTS_T;
	//remove all our helpers
	InvalidateRect(NULL, NULL, TRUE);
	Sleep(50);
}