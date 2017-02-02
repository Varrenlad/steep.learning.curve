#ifndef FTRAP
#define FTRAP
#include "drawable.h"

class Trapezoid : public Drawable {
public:
	Trapezoid(HDC &hdc, HWND hwnd);
	~Trapezoid();
	void Draw();
	void Load(std::istream &st);
	void CLoad(std::istream &st);
	void Save(std::ostream &st);
	char GetType() const;
private:
	static void SaveC(COLORREF &cl, std::ostream &st);
	void SaveP(std::ostream &st) const;
	void LoadP(std::istream &st) const;
	static bool LoadC(COLORREF *cl, std::istream &st);
};
#endif