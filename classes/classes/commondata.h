#pragma once

struct list {
	int i;
	list *next = nullptr;
};

#define EXC_BG_VL_WRONG 0
#define EXC_C_TR_VL_WRONG 1
#define EXC_F_TR_VL_WRONG 2
#define EXC_OOB 3
#define EXC_RD_ERR 4
#define EXC_WR_FAIL 5
#define EXC_NOT_IN_DC 6

#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <windowsx.h>