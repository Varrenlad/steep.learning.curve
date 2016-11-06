#include "drawable.h"

Drawable::Drawable(int input, HDC hdc_i) {
	points = new POINT[input];
	hwnd_i = 0;
	hdc = hdc_i;
	count_of_p = input;
	basePen = CreatePen(1, 1, RGB(0, 0, 0));
	baseBrush = CreateSolidBrush(RGB(0, 0, 0));
}

Drawable::~Drawable() {
	delete[] points;
	DeletePen(basePen);
	DeleteBrush(baseBrush);
	count_of_p = 0;
}