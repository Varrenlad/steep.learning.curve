#pragma once
#include "the_include.h"

class Drawable {
protected:
	int number_of_points;
	HDC hdc_i;
	HPEN basePen;
	HBRUSH baseBrush;
public:
	Drawable(int input, HDC &hdc) {
		number_of_points = input;
		points_of_figure = new POINT[input];
		basePen = CreatePen(1, 0, RGB(0, 0, 0));
		hdc_i = hdc;
	}
	virtual void draw(HPEN, POINT*, HDC, int);
	virtual void draw(HPEN, HBRUSH, HDC, POINT*);
	virtual void draw(HPEN, HPEN, HBRUSH, HBRUSH, HDC, POINT*);
	virtual int *get_types(std::istream);
	virtual POINT *load_data(std::istream, int);
	virtual void load_colour(std::istream);
	virtual void validate(colour, POINT*, int);
	virtual void validate(colour, colour, POINT*, int);
	virtual void validate(colour, colour, colour, colour, POINT*, int);
private:
	POINT *points_of_figure;
};

class Background : public Drawable {
public:
	Background(int input, HDC &hdc) : Drawable(input, hdc)
	{};
	void draw(int num, RECT rt) {
		SelectPen(hdc_i, basePen);
		SelectBrush(hdc_i, baseBrush);
		Rectangle(hdc_i, rt.left - 10, rt.top - 10, rt.right + 10, rt.bottom + 10);
	}
	void load_colour(std::istream iost) {
		colour new_colour;
		iost >> new_colour.red >> new_colour.green >> new_colour.blue;
		if (new_colour.red > 255 || new_colour.green > 255 || new_colour.blue > 255)
			throw EXCEPTION_READ_FAULT;
		else {
			baseColour = RGB(new_colour.red, new_colour.green, new_colour.blue);
			baseBrush = CreateSolidBrush(baseColour);
		}
	}
	~Background() {
		DeletePen(basePen);
		DeleteBrush(baseBrush);
	}
private:
	COLORREF baseColour;
};