#include "container.h"
#define INPUT_FILE "input.txt"

void draw(Container<Drawable> &objects, HDC hdc);

int main() {
	char filename[FILENAME_MAX];
	std::ifstream ifstr;
	std::ofstream ofstr;
	Container<Drawable> objects;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	unsigned int i, type;
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
#ifdef LEGACY_LOAD
	Background *bg = new Background(hdc, hwnd);
	ifstr >> type;
	objects.Push(bg);
	switch (type) {
	case 1: {	
	ContourTrapezoid *t = new ContourTrapezoid(hdc, hwnd);
	objects.Push(t);
	break; 
	}
	case 2: {
	FilledTrapezoid *t = new FilledTrapezoid(hdc, hwnd);
	objects.Push(t);
	break; 
	}
	case 3:	{
	PartialTrapezoid *t = new PartialTrapezoid(hdc, hwnd);
	objects.Push(t);
	break; 
	}
	default:
		TextOutA(hdc, 0, 0, "Couldn't find type specializer, aborting", 41);
		getchar();
		exit(-1);
	}
#endif
#ifndef LEGACY_LOAD
	objects.Load(ifstr, hdc, hwnd);
#else
	for (i = 0; i < objects.Size(); ++i) {
		try {
			objects[i].Setter(ifstr);
		}
		catch (int e) {
			switch (e) {
			case EXC_BG_VL_WRONG:
				TextOutA(hdc, 0, 0, "Wrong background colour data", 29);
				break;
			case EXC_C_TR_VL_WRONG:
				TextOutA(hdc, 0, 0, "Wrong contour trapezoid data", 29);
				break;
			case EXC_F_TR_VL_WRONG:
				TextOutA(hdc, 0, 0, "Wrong filled trapezoid data", 28);
				break;
			case EXC_P_TR_VL_WRONG:
				TextOutA(hdc, 0, 0, "Wrong partial trapezoid data", 29);
				break;
			default:
				TextOutA(hdc, 0, 0, "Unknown error while loading", 28);
				break;
			}
			getchar();
			exit(-1);
		}
	}
#endif
	ifstr.sync();
	ifstr.close();
	draw(objects, hdc);
	ofstr.open(filename, std::ofstream::out);
	TextOutA(hdc, 0, 0, "Do you want to save current data? Y/n\n", 39);
	i = getchar();
	if (i != 'n' || i != 'N') {
		try {
			objects.Save(ofstr);
		}
		catch (int e) {
			if (e == EXC_WR_FAIL)
				TextOutA(hdc, 0, 0, "Unable to write data to file", 29);
			else
				TextOutA(hdc, 0, 0, "Unknown error while saving data", 32);
		}
	}
	ofstr.close();
	return 0;
}

