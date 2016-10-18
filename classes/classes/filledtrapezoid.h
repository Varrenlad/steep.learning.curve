#ifndef FTRAP
#define FTRAP
#include "drawable.h"

class FilledTrapezoid : public Drawable {
public:
	FilledTrapezoid(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::ifstream &st);
	void Getter(std::ofstream &st);
	void Draw(FilledTrapezoid &ft);
	COLORREF GetPenColour();
	COLORREF GetBrushColour();
private:
	void BorderCheck();
	int pen_type = 0;
	int brush_type = 0;
	COLORREF pen;
	COLORREF brush;
};
#endif