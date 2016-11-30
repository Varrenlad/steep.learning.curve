#ifndef PTRAP
#define PTRAP
#include "background.h"
#include "filledtrapezoid.h"
#include "filledtrapezoid_proxified.h"

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
	void Resize(float new_size);
	void Rotate(float angle);
private:
	FilledTrapezoid *inner;
	FilledTrapezoid_Proxy *proxy;
};
#endif