#include "drawable.h"

Drawable::Drawable(int input, HDC hdc_i) {
	pen_type = 0;
	pen_width = 5;
	pen = RGB(0, 0, 0);
	CreatePen(pen_type, pen_width, pen);
	points = new POINT[input];
	hwnd_i = 0;
	hdc = hdc_i;
	count_of_p = input;
}

Drawable::~Drawable() {
	delete[] points;
	DeletePen(basePen);
	count_of_p = 0;
}