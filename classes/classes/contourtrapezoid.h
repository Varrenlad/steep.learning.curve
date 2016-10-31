#ifndef CONT
#define CONT
#include "drawable.h"

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool PointInside(POINT p);
	bool HasColour(COLORREF c);
	char GetType() const;
	~ContourTrapezoid();
protected:
	bool IsCorrect(POINT *points) const;
	void BorderCheck();
	int pen_type;
	COLORREF pen;
	static float Signum(POINT p1, POINT p2, POINT p3);
};
#endif