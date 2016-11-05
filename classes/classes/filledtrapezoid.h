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
	bool HasColour(COLORREF c);
	char GetType() const;
protected:
	HBRUSH *CreateBrush(COLORREF color, int type);
	unsigned short int brush_type;
	COLORREF brush;
};
#endif