#include "the_include.h"
int cont_proc(FILE *, HWND, HDC);
int fill_proc(FILE *, HWND, HDC);
int part_proc(FILE *, HWND, HDC);

int cont_proc(FILE *fp, HWND hwnd, HDC hdc) {
	int pen_type;
	trapeze *base = new trapeze;
	colour *cBG = new colour;
	colour *cTrapeze = new colour;
	HBRUSH hBackgroundBrush;
	RECT rt;
	pen_type = get_type(fp);
	if (get_data(fp, base, cTrapeze, cBG))
		return 2;
	SetBkColor(hdc, RGB(255 - cBG->red, 255 - cBG->green, 255 - cBG->blue));
	SetBkMode(hdc, OPAQUE);
	HPEN hTrapezePen = CreatePen(pen_type, 5, RGB(cTrapeze->red, cTrapeze->green,
		cTrapeze->blue));
	hBackgroundBrush = CreateSolidBrush(RGB(cBG->red, cBG->green, cBG->blue));
	do {
		GetClientRect(hwnd, &rt);
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		if (size_check(*base, rt, hdc))
			continue;
		draw_contour(*base, hTrapezePen, hdc);
	} while (getch() != 27);
	DeletePen(hTrapezePen);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int fill_proc(FILE *fp, HWND hwnd, HDC hdc) {
	int pen_type;
	int brush_type;
	trapeze *base = new trapeze;
	colour *cBG = new colour;
	colour *cTrapeze = new colour;
	colour *cTrapezePen = new colour;
	RECT rt;
	pen_type = get_type(fp);
	brush_type = get_type(fp);
	if (get_data(fp, base, cTrapezePen, cBG, cTrapeze))
		return 2;
	HPEN hTrapezePen = CreatePen(pen_type, 5, RGB(cTrapeze->red, cTrapeze->green,
		cTrapeze->blue));
	HBRUSH hTrapezeBrush = CreateBrush(*cTrapeze, brush_type);
	SetBkColor(hdc, RGB(255 - cBG->red, 255 - cBG->green, 255 - cBG->blue));
	HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(cBG->red, cBG->green, cBG->blue));
	do {
		GetClientRect(hwnd, &rt);
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		if (size_check(*base, rt, hdc))
			continue;
		if (validate_input(*base, *cBG, *cTrapeze))
			return 1;
		draw_filled(*base, hTrapezePen, hTrapezeBrush, hdc);
	} while (getch() != 27);
	DeletePen(hTrapezePen);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int part_proc(FILE *fp, HWND hwnd, HDC hdc) {
	int pen_type_in, pen_type_out;
	int brush_type;
	trapeze *outer = new trapeze;
	trapeze *inner = new trapeze;
	colour *cBG = new colour;
	colour *cOuter = new colour;
	colour *cPenIn = new colour;
	colour *cPenOut = new colour;
	RECT rt;
	pen_type_in = get_type(fp);
	pen_type_out = get_type(fp);
	brush_type = get_type(fp);
	if (get_data(fp, outer, inner, cBG, cOuter, cPenOut, cPenIn))
		return 2;
	do {
		GetClientRect(hwnd, &rt);
	} while (size_check(*outer, rt, hdc));
		if (!validate_trapeze(*inner, *outer, hdc))
		return 3;
	HPEN hPenIn = CreatePen(pen_type_in, 0, RGB(cPenIn->red, cPenIn->green, cPenIn->blue));
	HPEN hPenOut = CreatePen(pen_type_out, 0, RGB(cPenOut->red, cPenOut->green, cPenOut->blue));
	HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(cBG->red, cBG->green, cBG->blue));
	HBRUSH hTrapezeBrush = CreateBrush(*cOuter, brush_type);
	SetBkColor(hdc, RGB(255 - cBG->red, 255 - cBG->green, 255 - cBG->blue));
	do {
		GetClientRect(hwnd, &rt);
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		if (size_check(*outer, rt, hdc))
			continue;
		draw_partfilled(*outer, *inner, hPenIn, hPenOut, hTrapezeBrush, hBackgroundBrush, hdc);
	} while (getch() != 27);
	DeletePen(hPenIn);
	DeletePen(hPenOut);
	DeleteBrush(hTrapezeBrush);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int main() {
	int draw_type, brush_type, pen_type;
	FILE *fp = fopen(INPUT_FILE, "r");
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	draw_type = get_type(fp);
	if (validate_type(draw_type)) {
		switch (draw_type) {
		case 3:
			return part_proc(fp, hwnd, hdc);
		case 2:
			return fill_proc(fp, hwnd, hdc);
		case 1:
			return cont_proc(fp, hwnd, hdc);
		default:
			return 10;
		}
	}
}