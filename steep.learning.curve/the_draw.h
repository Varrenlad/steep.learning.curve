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
}

void draw_filled(trapeze t, COLORREF colour, HDC hdc) {
	POINT ppt[4] = { { t.A[0], t.A[1] },{ t.B[0], t.B[1] },
	{ t.C[0], t.C[1] },{ t.D[0], t.D[1] } };
	HPEN hTransparentPen SelectPen(hdc, NULL_PEN);
	//draw_contour(t, hTransparentPen);
	HBRUSH hFillBrush = CreateSolidBrush(colour);
	//FloodFill(hdc, t.A[0], t.C[1], colour);
	Polygon(hdc, ppt, 4);
}

void draw_partfilled(trapeze outer, trapeze inner, COLORREF colour, 
				COLORREF cBGColour, HDC hdc) {
	HPEN hTransparentPen SelectPen(hdc, NULL_PEN);
	draw_contour(outer, hTransparentPen, hdc);
	FloodFill(hdc, outer.A[0], outer.C[1], colour);
	draw_contour(inner, hTransparentPen, hdc);
	FloodFill(hdc, inner.A[0], inner.C[1], colour);
}