#ifndef CDAT
#define CDAT

#define TYPES

#define EXC_BG_VL_WRONG 0
#define EXC_C_TR_VL_WRONG 1
#define EXC_F_TR_VL_WRONG 2
#define EXC_OOB 3
#define EXC_RD_ERR 4
#define EXC_WR_FAIL 5
#define EXC_NOT_IN_DC 6
#define EXC_CANT_CONTAIN 7
#define EXC_P_TR_VL_WRONG 8

//#define CONT_W

#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <windowsx.h>
#include <cstdlib>
#include <cstdarg>

struct list {
	int i;
	list *next = nullptr;
};

#endif