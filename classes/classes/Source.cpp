#include "container.h"
void draw(Container<Drawable> &objects, HDC hdc, HWND nwnd);

int main() {
	char filename[FILENAME_MAX];
	std::ifstream ifstr;
	std::ofstream ofstr;
	Container<Drawable> objects;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	size_t i;/*
	while (true) {
		std::cin >> filename;
		ifstr.open(filename, std::ifstream::in);
		if (ifstr.rdstate() & std::ios::failbit) {
			TextOutA(hdc, 0, 0, "Couldn't find file, aborting", 29);
			getchar();
		}
		else break;
	}
	getchar();
		try {
			objects.Load(ifstr, hdc, hwnd);
		}
		catch (int e) {
			TextOutA(hdc, 0, 0, "Unknown error while loading", 28);
			std::cout << e;
			getchar();
			exit(-1);
		}
	ifstr.sync();
	ifstr.close();*/
	draw(objects, hdc, hwnd);
	TextOutA(hdc, 0, 0, "Do you want to save current data? Y/n\n", 39);
	i = getchar();
	if (i != 'n' || i != 'N') {
		TextOutA(hdc, 0, 20, "Where to save data?", 20);
		std::cin >> filename;
		ofstr.open(filename, std::ofstream::out);
		try {
			objects.Save(ofstr);
		}
		catch (int e) {
			if (e == EXC_WRITE_FAIL)
				TextOutA(hdc, 0, 0, "Unable to write data to file", 29);
			else
				TextOutA(hdc, 0, 0, "Unknown error while saving data", 32);
		}
	}
	ofstr.close();
	return 0;
}

void draw(Container<Drawable> &objects, HDC hdc, HWND hwnd) {
	bool show_debugging_info = 0;
	unsigned int c, i;
	do {
		InvalidateRect(hwnd, NULL, TRUE);
		Sleep(10);
		system("cls");
		for (i = 0; i < objects.Size(); ++i) {
			try {
				if (show_debugging_info) {
					system("cls");
					objects[i].Save(std::cout);
				}
				objects[i].Draw();
			}
			catch (int e) {
				if (e == EXC_OOB)
					TextOutA(hdc, 0, 0, "Unable to draw: window is too small", 36);
				else TextOutA(hdc, 0, 32, "Unknown exception while drawing objects", 40);
				}
			}
		c = _getch();
		if (c == 'a') {
			bool isFine = 1;
			char t;
			Drawable *obj;
			std::cout << "t for trapezoid, r for rectangle" << std::endl;
			std::cin >> t;
			switch (t) {
			case 't': {
				obj = new Trapezoid(hdc, hwnd);
				std::cout << "Syntax: pen colour (3 int)" << std::endl
					<< "Brush colour (3 int)" << std::endl
					<< "Point x, y (4 times)" << std::endl;
				try {
					obj->Load(std::cin);
				}
				catch (int e) {
					isFine = 0;
					std::cout << e;
					Sleep(10000);
				}
				break;
			}
			case 'r': {
				obj = new _Rectangle(hdc, hwnd);
				std::cout << "Syntax: pen colour (3 int)" << std::endl
					<< "Brush colour (3 int)" << std::endl
					<< "Point x, y (2 times)" << std::endl;
				try {
					obj->Load(std::cin);
				}
				catch (int e) {
					isFine = 0;
					std::cout << e;
					Sleep(10000);
				}
				break;
			}
			default:
				obj = nullptr;
				isFine = 0;
				break;
			}
			if (isFine) {
				objects.Push(obj);
			}
			else {
				TextOutA(hdc, 0, 16, "Wrong data received", 30);
				if (obj)
					delete obj;
			}
		}
		if (c == 'r') {
			float f;
			std::cout << "Input angle to rotate" << std::endl;
			std::cin >> f;
			for (i = 0; i < objects.Size(); ++i) {
				objects[i].Rotate(f);
			}
		}
		if (c == 'z') {
			float f;
			std::cout << "Input size modificator" << std::endl;
			std::cin >> f;
			for (i = 0; i < objects.Size(); ++i) {
				objects[i].Resize(f);
			}
		}
		if (c == 'd')
			show_debugging_info = !show_debugging_info;

		if (c == 0 || c == 224) {
			c = _getch();
			for (i = 0; i < objects.Size(); ++i) {
				switch (c) {
				case 72:
					objects[i].Move(0, -10);
					break;
				case 80:
					objects[i].Move(0, 10);
					break;
				case 75:
					objects[i].Move(-10, 0);
					break;
				case 77:
					objects[i].Move(10, 0);
					break;
				default:
					break;
				}
			}
		}
	} while (c != 27);
}