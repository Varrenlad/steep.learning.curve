#pragma warning (disable : 4996)
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>

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
	Polyline(hdc, ppt, 5);
}

void draw_filled(trapeze t, HBRUSH hTrapezeBrush) {

}

void draw_partfilled(trapeze outer, trapeze inner, HPEN hContourPen,
					 HBRUSH hTrapezeBrush, colour cBGColour) {

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

//For contoured
int validate_input(trapeze t, HPEN hContourPen, colour cBGColour) {
	if (!validate_trapeze(t))
		return 0;
}

//For filled
int validate_input(trapeze t, HBRUSH hTrapezeBrush, colour cBGColour) {
	if (!validate_trapeze(t))
		return 0;
	if (!validate_colour(cBGColour))
		return 0;
}
 
//For cut
int validate_input(trapeze outer, trapeze inner, HPEN hContourPen,
HBRUSH hTrapezeBrush, colour cBGColour) {
	if (!validate_trapeze(outer))
		return 0;
	if (!validate_trapeze(inner))
		return 0;
	if (!validate_colour(cBGColour))
		return 0;
}

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
		
	} while (getch() != 27); // ��� ������� ����� �������
							 // (����� Esc) �������������� �����������,
							 // ����������� ���������, ���� ���������� ������� ����,
							 // ������� Esc � �����
							 // �������� � �������� ����������� ���������� ����
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

