#ifndef DRAW
#define DRAW
#include "commondata.h"

class Drawable {
public:
	Drawable(int input, HDC hdc_i);
	virtual char GetType() const = 0;
	virtual void Draw() = 0;
	virtual void Setter(std::istream &st) = 0;
	void Move(int x, int y);
	virtual void Getter(std::ostream &st) = 0;
	virtual bool PointInside(POINT p) = 0;
	virtual bool HasColour(COLORREF c) = 0;
	virtual ~Drawable();
protected:
	POINT *points;
	HDC hdc;
	int count_of_p;
	int pen_width;
	HPEN basePen;
	HBRUSH baseBrush;
	HWND hwnd_i;
};
#endif