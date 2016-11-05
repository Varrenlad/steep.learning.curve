#ifndef PTRAP
#define PTRAP
#include "background.h"
#include "filledtrapezoid.h"

class PartialTrapezoid : public FilledTrapezoid {
public:
	PartialTrapezoid(HDC &hdc, HWND &hwnd);
	~PartialTrapezoid();
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool HasColour(COLORREF c);
	bool PointInside(POINT p);
	char GetType() const;
private:
	unsigned short int in_pen_type = 0;
	unsigned short int in_brush_type = 0;
	POINT *in_points;
	HBRUSH hbgBrush;
};
#endif