void draw(Container<Drawable> &objects, HDC hdc) {
	unsigned int c, i;
	do {
		for (i = 0; i < objects.Size(); ++i) {
			try {
				objects.Draw(i);
			}
			catch (int e) {
				if (e == EXC_OOB)
					TextOutA(hdc, 0, 0, "Unable to draw: window is too small", 36);
				else if (e == EXC_P_TR_VL_WRONG)
					TextOutA(hdc, 0, 16, "Couldn't draw inner trapezoid", 30);
				else TextOutA(hdc, 0, 32, "Unknown exception while drawing objects", 40);
				}
			}
		c = _getch();
		if (c == 0 || c == 224) {
			c = _getch();
			for (i = 0; i < objects.Size(); ++i) {
				if (objects[i].GetType() != 'b')
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

/*int main() {
	int pos = 0;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	Container<Drawable> ctr;
	while (pos != 9) {
		std::cout
			<< "1. Add element\n"
			<< "2. Remove element\n"
			<< "3. Show container\n"
			<< "4. Search figures by color\n"
			<< "5. Search figures by point\n"
			<< "6. Load data from file\n"
			<< "7. Save data to file\n"
			<< "8. Draw element\n"
			<< "9. Exit\n";
		pos = 0;
		std::cin >> pos;
		switch (pos) {
		case 1: {
			std::cout
				<< "1. Add ""Background"" type\n"
				<< "2. Add ""Contoured Trapezoid"" type\n"
				<< "3. Add ""Filled Trapezoid"" type\n"
				<< "4. Add ""Partial Trapezoid"" type\n";
			std::cin >> pos;
			int place = 0;
			std::cout
				<< "1. Push to front\n"
				<< "2. Push to back\n";
			std::cin >> place;
			switch (pos) {
			case 1: {
				std::cout 
					<< "Setter syntax is:\n"
					<< "red green blue\n";
				Background *obj = new Background(hdc, hwnd);
				obj->Setter(std::cin);
				if (place == 1)
					ctr.Push(obj);
				if (place == 2)
					ctr.FrontPush(obj);
				break;
			}
			case 2: {
				std::cout
					<< "Setter syntax is:\n"
					<< "pen_type pen_width\n"
					<< "r g b\n"
					<< "A.x A.y B.x B.y\n"
					<< "C.x C.y D.x D.y\n";
				ContourTrapezoid *obj = new ContourTrapezoid(hdc, hwnd);
				obj->Setter(std::cin);
				if (place == 1)
					ctr.Push(obj);
				if (place == 2)
					ctr.FrontPush(obj);
				break;
			}
			case 3: {
				FilledTrapezoid *obj = new FilledTrapezoid(hdc, hwnd);
				std::cout
					<< "Setter syntax is:\n"
					<< "pen_type pen_width brush_type\n"
					<< "r g b for pen\n"
					<< "r g b for brush\n"
					<< "A.x A.y B.x B.y\n"
					<< "C.x C.y D.x D.y\n";
				obj->Setter(std::cin);
				if (place == 1)
					ctr.Push(obj);
				if (place == 2)
					ctr.FrontPush(obj);
				break;
			}
			case 4: {
				PartialTrapezoid *obj = new PartialTrapezoid(hdc, hwnd);
				std::cout
					<< "Setter syntax is:\n"
					<< "pen_type pen_width brush_type\n"
					<< "r g b for pen\n"
					<< "r g b for brush\n"
					<< "A.x A.y B.x B.y\n"
					<< "C.x C.y D.x D.y\n";
				obj->Setter(std::cin);
				if (place == 1)
					ctr.Push(obj);
				if (place == 2)
					ctr.FrontPush(obj);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2: {
			pos = 0;
			std::cout
				<< "1. Show last element\n"
				<< "2. Remove last element\n";
			std::cin >> pos;
			switch (pos) {
			case 1:
				ctr.Pop().Getter(std::cout);
				break;
			case 2:
				ctr.PopRem()->Getter(std::cout);
				break;
			default:
				break;
			}
			break;
		}
		case 3: {
			pos = 0;
			std::cout
				<< "1. Show list forwards\n"
				<< "2. Show list backwards\n";
			std::cin >> pos;
			switch (pos) {
			case 1:
				ctr.Show(false);
				break;
			case 2:
				ctr.Show(true);
				break;
			default:
				break;
				}
			break;
		}
		case 4: {
			int r, g, b;
			std::cout << "Enter red green and blue components\n";
			std::cin >> r >> g >> b;
			list *t, *l = ctr.Search(RGB(r, g, b));
			t = l;
			while (t != nullptr) {
				std::cout << t->i;
				t = t->next;
			}
			t = l;
			while (t != nullptr) {
				l = t->next;
				delete t;
				t = l;
			}
			delete t;
			break;
		}
		case 5: {
			POINT p;
			std::cout << "Enter X and Y coordinates\n";
			std::cin >> p.x, p.y;
			list *t, *l = ctr.Search(p);
			t = l;
			while (t != nullptr) {
				std::cout << t->i;
				t = t->next;
			}
			t = l;
			while (t != nullptr) {
				l = t->next;
				delete t;
				t = l;
			}
			delete t;
			break;
		}
		case 6: {
			std::ifstream st;
			char name[FILENAME_MAX];
			std::cin >> name;
			st.open(name, std::ifstream::in);
			if (!(st.rdstate() & std::ios::failbit)) {
				ctr.Load(st, hdc, hwnd);
			}
			break;
		}
		case 7: {
			std::ofstream st;
			char name[FILENAME_MAX];
			std::cin >> name;
			st.open(name, std::ifstream::out);
			if (!(st.rdstate() & std::ios::failbit)) {
				ctr.Save(st);
			}
			break;
		}
		case 8: {
			pos = 0;
			std::cout << "Enter numeral to draw\n";
			std::cin >> pos;
			system("cls");
			//RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		//	UpdateWindow(hwnd);
			ctr.Draw(pos);
			std::cin.get();
			std::cin.get();
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		}
		default:
			break;
		}
	}
	return 0;
}*/