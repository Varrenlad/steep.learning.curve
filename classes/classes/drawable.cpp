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

void Drawable::Resize(float new_size) { //resize needs accuracy gix
	size_t i;
	if (new_size < 0)
		throw EXC_CANT_CONTAIN;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x *= new_size;
		points[i].y *= new_size;
	}
}

void Drawable::Rotate(float an) { //rotation needs accuracy fix 
	size_t i;
	double angle = an/57.3, temp = angle, x, y;
	POINT def_centre;
	POINT line[2];
	if (count_of_p == 4) {
		float a = abs(points[1].x + points[0].x);
		float h = abs(points[2].y + points[0].y);
		def_centre.x = a / 2;
		def_centre.y = h / 2;
	}
	else { //rectangle
		def_centre.x = (points[0].x + points[1].x) / 2;
		def_centre.y = (points[0].y + points[1].y) / 2;
	}
	for (i = 0; i < count_of_p; ++i) {
		x = points[i].x;
		y = points[i].y;
		//while (angle > 0) {
			x = def_centre.x + (x - def_centre.x) * std::cos(angle) + (y - def_centre.y) * std::sin(angle);
			y = def_centre.y + (y - def_centre.y) * std::cos(angle) - (x - def_centre.x) * std::sin(angle);
			//angle -= (rot > 0) ? 0.1 : -0.1;
		//}
		points[i].x = round(x);
		points[i].y = round(y);
	}
}