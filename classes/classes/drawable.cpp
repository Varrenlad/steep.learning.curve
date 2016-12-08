#include "drawable.h"

Drawable::Drawable(int input, HDC hdc_i) {
	pen_type = 0;
	pen_width = 5;
	pen = RGB(0, 0, 0);
	basePen = CreatePen(pen_type, pen_width, pen);
	points = new POINT[input];
	hwnd = GetConsoleWindow();
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
		throw EXC_WRITE_FAIL;
	filename.append(".emf");
	HDC hdcMeta = CreateEnhMetaFile(hdc, filename.c_str(), &rt, NULL);
	this->Draw();
	DeleteEnhMetaFile(CloseEnhMetaFile(hdcMeta));
	hdc = temp;
}

void Drawable::Resize(float new_size) {//switch to matrix of transformation; urgent
	size_t i;
	POINT def_centre;
	long double x, y;
	def_centre.x = points[0].x;
	def_centre.y = points[0].y;
	if (new_size < 0)
		throw EXC_CORRUPT_DATA;
	for (i = 0; i < count_of_p; ++i) {
		x = def_centre.x + (points[i].x - def_centre.x) * new_size;
		y = def_centre.y + (points[i].y - def_centre.y) * new_size;
		points[i].x = x;
		points[i].y = y;
	}
}

void Drawable::Rotate(float an) { //this is fine. No fix pending 
	size_t i;
	double angle = an / 57.3, x, y;
	POINT def_centre;
	def_centre.x = points[0].x;
	def_centre.y = points[0].y;
	for (i = 0; i < count_of_p; ++i) {
		x = def_centre.x + (points[i].x - def_centre.x) * std::cos(angle) - (points[i].y - def_centre.y) * std::sin(angle);
		y = def_centre.y + (points[i].y - def_centre.y) * std::cos(angle) + (points[i].x - def_centre.x) * std::sin(angle);
		points[i].x = x;
		points[i].y = y;
	}
}

HBRUSH* Drawable::CreateBrush(COLORREF color, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(color);
	else
		*retval = CreateHatchBrush(type, color);
	return retval;
}

void Drawable::BorderCheck() {
	RECT rt;
	size_t i;
	GetClientRect(hwnd, &rt);
	for (i = 0; i < count_of_p; ++i) {
		if (points[i].x < 0 || points[i].x > rt.right ||
			points[i].y < 0 || points[i].y > rt.bottom)
			throw EXC_OOB;
	}
}

void Drawable::Move(int x, int y) {
	size_t i;
	for (i = 0; i < count_of_p; ++i) {
		points[i].x += x;
		points[i].y += y;
	}
}