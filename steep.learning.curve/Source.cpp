#pragma warning (disable : 4996)
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
void main()
{
	// �������� ������������� ����
	HWND hwnd = GetConsoleWindow();
	// �������� �������� �����������
	HDC hdc = GetDC(hwnd);
	RECT rt;
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