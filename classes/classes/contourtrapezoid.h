#ifndef CONT
#define CONT
#include "drawable.h"

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	~ContourTrapezoid();
private:
	void BorderCheck();
	int pen_type;
	COLORREF pen;
};
#endif