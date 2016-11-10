#ifndef FTRAP
#define FTRAP
#include "contourtrapezoid.h"
#include "filled.h"

class FilledTrapezoid : public ContourTrapezoid, public Filled {
public:
	FilledTrapezoid(HDC &hdc, HWND hwnd);
	~FilledTrapezoid();
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool HasColour(COLORREF c);
	char GetType() const;
};
#endif