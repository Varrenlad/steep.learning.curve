#include "the_include.h"

int main() {
	int draw_type;
	HDC hdc;
	RECT rt;
	trapeze *base = new trapeze;
	trapeze *outer = new trapeze;
	trapeze *inner = new trapeze;
	colour *cBGColour = new colour;
	colour *cTrapezeColour = new colour;
	colour *cOuterColour = new colour;
	FILE *fp = fopen(INPUT_FILE, "r");
	HWND hwnd = GetConsoleWindow();
	HBRUSH hBackgroundBrush;
	hdc = GetDC(hwnd);
	draw_type = get_type(fp);
	GetClientRect(hwnd, &rt);
	switch (draw_type) {
	case 3:
		get_data(fp, outer, inner, cOuterColour, cBGColour);
		if (!validate_input(*outer, *inner, *cOuterColour, *cBGColour, rt))
			return 1;
		SetBkColor(hdc, RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
		while (getch() != 27) {
			GetClientRect(hwnd, &rt);
			draw_partfilled(*outer, *inner, RGB(cOuterColour->red, cOuterColour->green, cOuterColour->blue),
				RGB(cBGColour->red, cBGColour->green, cBGColour->blue), hdc);
		}
		break;
	case 2:
		get_data(fp, base, cTrapezeColour, cBGColour);
		if (!validate_input(*base, *cBGColour, *cTrapezeColour, rt))
			return 1;
		SetBkColor(hdc, RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
		while (getch() != 27) {
			draw_filled(*base, RGB(cTrapezeColour->red, cTrapezeColour->green, cTrapezeColour->blue), hdc);
			GetClientRect(hwnd, &rt);
		}
		break;
	default:
		get_data(fp, base, cTrapezeColour, cBGColour);
		if (!validate_input(*base, *cBGColour, *cTrapezeColour, rt))
			return 1;
		SetBkMode(hdc, OPAQUE);
		HPEN hTrapezePen =
			CreatePen(PS_SOLID, 5, RGB(cTrapezeColour->red, cTrapezeColour->green, cTrapezeColour->blue));
		hBackgroundBrush = CreateSolidBrush(RGB(cBGColour->red, cBGColour->green, cBGColour->blue));
		do {
			GetClientRect(hwnd, &rt);
			SelectBrush(hdc, hBackgroundBrush);
			Rectangle(hdc, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5); //awful dirty hack not to see contour of rectangle
			draw_contour(*base, hTrapezePen, hdc);
		} while (getch() != 27);
		break;
	}
}

/*
void main()
{
	// �������� ������������� ����
	HWND hwnd = GetConsoleWindow();
	// �������� �������� �����������
	hdc = GetDC(hwnd);
	char buf[100];
	// ������������� ���� ����
	SetBkColor(hdc, RGB(255, 10, 10));
	// ������������� ���� ������
	SetTextColor(hdc, RGB(255, 0, 0));
	// ������� ������� ����
	HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	// � �������� ��� � �������� �����������,
	// �������� ���������� ����
	HPEN hOldPen = SelectPen(hdc, hRedPen);
	// ������� ������� �����
	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hFaceBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hFaceBrush1 = CreateSolidBrush(RGB(255, 102, 0));
		// � �������� �� � �������� �����������,
		// �������� ���������� �����
	HBRUSH hOldBrush;
	// ������� ������ ������������ ����������
	printf("Graphics in Console Window.");
	do {
		hOldBrush = SelectBrush(hdc, hGreenBrush);
		// �������� ������ ����
		GetClientRect(hwnd, &rt);
		// ��������� ��������� ������
		sprintf(buf, "������ ���� %d �� %d ��������",
			rt.right, rt.bottom);
		// ������� ������ ������������ ����������
		TextOutA(hdc, 10, 10, buf, strlen(buf));
		// ������ ����������� ������
		Ellipse(hdc, 35, -200, rt.right - 30, rt.bottom + 100);
		hOldBrush = SelectBrush(hdc, hFaceBrush1);
		Ellipse(hdc, 60, 60, rt.right - 50, rt.bottom - 10);
		hOldBrush = SelectBrush(hdc, hFaceBrush);
		Ellipse(hdc, rt.right / 2 - 20, 70, rt.right / 2 + 20, rt.bottom - 10);
		
	} while (getch() != 27);
	SelectPen(hdc, hOldPen);
	// �������� � �������� ����������� ���������� �����
	SelectBrush(hdc, hOldBrush);
	// ������� ������� ����
	DeletePen(hRedPen);
	// ������� ������� �����
	DeleteBrush(hGreenBrush);
	// ����������� �������� �����������
	ReleaseDC(hwnd, hdc);
}
*/
