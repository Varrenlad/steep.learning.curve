#include "the_include.h"
int cont_proc(FILE *fp, HWND hwnd, HDC hdc);
int fill_proc(FILE *fp, HWND hwnd, HDC hdc);
int part_proc(FILE *fp, HWND hwnd, HDC hdc);

int cont_proc(FILE *fp, HWND hwnd, HDC hdc) {
	trapeze *base = new trapeze;
	colour *cBGColour = new colour;
	colour *cTrapezeColour = new colour;
	HBRUSH hBackgroundBrush;
	RECT rt;
	get_data(fp, base, cTrapezeColour, cBGColour);
	SetBkColor(hdc, RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	SetBkMode(hdc, OPAQUE);
	HPEN hTrapezePen = CreatePen(PS_SOLID, 5, RGB(cTrapezeColour->red, cTrapezeColour->green, 
					cTrapezeColour->blue));
	hBackgroundBrush = CreateSolidBrush(RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	do {
		GetClientRect(hwnd, &rt);
		if (validate_input(*base, *cBGColour, *cTrapezeColour, rt))
			return 1;
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		//awful dirty hack not to see contour of rectangle
		draw_contour(*base, hTrapezePen, hdc);
	} while (getch() != 27);
	DeletePen(hTrapezePen);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int fill_proc(FILE *fp, HWND hwnd, HDC hdc) {
	trapeze *base = new trapeze;
	colour *cBGColour = new colour;
	colour *cTrapezeColour = new colour;
	HBRUSH hBackgroundBrush;
	RECT rt;
	HPEN pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	SelectPen(hdc, pen);
	get_data(fp, base, cTrapezeColour, cBGColour);
	SetBkColor(hdc, RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	hBackgroundBrush = CreateSolidBrush(RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	do {
		GetClientRect(hwnd, &rt);
		if (validate_input(*base, *cBGColour, *cTrapezeColour, rt))
			return 1;
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		//awful dirty hack not to see contour of rectangle
		draw_filled(*base, RGB(cTrapezeColour->red, cTrapezeColour->green, cTrapezeColour->blue), hdc);
	} while (getch() != 27);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int part_proc(FILE *fp, HWND hwnd, HDC hdc) {
	trapeze *outer = new trapeze;
	trapeze *inner = new trapeze;
	colour *cBGColour = new colour;
	colour *cOuterColour = new colour;
	HBRUSH hBackgroundBrush;
	RECT rt;
	HPEN pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	SelectPen(hdc, pen);
	get_data(fp, outer, inner, cOuterColour, cBGColour);
	SetBkColor(hdc, RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	hBackgroundBrush = CreateSolidBrush(RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
	do {
		GetClientRect(hwnd, &rt);
		if (validate_input(*outer, *inner, *cOuterColour, *cBGColour, rt))
			return 1;
		SelectBrush(hdc, hBackgroundBrush);
		Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
		//awful dirty hack not to see contour of rectangle
		draw_partfilled(*outer, *inner, RGB(cOuterColour->red, cOuterColour->green, cOuterColour->blue),
						RGB(cBGColour->red, cBGColour->green, cBGColour->blue), hdc);
	} while (getch() != 27);
	DeleteBrush(hBackgroundBrush);
	ReleaseDC(hwnd, hdc);
	return 0;
}

int main() {
	int draw_type;
	FILE *fp = fopen(INPUT_FILE, "r");
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	draw_type = get_type(fp);
	switch (draw_type) {
	case 3:
		part_proc(fp, hwnd, hdc);
		break;
	case 2:
		fill_proc(fp, hwnd, hdc);
		break;
	case 1:
		cont_proc(fp, hwnd, hdc);
		break;
	default:
		return 1;
	}
	return 0;
}