#ifndef BG
#define BG
#include "drawable.h"

class Background : public Drawable {
public:
	Background(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::ifstream &st);
	void Getter(std::ofstream &st);
	~Background();
private:
	void Update(HWND hwnd);
	RECT rt;
	COLORREF bgc;
};
#endif