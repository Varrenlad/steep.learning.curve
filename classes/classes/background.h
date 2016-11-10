#ifndef BG
#define BG
#include "drawable.h"
#include "filled.h"

class Background : public Drawable, public Filled {
public:
	Background(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool PointInside(POINT p);
	bool HasColour(COLORREF c);
	void Move(int x, int y);
	const COLORREF GetColour() const;
	char GetType() const;
	~Background();
private:
	void Update(HWND hwnd);
	RECT rt;
};
#endif