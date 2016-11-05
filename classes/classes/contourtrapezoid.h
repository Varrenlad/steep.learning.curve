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
	~ContourTrapezoid();
protected:
	static void SaveC(COLORREF &cl, std::ostream &st);
	void SaveP(std::ostream &st, POINT *p) const;
	bool LoadP(std::istream &st, POINT **p) const;
	static bool LoadC(COLORREF *cl, std::istream &st);
	void BorderCheck();
	unsigned short int pen_type;
	unsigned short int pen_width;
	COLORREF pen;
	static double Signum(POINT p1, POINT p2, POINT p3);
};
#endif