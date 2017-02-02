#ifndef DRAW
#define DRAW
#include "commondata.h"

class Drawable {
public:
	Drawable(int input, HDC hdc_i);
	virtual void Rotate(float angle);
	virtual void Resize(float newsize);
	virtual void ToEMF(std::string &filename);
	virtual char GetType() const = 0;
	virtual void Draw() = 0;
	virtual void Load(std::istream &st) = 0;
	virtual void CLoad(std::istream &st) = 0;
	void Move(int x, int y);
	virtual void Save(std::ostream &st) = 0;
	Drawable(const Drawable& that) = delete;
	void ModifyDC(HDC &new_dc);
	void BorderCheck();
	virtual ~Drawable();
protected:
	POINT *points;
	HDC hdc;
	size_t count_of_p;
	HPEN basePen;
	COLORREF pen;
	unsigned short int pen_type;
	unsigned short int pen_width;
	HWND hwnd;
	HBRUSH baseBrush;
	COLORREF brush;
	HBRUSH *CreateBrush(COLORREF colour, int type);
	unsigned short int brush_type;
};
#endif