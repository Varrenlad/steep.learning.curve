#pragma warning (disable : 4996)
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
void main()
{
	// получаем идентификатор окна
	HWND hwnd = GetConsoleWindow();
	// получаем контекст отображения
	HDC hdc = GetDC(hwnd);
	RECT rt;
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
		
	} while (getch() != 27); // при нажатии любой клавиши
							 // (кроме Esc) перерисовываем изображение,
							 // изображение изменится, если изменились размеры окна,
							 // нажатие Esc – выход
							 // выбираем в контекст отображения предыдущее перо
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