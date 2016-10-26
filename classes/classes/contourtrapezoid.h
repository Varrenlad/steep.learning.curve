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
	~ContourTrapezoid();
private:
	void BorderCheck();
	int pen_type;
protected:
	COLORREF pen;
	float Signum(POINT p1, POINT p2, POINT p3);
};
#endif