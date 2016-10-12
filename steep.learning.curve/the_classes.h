#pragma once
#include "the_include.h"

///Abstract class for everything
class Drawable {
public:
	Drawable(int input, HDC hdc_i) {
		points = new POINT[input];
		hdc = hdc_i;
		count_of_p = input;
		basePen = CreatePen(1, 1, RGB(0, 0, 0));
	}
	virtual void Draw() = 0;
	virtual void Setter() = 0;
	void Move(int x, int y) {
		int i;
		for (i = 0; i < count_of_p; ++i) {
			points[i].x += x;
			points[i].y += y;
		}
	}
	virtual void Getter() = 0;
	~Drawable() {
		delete[] points;
		count_of_p = 0;
	}
protected:
	POINT *points;
	HDC hdc;
	int count_of_p;
	int type_of_task;
	int pen_width;
	HPEN basePen;
	HBRUSH baseBrush;
};

class Background : public Drawable {
public:
	Background(HDC &hdc) : Drawable(2, hdc)
	{};
	void Draw(HWND hwnd) {
		baseBrush = CreateSolidBrush(bgc);
		Setter(hwnd);
		SelectBrush(hdc, baseBrush);
		Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
		DeleteBrush(baseBrush);
	}
	void Setter(std::ifstream &st) {
		int red, green, blue;
		st >> red >> green >> blue;
		if (red < 0   || red > 255 ||
			green < 0 || green > 255 ||
			blue < 0  || blue > 255)
			throw EXCEPTION_READ_FAULT;
		else bgc = RGB(red, green, blue);
	}
	void Getter(std::ofstream &st) {
		int i;
		try {
			st << GetRValue(bgc) << " " << GetGValue(bgc) << " " << GetBValue(bgc) << "\n";
			for (i = 0; i < count_of_p; ++i) {
				st << points[i].x << " " << points[i].y << "\n";
			}
		}
		catch (int e) {
			throw EXCEPTION_NONCONTINUABLE;
		}
	}
	~Background(){ //not sure if it even starts ~Drawable
		DeleteBrush(baseBrush);
	};
private:
	void Setter(HWND hwnd) {
		GetClientRect(hwnd, &rt);
		points[0].x = rt.left - 10;
		points[0].y = rt.top - 10;
		points[1].x = rt.right + 10;
		points[1].y = rt.bottom + 10;
	}
	RECT rt;
	COLORREF bgc;
};

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc) : Drawable(5, hdc)
	{};
	void Draw() {
		SelectPen(hdc, basePen);
		Polyline(hdc, points, 5);
		DeletePen(basePen);
	}
	void Setter(std::ifstream &st) { ///Four points, no less
		int i;
		st >> pen_type >> pen_width;
		for (i = 0; i < count_of_p - 1; ++i) {
			st >> points[i].x >> points[i].y;
		}
		points[4] = points[0];
		basePen = CreatePen(pen_type, pen_width, pen);
	}
	void Getter(std::ostream &st) {
		int i;
		try {
			st << pen_type << "\n";
			st << GetRValue(pen) << " " << GetGValue(pen) << " " << GetBValue(pen) << "\n";
			for (i = 0; i < count_of_p - 1; ++i) {
				st << points[i].x << " " << points[i].y << "\n";
			}
		}
		catch (int e) {
			throw;
		}
	}
private:
	int pen_type = 0;
	COLORREF pen;
};

class FilledTrapezoid : public Drawable {
public:
	FilledTrapezoid(HDC &hdc) : Drawable(4, hdc)
	{};
	void Draw() {
		SelectPen(hdc, basePen);
		SelectBrush(hdc, baseBrush);
		Polygon(hdc, points, 4);
		DeletePen(basePen);
		DeleteBrush(baseBrush);
	}
	void Setter(std::ifstream &st) { ///Four points, no less
		int i, r, g, b;
		st >> pen_type >> pen_width >> brush_type;
		st >> r >> g >> b;
		pen = RGB(r, g, b);
		st >> r >> g >> b;
		brush = RGB(r, g, b);
		for (i = 0; i < count_of_p; ++i) {
			st >> points[i].x >> points[i].y;
		}
		basePen = CreatePen(pen_type, pen_width, pen);
		baseBrush = CreateBrush(brush, brush_type);
	}
	void Getter(std::ostream &st) {
		int i;
		try {
			st << pen_type << " " << brush_type << "\n";
			st << GetRValue(pen) << " " << GetGValue(pen) << " " << GetBValue(pen) << "\n";
			st << GetRValue(brush) << " " << GetGValue(brush) << " " << GetBValue(brush) << "\n";
			for (i = 0; i < count_of_p - 1; ++i) {
				st << points[i].x << " " << points[i].y << "\n";
			}
		}
		catch (int e) {
			throw;
		}
	}
	void Draw(FilledTrapezoid &ft) {
		int i;
		for (i = 0; i < count_of_p; ++i) {
			if (!GetPixel(hdc, points[i].x, points[i].y) == ft.GetPenColour() ||
				!GetPixel(hdc, points[i].x, points[i].y) == ft.GetBrushColour())
				throw EXCEPTION_NONCONTINUABLE;
		}
	}
	COLORREF GetPenColour() {
		return pen;
	}
	COLORREF GetBrushColour() {
		return brush;
	}
private:
	int pen_type = 0;
	int brush_type = 0;
	COLORREF pen;
	COLORREF brush;
};