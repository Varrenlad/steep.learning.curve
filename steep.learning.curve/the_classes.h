#pragma once
#define EXCEPTION_OUT_OF_BORDER 1
#define EXCEPTION_READ_FAULT 2
#define EXCEPTION_WRONG_VALUES 3
#define EXCEPTION_WRITE_FAIL 4

HBRUSH CreateBrush(COLORREF color, int type);

HBRUSH CreateBrush(COLORREF color, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(color);
	else
		*retval = CreateHatchBrush(type, color);
	return *retval;
}

///Abstract class for everything
class Drawable {
public:
	Drawable(int input, HDC hdc_i) {
		points = new POINT[input];
		hdc = hdc_i;
		count_of_p = input;
		basePen = CreatePen(1, 1, RGB(0, 0, 0));
	}
	virtual void Draw() = 0;
	virtual void Setter(std::ifstream &st) = 0;
	void Move(int x, int y) {
		int i;
		for (i = 0; i < count_of_p; ++i) {
			points[i].x += x;
			points[i].y += y;
		}
	}
	virtual void Getter(std::ofstream &st) = 0;
	~Drawable() {
		delete[] points;
		count_of_p = 0;
	}
protected:
	POINT *points;
	HDC hdc;
	int count_of_p;
	int type_of_task;
	int pen_width;
	HPEN basePen;
	HBRUSH baseBrush;
	HWND hwnd_i;
};

class Background : public Drawable {
public:
	Background(HDC &hdc, HWND hwnd) : Drawable(2, hdc)
	{
		hwnd_i = hwnd;
	};
	void Draw() {
		Update(hwnd_i);
		baseBrush = CreateSolidBrush(bgc);
		SelectBrush(hdc, baseBrush);
		Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
		DeleteBrush(baseBrush);
	}
	void Setter(std::ifstream &st) {
		int red, green, blue;
		st >> red >> green >> blue;
		if (red < 0   || red > 255 ||
			green < 0 || green > 255 ||
			blue < 0  || blue > 255)
			throw EXCEPTION_WRONG_VALUES;
		else bgc = RGB(red, green, blue);
	}
	void Getter(std::ofstream &st) {
		int i;
		try {
			st << (int) GetRValue(bgc) << ' ' << (int) GetGValue(bgc) 
			   << ' ' << (int) GetBValue(bgc) << '\n' << '\n';
		}
		catch (int e) {
			throw EXCEPTION_WRONG_VALUES;
		}
	}
	~Background(){ //not sure if it even starts ~Drawable
		DeleteBrush(baseBrush);
	};
private:
	void Update(HWND hwnd) {
		GetClientRect(hwnd, &rt);
		points[0].x = rt.left - 10;
		points[0].y = rt.top - 10;
		points[1].x = rt.right + 10;
		points[1].y = rt.bottom + 10;
	}
	RECT rt;
	COLORREF bgc;
};

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc, HWND hwnd) : Drawable(5, hdc){
		hwnd_i = hwnd;
	};
	void Draw() {
		try {
			BorderCheck();
		}
		catch(int e) {
			if (e == EXCEPTION_OUT_OF_BORDER)
				throw e;
		}
		SelectPen(hdc, basePen);
		Polyline(hdc, points, 5);
		DeletePen(basePen);
	}
	void Setter(std::ifstream &st) { ///Four points, no less
		int i;
		st >> pen_type >> pen_width;
		int red, green, blue;
		st >> red >> green >> blue;
		if (red < 0 || red > 255 ||
			green < 0 || green > 255 ||
			blue < 0 || blue > 255)
			throw EXCEPTION_READ_FAULT;
		else pen = RGB(red, green, blue);
		for (i = 0; i < count_of_p - 1; ++i) {
			st >> points[i].x >> points[i].y;
		}
		points[4] = points[0];
		basePen = CreatePen(pen_type, pen_width, pen);
	}
	void Getter(std::ofstream &st) {
		int i;
		try {
			st << pen_type << ' ' << pen_width << '\n';
			st.flush();
			st << (int) GetRValue(pen) << ' ' << (int) GetGValue(pen) << ' ' 
			   << (int) GetBValue(pen) << '\n';
			st.flush();
			for (i = 0; i < count_of_p - 1; ++i) {
				st << points[i].x << ' ' << points[i].y << '\n';
				st.flush();
			}
		}
		catch (int e) {
			throw e;
		}
	}
private:
	int BorderCheck() {
		RECT rt;
		int i, j;
		GetClientRect(hwnd_i, &rt);
		for (i = 0; i < count_of_p; ++i) {
			if (points[i].x < 0 || points[i].x > rt.right ||
				points[i].y < 0 || points[i].y > rt.bottom)
				throw EXCEPTION_OUT_OF_BORDER;
		}
	}
	int pen_type = 0;
	COLORREF pen;
};

class FilledTrapezoid : public Drawable {
public:
	FilledTrapezoid(HDC &hdc, HWND hwnd) : Drawable(4, hdc){
		hwnd_i = hwnd;
	};
	void Draw() {
		try {
			BorderCheck();
		}
		catch (int e) {
			if (e == EXCEPTION_OUT_OF_BORDER)
				throw e;
		}
		SelectPen(hdc, basePen);
		SelectBrush(hdc, baseBrush);
		Polygon(hdc, points, 4);
		//DeletePen(basePen);
		//DeleteBrush(baseBrush);
	}
	void Setter(std::ifstream &st) { ///Four points, no less
		int i, r, g, b;
		st >> pen_type >> pen_width >> brush_type;
		st >> r >> g >> b;
		pen = RGB(r, g, b);
		st >> r >> g >> b;
		brush = RGB(r, g, b);
		for (i = 0; i < count_of_p; ++i) {
			st >> points[i].x >> points[i].y;
		}
		basePen = CreatePen(pen_type, pen_width, pen);
		baseBrush = CreateBrush(brush, brush_type);
	}
	void Getter(std::ofstream &st) {
		int i;
		try {
			st << pen_type << ' ' << pen_width << ' ' << brush_type << '\n';
			st << (int) GetRValue(pen) << ' ' << (int) GetGValue(pen) << ' ' 
			   << (int) GetBValue(pen) << '\n';
			st << (int) GetRValue(brush) << ' ' << (int) GetGValue(brush) << ' ' 
			   << (int) GetBValue(brush) << '\n';
			for (i = 0; i < count_of_p; ++i) {
				st << points[i].x << ' ' << points[i].y << '\n';
			}
			st << '\n';
		}
		catch (int e) {
			throw;
		}
	}
	void Draw(FilledTrapezoid &ft) { 
		int i;
		for (i = 0; i < count_of_p; ++i) {
			if ((GetPixel(hdc, points[i].x, points[i].y) != ft.GetPenColour()) &&
				(GetPixel(hdc, points[i].x, points[i].y) != ft.GetBrushColour()))
				throw EXCEPTION_WRONG_VALUES;
		}
		this->Draw();
	}
	COLORREF GetPenColour() {
		return pen;
	}
	COLORREF GetBrushColour() {
		return brush;
	}
private:
	int BorderCheck() {
		RECT rt;
		int i, j;
		GetClientRect(hwnd_i, &rt);
		for (i = 0; i < count_of_p; ++i) {
			if (points[i].x < 0 || points[i].x > rt.right ||
				points[i].y < 0 || points[i].y > rt.bottom)
				throw EXCEPTION_OUT_OF_BORDER;
		}
	}
	int pen_type = 0;
	int brush_type = 0;
	COLORREF pen;
	COLORREF brush;
};