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
	bool PointInsideF(POINT p);
	char GetType() const;
	void Move(int x, int y);
private:
	FilledTrapezoid *inner;
};
#endif