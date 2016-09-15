#pragma warning (disable : 4996)
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#define INPUT_FILE "input.txt"

HDC hdc;
RECT rt;

struct trapeze {
	int A[2];
	int B[2];
	int C[2];
	int D[2];
};

struct colour {
	int red;
	int green;
	int blue;
};

void draw_contour(trapeze t, HPEN hContourPen) {
	POINT ppt[5] = { {t.A[0], t.A[1]},{ t.B[0], t.B[1] },
	{ t.C[0], t.C[1] },{ t.D[0], t.D[1] },{ t.A[0], t.A[1] } };
	Polygon(hdc, ppt, 4);
}

void draw_filled(trapeze t, COLORREF colour) {
	HPEN hTransparentPen SelectPen(hdc, NULL_PEN);
	draw_contour(t, hTransparentPen);
	FloodFill(hdc, t.A[0], t.C[1], colour);
}

void draw_partfilled(trapeze outer, trapeze inner,
			COLORREF colour, COLORREF cBGColour) {
	HPEN hTransparentPen SelectPen(hdc, NULL_PEN);
	draw_contour(outer, hTransparentPen);
	FloodFill(hdc, outer.A[0], outer.C[1], colour);
	draw_contour(inner, hTransparentPen);
	FloodFill(hdc, inner.A[0], inner.C[1], colour);
}

int validate_trapeze(trapeze t) {
	if  (rt.right < t.A[0] || t.A[0] < 0)
		return 0;
	if  (rt.right < t.B[0] || t.B[0] < 0)
		return 0;
	if  (rt.right < t.C[0] || t.C[0] < 0)
		return 0;
	if  (rt.right < t.D[0] || t.D[0] < 0)
		return 0;
	if (rt.bottom < t.A[1] || t.A[1] < 0)
		return 0;
	if (rt.bottom < t.B[1] || t.B[1] < 0)
		return 0;
	if (rt.bottom < t.C[1] || t.C[1] < 0)
		return 0;
	if (rt.bottom < t.D[1] || t.D[1] < 0)
		return 0;
	return 1;
}

int validate_colour(colour c) {
	if (c.blue < 0  || c.blue > 255)
		return 0;
	if (c.green < 0 || c.green > 255)
		return 0;
	if (c.red < 0   || c.red > 255)
		return 0;
}

//For contoured and filled
int validate_input(trapeze t, colour cBGColour, colour cTrapezeColour) {
	if (!validate_trapeze(t) || !validate_colour(cBGColour) || !validate_colour(cTrapezeColour))
		return 0;
}
 
//For cut
int validate_input(trapeze outer, trapeze inner, colour cTrapezeColour, colour cBGColour) {
	if (!validate_trapeze(outer) || !validate_trapeze(inner) ||
		!validate_colour(cBGColour) || !validate_colour(cTrapezeColour))
		return 0;
}

int get_type(FILE *fp) {
	int i, j;
	fscanf(fp, "%d", i);
	return i;
}

void get_data(trapeze t, colour cTrapezeColour, colour cBGColour) {

}

void get_data(trapeze outer, trapeze inner, colour cTrapezeColour, colour cBGColour) {

}

int main() {
	FILE *fp = fopen(INPUT_FILE, "r");
	HWND hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	switch (get_type(fp)) {
	case 3:
		trapeze outer;
		trapeze inner;
		colour cOuterColour;
		colour cBGColour;
		get_data(outer, inner, cOuterColour, cBGColour);
		if (!validate_input(outer, inner, cOuterColour, cBGColour))
			return 1;
		while (getch() != 27)
			draw_partfilled(outer, inner, RGB(cOuterColour.red, cOuterColour.green, cOuterColour.blue),
				RGB(cBGColour.red, cBGColour.green, cBGColour.blue));
		break;
	case 2:
		trapeze base;
		colour cBGColour;
		colour cTrapezeColour;
		get_data(base, cTrapezeColour, cBGColour);
		if (!validate_input(base, cBGColour, cTrapezeColour))
			return 1;
		while (getch() != 27)
			draw_filled(base, RGB(cTrapezeColour.red, cTrapezeColour.green, cTrapezeColour.blue));
		break;
	default:
		trapeze base;
		colour cBGColour;
		colour cTrapezeColour;
		get_data(base, cTrapezeColour, cBGColour);
		if (!validate_input(base, cBGColour, cTrapezeColour))
			return 1;
		HPEN hTrapezePen = 
			CreatePen(PS_SOLID, 5, RGB(cTrapezeColour.red, cTrapezeColour.green, cTrapezeColour.blue));
		while (getch() != 27)
			draw_contour(base, hTrapezePen);
		break;
	}
}

/*
void main()
{
	// получаем идентификатор окна
	HWND hwnd = GetConsoleWindow();
	// получаем контекст отображения
	hdc = GetDC(hwnd);
	char buf[100];
	// устанавливаем цвет фона
	SetBkColor(hdc, RGB(255, 10, 10));
	// устанавливаем цвет текста
	SetTextColor(hdc, RGB(255, 0, 0));
	// создаем красное перо
	HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	// и выбираем его в контекст отображения,
	// сохраняя предыдущее перо
	HPEN hOldPen = SelectPen(hdc, hRedPen);
	// создаем зеленую кисть
	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hFaceBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hFaceBrush1 = CreateSolidBrush(RGB(255, 102, 0));
		// и выбираем ее в контекст отображения,
		// сохраняя предыдущую кисть
	HBRUSH hOldBrush;
	// выводим строку стандартными средствами
	printf("Graphics in Console Window.");
	do {
		hOldBrush = SelectBrush(hdc, hGreenBrush);
		// получаем размер окна
		GetClientRect(hwnd, &rt);
		// формируем выводимую строку
		sprintf(buf, "Размер окна %d на %d пикселей",
			rt.right, rt.bottom);
		// выводим строку графическими средствами
		TextOutA(hdc, 10, 10, buf, strlen(buf));
		// рисуем закрашенный эллипс
		Ellipse(hdc, 35, -200, rt.right - 30, rt.bottom + 100);
		hOldBrush = SelectBrush(hdc, hFaceBrush1);
		Ellipse(hdc, 60, 60, rt.right - 50, rt.bottom - 10);
		hOldBrush = SelectBrush(hdc, hFaceBrush);
		Ellipse(hdc, rt.right / 2 - 20, 70, rt.right / 2 + 20, rt.bottom - 10);
		
	} while (getch() != 27);
	SelectPen(hdc, hOldPen);
	// выбираем в контекст отображения предыдущую кисть
	SelectBrush(hdc, hOldBrush);
	// удаляем красное перо
	DeletePen(hRedPen);
	// удаляем зеленую кисть
	DeleteBrush(hGreenBrush);
	// освобождаем контекст отображения
	ReleaseDC(hwnd, hdc);
}
*/
