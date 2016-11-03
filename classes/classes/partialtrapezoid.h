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
	const COLORREF GetPenColour() const;
	const COLORREF GetBrushColour() const;
	bool PointInside(POINT p);
	char GetType() const;
private:
	int in_pen_type = 0;
	int in_brush_type = 0;
	POINT *in_points;
	COLORREF brush;
	COLORREF bgBrush;
	HBRUSH hbgBrush;
};
#endif