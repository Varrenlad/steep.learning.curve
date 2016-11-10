#ifndef CONT
#define CONT
#include "drawable.h"

class ContourTrapezoid : public Drawable {
public:
	ContourTrapezoid(HDC &hdc, HWND hwnd);
	void Draw();
	void Setter(std::istream &st);
	void Getter(std::ostream &st);
	bool PointInside(POINT p);
	bool HasColour(COLORREF c);
	char GetType() const;
	void Move(int x, int y);
	~ContourTrapezoid();
protected:
	static void SaveC(COLORREF &cl, std::ostream &st);
	void SaveP(std::ostream &st, POINT *p) const;
	bool LoadP(std::istream &st, POINT **p) const;
	static bool LoadC(COLORREF *cl, std::istream &st);
	void BorderCheck();
	static double Signum(POINT p1, POINT p2, POINT p3);
};
#endif