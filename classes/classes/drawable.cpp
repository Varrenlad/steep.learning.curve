#include "drawable.h"

Drawable::Drawable(int input, HDC hdc_i) {
	pen_type = 0;
	pen_width = 5;
	pen = RGB(0, 0, 0);
	basePen = CreatePen(pen_type, pen_width, pen);
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

void Drawable::ModifyDC(HDC &new_dc) {
	hdc = new_dc;
}

void Drawable::ToEMF(std::string &filename) {
	HDC temp = hdc;
	HWND hwnd = GetConsoleWindow();
	RECT rt;
	GetClientRect(hwnd, &rt);
	if (!filename.size())
		throw EXC_WR_FAIL;
	filename.append(".emf");
	HDC hdcMeta = CreateEnhMetaFile(hdc, filename.c_str(), &rt, NULL);
	this->Draw();
	DeleteEnhMetaFile(CloseEnhMetaFile(hdcMeta));
	hdc = temp;
}

void Drawable::Resize(float new_size) {
	size_t i;
	if (new_size < 0)
		throw EXC_CANT_CONTAIN;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x *= new_size;
		points[i].y *= new_size;
	}
}

void Drawable::Rotate(float angle) { //rotation needs placement fix
	size_t i;
	POINT def_centre;
	if (count_of_p == 4) {
		float a = abs(points[1].x - points[0].x);
		float b = abs(points[3].x - points[2].x);
		float h = abs(points[1].y - points[0].y);
		def_centre.x = (a*a + a*b + b*b) / (3 * (a + b));//trapezoid
		def_centre.y = (h*(a + 2 * b)) / (3 * (a + b));
		SetPixel(hdc, def_centre.x, def_centre.y, RGB(0, 0, 0));
		_getch();
		_getch();
	}
	else { //rectangle
		def_centre.x = (points[0].x + points[1].x) / 2;
		def_centre.y = (points[0].y + points[1].y) / 2;
	}
	for (i = 0; i < count_of_p; ++i) {
		points[i].x = def_centre.x + (points[i].x + def_centre.x) * cos(angle) - (points[i].y + def_centre.y) * sin(angle);
		points[i].y = def_centre.y + (points[i].y + def_centre.y) * cos(angle) - (points[i].x + def_centre.x) * sin(angle);
	}
}