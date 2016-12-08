#ifndef CDAT
#define CDAT

#define EXC_WRONG_POINTS_R 0
#define EXC_WRONG_POINTS_T 1
#define EXC_WRITE_FAIL 2
#define EXC_READ_FAIL 3
#define EXC_OOB 4
#define EXC_CANT_CONTAIN 5
#define EXC_CORRUPT_DATA 6

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