#include <fstream>
#include "../../steep.learning.curve/the_classes.h"
HBRUSH CreateBrush(colour cBrush, int type);

HBRUSH CreateBrush(COLORREF color, int type) {
	HBRUSH *retval = new HBRUSH;
	if (!type)
		*retval = CreateSolidBrush(color);
	else
		*retval = CreateHatchBrush(type, color);
	return *retval;
}

int main() {
	return 0;
}