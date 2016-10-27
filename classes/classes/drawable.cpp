#include "drawable.h"
#include "commondata.h"

Drawable::Drawable(int input, HDC hdc_i) {
	points = new POINT[input];
	hdc = hdc_i;
	count_of_p = input;
	basePen = CreatePen(1, 1, RGB(0, 0, 0));
}

void Drawable::Move(int x, int y) {
	int i;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x += x;
		points[i].y += y;
	}
}

Drawable::~Drawable() {
	delete[] points;
	DeletePen(basePen);
	DeleteBrush(baseBrush);
	count_of_p = 0;
}