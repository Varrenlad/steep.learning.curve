#include "commondata.h"
#include "drawable.h"
#include "background.h"
#include "contourtrapezoid.h"
#include "filledtrapezoid.h"
//#define INPUT_FILE "input.txt"
//#define INPUT_FILE "input1.txt"
#define INPUT_FILE "input2.txt"
#define OUTPUT_FILE "output.txt"

void save_data(Drawable *obj, std::ofstream &ofstr);
void draw(std::vector<Drawable *> objects, HDC hdc);

int main() {
	std::ifstream ifstr;
	std::ofstream ofstr;
	std::vector<Drawable *> objects;
	HWND hwnd = GetConsoleWindow();;
	HDC hdc = GetDC(hwnd);
	unsigned int c, type;
	Background *bg = new Background(hdc, hwnd);
	ifstr.open(INPUT_FILE, std::ifstream::in);
	ofstr.open(OUTPUT_FILE, std::ofstream::out);
	if (ifstr.rdstate() & std::ios::failbit ||
		ofstr.rdstate() & std::ios::failbit) {
		throw EXCEPTION_READ_FAULT;
		return -1;
	}
	ifstr >> type;
	try {
		bg->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_WRONG_VALUES)
			TextOutA(hdc, 0, 0, "Unable to read background color from file", 42);
		else TextOutA(hdc, 0, 0, "Unknown exception in background setter", 39);
	}
	objects.push_back(bg);
	switch (type) {
	case 1:
		{	ContourTrapezoid *t = new ContourTrapezoid(hdc, hwnd);
		try {
			t->Setter(ifstr);
		}
		catch (int e) {
			if (e == EXCEPTION_READ_FAULT)
				TextOutA(hdc, 0, 0, "Unable to read trapezoid data from file", 40);
			else TextOutA(hdc, 0, 0, "Unknown exception in trapezoid setter", 38);
		}
		objects.push_back(t);

		draw(objects, hdc);

		break; }
	case 2:
		{	FilledTrapezoid *t = new FilledTrapezoid(hdc, hwnd);
		try {
			t->Setter(ifstr);
		}
		catch (int e) {
			if (e == EXCEPTION_READ_FAULT)
				TextOutA(hdc, 0, 0, "Unable to read trapezoid data from file", 40);
			else TextOutA(hdc, 0, 0, "Unknown exception in trapezoid setter", 38);
		}
		objects.push_back(t);

		draw(objects, hdc);

		break; }
	case 3:
		{	FilledTrapezoid *in = new FilledTrapezoid(hdc, hwnd);
		FilledTrapezoid *out = new FilledTrapezoid(hdc, hwnd);
		try {
			out->Setter(ifstr);
			in->Setter(ifstr);
		}
		catch (int e) {
			if (e == EXCEPTION_READ_FAULT)
				TextOutA(hdc, 0, 0, "Unable to read trapezoid data from file", 40);
			else TextOutA(hdc, 0, 0, "Unknown exception in double trapezoid setter", 45);
		}
		objects.push_back(out);
		objects.push_back(in);

		draw(objects, hdc);

		break; }
	default:
		throw EXCEPTION_WRONG_VALUES;
	}
	TextOutA(hdc, 0, 0, "Do you want to save current data? Y/n\n", 39);
	c = getchar();
	if (c != 'n' || c != 'N') {
		ofstr << type << '\n';
		for (c = 0; c < objects.size(); ++c) {
			save_data(objects[c], ofstr);
		}
	}
}

void draw(std::vector<Drawable *> objects, HDC hdc) {
	unsigned int c, i;
	do {
		for (i = 0; i < objects.size(); ++i) {
			try {
				if (i != 2)
					objects[i]->Draw();
				else dynamic_cast<FilledTrapezoid *> (objects[i])->Draw(
					*dynamic_cast<FilledTrapezoid *> (objects[i - 1]));
			}
			catch (int e) {
				if (e == EXCEPTION_OUT_OF_BORDER)
					TextOutA(hdc, 0, 0, "Unable to draw: window is too small", 36);
				else if (e == EXCEPTION_WRONG_VALUES)
					TextOutA(hdc, 0, 16, "Couldn't draw inner trapezoid", 30);
				else TextOutA(hdc, 0, 32, "Unknown exception while drawing objects", 40);
				}
			}
		c = _getch();
		if (c == 0 || c == 224) {
			c = _getch();
			for (i = 1; i < objects.size(); ++i) {
				switch (c) {
				case 72:
					objects[i]->Move(0, -10);
					break;
				case 80:
					objects[i]->Move(0, 10);
					break;
				case 75:
					objects[i]->Move(-10, 0);
					break;
				case 77:
					objects[i]->Move(10, 0);
					break;
				default:
					break;
				}
			}
		}
	} while (c != 27);
}

void save_data(Drawable *obj, std::ofstream &ofstr) {
	obj->Getter(ofstr);
}