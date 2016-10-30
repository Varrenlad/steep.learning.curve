#ifndef BG
#define BG
#include "drawable.h"

class Background : public Drawable {
public:
	Background(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool PointInside(POINT p);
	bool HasColour(COLORREF c);
	const COLORREF GetColour() const;
	~Background();
private:
	void Update(HWND hwnd);
	RECT rt;
	COLORREF bgc;
};
#endif