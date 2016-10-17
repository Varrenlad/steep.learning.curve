#include <fstream>
#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <windowsx.h>
#include "../../steep.learning.curve/the_classes.h"

//#define INPUT_FILE "input.txt"
//#define INPUT_FILE "input1.txt"
#define INPUT_FILE "input2.txt"
#define OUTPUT_FILE "output.txt"

void save_data(Drawable *obj, std::ofstream &ofstr);
void draw(std::vector<Drawable *> objects, HDC hdc);
/*
int main() {
	std::ifstream ifstr;
	std::ofstream ofstr;
	HWND hwnd = GetConsoleWindow();;
	HDC hdc = GetDC(hwnd);
	int c, type;
	Background *bg = new Background(hdc, hwnd);
	ifstr.open(INPUT_FILE, std::ifstream::in);
	ofstr.open(OUTPUT_FILE, std::ofstream::out);
	if (ifstr.fail() || ofstr.fail()) {
		throw EXCEPTION_READ_FAULT;
		return -1;
	}
	try {
		bg->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
	}
	ifstr >> type;

	switch (type) {
	case 1:
	{	ContourTrapezoid *t = new ContourTrapezoid(hdc);
	try {
		t->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
	}
	
		ofstr << type << '\n';
		std::cout << "Do you want to save current data? Y/n\n";
		c = getchar();
		if (c != 'n' || c != 'N') {
			save_data(*bg, ofstr);
			save_data(*t, ofstr);
		}
		//bg->Getter(ofstr);
		//t->Getter(ofstr);
		delete t;
		break; }
	case 2:
	{	FilledTrapezoid *t = new FilledTrapezoid(hdc);
	try {
		t->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
	}
	t->Draw();
	ofstr << type << '\n';
	save_data(*bg, ofstr);
	save_data(*t, ofstr);
	delete t;
	break; }
	case 3:
	{	FilledTrapezoid *in = new FilledTrapezoid(hdc);
	FilledTrapezoid *out = new FilledTrapezoid(hdc);
	try {
		out->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
	}
	try {
		in->Setter(ifstr);
	}
	catch (int e) {
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
	}
	out->Draw();
	in->Draw(*out);
	ofstr << type << '\n';
	save_data(*bg, ofstr);
	save_data(*out, ofstr);
	save_data(*in, ofstr);
	delete out;
	delete in;
	break; }
	default:
		throw EXCEPTION_FLT_INVALID_OPERATION;
	}
	getchar();
	return 0;
}



char get_input() {
	int c;
	c = _getch();
	if (c == 0 || c == 224) {
		c = _getch();
		switch (c) {
		case 72:
			return 'u';
			break;
		case 80:
			return 'd';
			break;
		case 75:
			return 'r';
			break;
		case 77:
			return 'l';
			break;
		default:
			break;
		}
	}
	if (c == 27)
		return 'q';
	return 0;
}

void draw_single(Background &bg, Drawable &t) {
	int c;
	do {
		bg.Draw();
		t.Draw();
		c = get_input();
		switch (c) {
		case 'u':
			t.Move(0, -10);
			break;
		case 'd':
			t.Move(0, 10);
			break;
		case 'r':
			t.Move(10, 0);
			break;
		case 'l':
			t.Move(-10, 0);
			break;
		default:
			break;
		}
	} while (c != 27);
}

void draw_double(Background &bg, FilledTrapezoid &out, FilledTrapezoid &in) {
	int c;
	do {
		bg.Draw();
		out.Draw();
		try {
			in.Draw(out);
		}
		catch (int e) {
			if (e == EXCEPTION_NONCONTINUABLE)
				std::cout << "Inner trapezoid is not inside outer";
			else std::cout << "Unknown exception while drawing inner trapezoid";
			exit(-3);
		}
		c = get_input();
		switch (c) {
		case 'u':
			out.Move(0, -10);
			in.Move(0, -10);
			break;
		case 'd':
			out.Move(0, 10);
			in.Move(0, 10);
			break;
		case 'r':
			out.Move(10, 0);
			in.Move(10, 0);
			break;
		case 'l':
			out.Move(-10, 0);
			in.Move(-10, 0);
			break;
		default:
			break;
		}
	} while (c != 27);
}
*/

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
		if (e == EXCEPTION_READ_FAULT)
			std::cout << "Unable to read background color from file";
		else std::cout << "Unknown exception in background setter";
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
				std::cout << "Unable to read trapezoid data from file";
			else std::cout << "Unknown exception in trapezoid setter";
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
				std::cout << "Unable to read trapezoid data from file";
			else std::cout << "Unknown exception in trapezoid setter";
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
				std::cout << "Unable to read trapezoid data from file";
			else std::cout << "Unknown exception in double trapezoid setter";
		}
		objects.push_back(out);
		objects.push_back(in);

		draw(objects, hdc);

		break; }
	default:
		throw EXCEPTION_FLT_INVALID_OPERATION;
	}
	std::cout << "Do you want to save current data? Y/n\n";
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
				if (e == EXCEPTION_EXECUTE_FAULT)
					TextOutA(hdc, 0, 0, "Unable to draw: window is too small", 36);
				else if (e == EXCEPTION_NONCONTINUABLE)
					TextOutA(hdc, 0, 0, "Couldn't draw inner trapezoid", 30);
				else std::cout << "Unknown exception while drawing objects";
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