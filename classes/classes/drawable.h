#ifndef DRAW
#define DRAW
#include "commondata.h"

class Drawable {
public:
	Drawable(int input, HDC hdc_i);
	virtual char GetType() const = 0;
	virtual void Draw() = 0;
	virtual void Setter(std::istream &st) = 0;
	virtual void Move(int x, int y) = 0;
	virtual void Getter(std::ostream &st) = 0;
	virtual bool PointInside(POINT p) = 0;
	virtual bool HasColour(COLORREF c) = 0;
	Drawable(const Drawable& that) = delete;
	virtual ~Drawable();
protected:
	POINT *points;
	HDC hdc;
	size_t count_of_p;
	HPEN basePen;
	COLORREF pen;
	unsigned short int pen_type;
	unsigned short int pen_width;
	HWND hwnd_i;
};
#endif