#include <fstream>
#include <Windows.h>
#include <windowsx.h>
#include "../../steep.learning.curve/the_classes.h"

#define INPUT_FILE "input.txt"

int main() {
	std::ifstream ifstr;
	std::ofstream oistr; //FIXME
	HDC hdc;
	HWND hwnd;
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	Background *bg = new Background(hdc, hwnd);
	ifstr.open(INPUT_FILE, std::ifstream::in);
	if (ifstr.fail()) {
		throw EXCEPTION_READ_FAULT;
		return -1;
	}
	int type;
	ifstr >> type;
	bg->Setter(ifstr);
	bg->Draw();
	switch (type) {
	case 1:
	{ContourTrapezoid *t = new ContourTrapezoid(hdc);
	t->Setter(ifstr);
	t->Draw();
	delete t;
	break; }
	case 2:
	{FilledTrapezoid *t = new FilledTrapezoid(hdc);
	t->Setter(ifstr);
	t->Draw();
	delete t;
	break; }
	case 3:
	{FilledTrapezoid *in = new FilledTrapezoid(hdc);
	FilledTrapezoid *out = new FilledTrapezoid(hdc);
	out->Setter(ifstr);
	in->Setter(ifstr);
	out->Draw();
	in->Draw(*out);
	delete out;
	delete in;
	break; }
	default:
		throw EXCEPTION_FLT_INVALID_OPERATION;
	}
	return 0;
}