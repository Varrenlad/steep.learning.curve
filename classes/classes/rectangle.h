#pragma once
#include "drawable.h"
class _Rectangle :
	public Drawable {
public:
	_Rectangle(HDC &hdc_g, HWND &hwnd_g);
	void Draw();
	void Load(std::istream &st);
	void Save(std::ostream &st);
	char GetType() const;
	~_Rectangle();
private:
	static void SaveC(COLORREF &cl, std::ostream &st);
	void SaveP(std::ostream &st) const;
	void LoadP(std::istream &st) const;
	static bool LoadC(COLORREF *cl, std::istream &st);
};

