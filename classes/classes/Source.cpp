//#include "commondata.h"
#include "container.h"
//#include "drawable.h"
#include "background.h"
//#include "contourtrapezoid.h"
//#include "filledtrapezoid.h"
#define INPUT_FILE "input.txt"
/*
void save_data(Drawable *obj, std::ofstream &ofstr);
void draw(std::vector<Drawable *> objects, HDC hdc);

int main() {
	std::ifstream ifstr;
	std::ofstream ofstr;
	std::vector<Drawable *> objects;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	unsigned int i, type;
	Background *bg = new Background(hdc, hwnd);
	ifstr.open(INPUT_FILE, std::ifstream::in);
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
			getchar();
			exit(-1);
		}
	}
	ifstr.sync();
	ifstr.close();
	ofstr.open(INPUT_FILE, std::ofstream::out);
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
	ofstr.close();
	return 0;
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
		throw;
	}
}*/

int main() {
	int pos = 0;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	Container<Drawable &> ctr;
	while (pos != 8) {
		std::cout 
			<< "1. Add element\n"
			<< "2. Remove element\n"
			<< "3. Show container\n"
			<< "4. Search figures by color\n"
			<< "5. Search figures by point\n"
			<< "6. Load data from file\n"
			<< "7. Save data to file\n"
			<< "8. Exit\n";
		pos = 0;
		std::cin >> pos;
		switch (pos) {
		case 1: {
			std::cout
				<< "1. Add ""Background"" type\n"
				<< "2. Add ""Contoured Trapezoid type\n"
				<< "3. Add ""Filled Trapezoid type\n";
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
					ctr.Push(*obj);
				if (place == 2)
					ctr.FrontPush(*obj);
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
					ctr.Push(*obj);
				if (place == 2)
					ctr.FrontPush(*obj);
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
					ctr.Push(*obj);
				if (place == 2)
					ctr.FrontPush(*obj);
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
				ctr.PopRem().Getter(std::cout);
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
			if (!st.rdstate() & std::ios::failbit) {
				ctr.Load(st);
			}
			break;
		}
		case 7: {
			std::ofstream st;
			char name[FILENAME_MAX];
			std::cin >> name;
			st.open(name, std::ifstream::out);
			if (!st.rdstate() & std::ios::failbit) {
				ctr.Save(st);
			}
			break;
		}
		default:
			break;
		}
	}
	return 0;
}