#pragma once
#include "commondata.h"
class Filled {
protected:
	HBRUSH baseBrush;
	COLORREF brush;
	HBRUSH *CreateBrush(COLORREF colour, int type);
	unsigned short int brush_type;
};