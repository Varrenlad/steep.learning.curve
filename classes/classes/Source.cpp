#include "commondata.h"
#include "drawable.h"
#include "background.h"
#include "contourtrapezoid.h"
#include "filledtrapezoid.h"
//#define INPUT_FILE "input.txt"
//#define INPUT_FILE "input1.txt"
#define INPUT_FILE "input9.txt"
#define OUTPUT_FILE "output.txt"

void save_data(Drawable *obj, std::ofstream &ofstr);
void draw(std::vector<Drawable *> objects, HDC hdc);

int main() {
	std::ifstream ifstr;
	std::ofstream ofstr;
	std::vector<Drawable *> objects;
	HWND hwnd = GetConsoleWindow();;
	HDC hdc = GetDC(hwnd);
	unsigned int i, type;
	Background *bg = new Background(hdc, hwnd);
	ifstr.open(INPUT_FILE, std::ifstream::in);
	ofstr.open(OUTPUT_FILE, std::ofstream::out);
	if (ifstr.rdstate() & std::ios::failbit ||
		ofstr.rdstate() & std::ios::failbit) {
		TextOutA(hdc, 0, 0, "Couldn't find file, aborting", 29);
		getchar();
		return -1;
	}
	ifstr >> type;
	objects.push_back(bg);
	switch (type) {
	case 1:
		{	ContourTrapezoid *t = new ContourTrapezoid(hdc, hwnd);
		objects.push_back(t);
		break; }
	case 2:
		{	FilledTrapezoid *t = new FilledTrapezoid(hdc, hwnd);
		objects.push_back(t);
		break; }
	case 3:
		{	FilledTrapezoid *in = new FilledTrapezoid(hdc, hwnd);
		FilledTrapezoid *out = new FilledTrapezoid(hdc, hwnd);
		objects.push_back(out);
		objects.push_back(in);
		break; }
	default:
		TextOutA(hdc, 0, 0, "Couldn't find type specializer, aborting", 41);
		getchar();
		exit(-1);
	}
	for (i = 0; i < objects.size(); ++i) {
		try {
			objects[i]->Setter(ifstr);
		}
		catch (int e) {
			if (e == EXC_BG_VL_WRONG)
				TextOutA(hdc, 0, 0, "Wrong background colour data", 29);
			if (e == EXC_C_TR_VL_WRONG)
				TextOutA(hdc, 0, 0, "Wrong contour trapezoid data", 29);
			if (e == EXC_F_TR_VL_WRONG)
				TextOutA(hdc, 0, 0, "Wrong filled trapezoid data", 28);
			else
				TextOutA(hdc, 0, 0, "Unknown error while reading file", 33);
		}
	}
	draw(objects, hdc);
	TextOutA(hdc, 0, 0, "Do you want to save current data? Y/n\n", 39);
	i = getchar();
	if (i != 'n' || i != 'N') {
		ofstr << type << '\n';
		for (i = 0; i < objects.size(); ++i) {
			try {
				save_data(objects[i], ofstr);
			}
			catch (int e) {
				if (e == EXC_WR_FAIL)
					TextOutA(hdc, 0, 0, "Unable to write data to file", 29);
				else
					TextOutA(hdc, 0, 0, "Unknown error while saving data", 32);
			}
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
				if (e == EXC_OOB)
					TextOutA(hdc, 0, 0, "Unable to draw: window is too small", 36);
				else if (e == EXC_F_TR_VL_WRONG)
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
	try {
		obj->Getter(ofstr);
	}
	catch (int e) {
		throw e;
	}
}