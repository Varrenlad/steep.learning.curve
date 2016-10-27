#ifndef FUNC
#define FUNC
#include "commondata.h"

extern HBRUSH *CreateBrush(COLORREF color, int type);

HBRUSH *CreateBrush(COLORREF color, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(color);
	else
		*retval = CreateHatchBrush(type, color);
	return retval;
}
#endif