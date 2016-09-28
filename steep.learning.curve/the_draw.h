#pragma once
#include "the_include.h"
void draw_contour(trapeze, HPEN, HDC);
void draw_filled(trapeze, HPEN, HBRUSH, HDC);
void draw_partfilled(trapeze, trapeze, HPEN,
				HPEN, HBRUSH, HBRUSH, HDC);
int size_check(trapeze t, RECT rt, HDC hdc);
HBRUSH CreateBrush(colour, int);

void draw_contour(trapeze t, HPEN hPen, HDC hdc) {
	POINT ppt[5] = { { t.A[0], t.A[1] },{ t.B[0], t.B[1] },
	{ t.C[0], t.C[1] },{ t.D[0], t.D[1] },{ t.A[0], t.A[1] } };
	SelectPen(hdc, hPen);
	Polyline(hdc, ppt, 5);
}

void draw_filled(trapeze t, HPEN hPen, HBRUSH hBrush, HDC hdc) {
	POINT ppt[4] = { { t.A[0], t.A[1] },{ t.B[0], t.B[1] },
	               { t.C[0], t.C[1] },{ t.D[0], t.D[1] } };
	SelectPen(hdc, hPen);
	SelectBrush(hdc, hBrush);
	Polygon(hdc, ppt, 4);
}

void draw_partfilled(trapeze outer, trapeze inner, HPEN hIn,
				HPEN hOutP, HBRUSH hOutB, HBRUSH hBG, HDC hdc) {
	draw_filled(outer, hOutP, hOutB, hdc);
	draw_filled(inner, hIn, hBG, hdc);
}
	
int size_check(trapeze t, RECT rt, HDC hdc) {
	if (rt.right < t.A[0]  || t.A[0] < 0 ||
		rt.right < t.B[0]  || t.B[0] < 0 ||
		rt.right < t.C[0]  || t.C[0] < 0 ||
		rt.right < t.D[0]  || t.D[0] < 0 ||
		rt.bottom < t.A[1] || t.A[1] < 0 ||
		rt.bottom < t.B[1] || t.B[1] < 0 ||
		rt.bottom < t.C[1] || t.C[1] < 0 ||
		rt.bottom < t.D[1] || t.D[1] < 0) {
		TextOutA(hdc, 10, 10, "Window size is too small", 25);
		return 1;
	}
	return 0;
}

HBRUSH CreateBrush(colour cBrush, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(RGB(cBrush.red, cBrush.green, cBrush.blue));
	else
		*retval = CreateHatchBrush(type, RGB(cBrush.red, cBrush.green, cBrush.blue));
	return *retval;
}