#ifndef FTRAP
#define FTRAP
#include "contourtrapezoid.h"

class FilledTrapezoid : public ContourTrapezoid {
public:
	FilledTrapezoid(HDC &hdc, HWND hwnd);
	~FilledTrapezoid();
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	void Draw(FilledTrapezoid &ft);
	bool HasColour(COLORREF c);
	const COLORREF GetPenColour() const;
	const COLORREF GetBrushColour() const;
private:
	void BorderCheck();
	int pen_type = 0;
	int brush_type = 0;
	COLORREF brush;
};
#endif