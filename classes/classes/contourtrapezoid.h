#ifndef CONT
#define CONT
#include "drawable.h"

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::ifstream &st);
	void Getter(std::ofstream &st);
	~ContourTrapezoid();
private:
	void BorderCheck();
	int pen_type = 0;
	COLORREF pen;
};
#endif