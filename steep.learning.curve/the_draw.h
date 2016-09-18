#pragma once
#include "the_include.h"
void draw_contour(trapeze t, HPEN hContourPen, HDC hdc);
void draw_filled(trapeze t, COLORREF colour, HDC hdc);
void draw_partfilled(trapeze outer, trapeze inner,
				COLORREF colour, COLORREF cBGColour, HDC hdc);

void draw_contour(trapeze t, HPEN hContourPen, HDC hdc) {
				POINT ppt[5] = { { t.A[0], t.A[1] },{ t.B[0], t.B[1] },
	{ t.C[0], t.C[1] },{ t.D[0], t.D[1] },{ t.A[0], t.A[1] } };
	SelectPen(hdc, hContourPen);
	Polyline(hdc, ppt, 5);
	DeletePen(hContourPen);
}

void draw_filled(trapeze t, COLORREF colour, HDC hdc) {
				POINT ppt[4] = { { t.A[0], t.A[1] },{ t.B[0], t.B[1] },
	{ t.C[0], t.C[1] },{ t.D[0], t.D[1] } };
	HBRUSH hFillBrush = CreateSolidBrush(colour);
	SelectBrush(hdc, hFillBrush);
	Polygon(hdc, ppt, 4);
	DeleteBrush(hFillBrush);
}

void draw_partfilled(trapeze outer, trapeze inner, COLORREF colour,
				COLORREF cBGColour, HDC hdc) {
	draw_filled(outer, colour, hdc);
	draw_filled(inner, cBGColour, hdc);
}
	//HPEN hTransparentPen SelectPen(hdc, NULL_PEN);
	//draw_contour(outer, hTransparentPen, hdc);
	//FloodFill(hdc, outer.A[0], outer.C[1], colour);
	//draw_contour(inner, hTransparentPen, hdc);
	//FloodFill(hdc, inner.A[0], inner.C[1], colour);
