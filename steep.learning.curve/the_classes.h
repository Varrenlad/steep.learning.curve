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
	virtual void SetType() = 0;
	void Move(int x, int y) {
		int i;
		for (i = 0; i < count_of_p; ++i) {
			points[i].x += x;
			points[i].y += y;
		}
	}
	virtual void Getter(std::ostream str) {
		int i;
		for (i = 0; i < count_of_p; ++i)
			str << points[i].x << " " << points[i].y << "\n";
	}
	~Drawable() {
		delete[] points;
		count_of_p = 0;
	}
protected:
	POINT *points;
	HDC hdc;
	int count_of_p;
	int type_of_task;
	HPEN basePen;
	HBRUSH baseBrush;
};

class Background : public Drawable {
public:
	Background(HDC &hdc) : Drawable(2, hdc)
	{};
	void Draw(HWND hwnd) {
		Setter(hwnd);
		SelectBrush(hdc, baseBrush);
		Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
		DeleteBrush(baseBrush);
	}
	void Setter(COLORREF col) {
		baseBrush = CreateSolidBrush(col);
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
	void Setter(POINT *p) { ///Four points, no less
		int i;
		for (i = 0; i < count_of_p; ++i) {
			points[i] = p[i];
		}
		points[4] = p[0];
	}
	void SetPenType(int type) {
		pen_type = type;
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
	void Getter() {

	}
	void SetType(int type, int type_of_type) {
		if (type_of_type)
			pen_type = type;
		else
			brush_type = type;
	}
private:
	int pen_type = 0;
	int brush_type = 0;
	COLORREF pen;
	COLORREF brush;
};