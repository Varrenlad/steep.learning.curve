#pragma once
#pragma warning (disable : 4996)

//#define INPUT_FILE "input_both.txt"
//#define INPUT_FILE "input_cont.txt"
#define INPUT_FILE "input_fill.txt"

struct point {
	int x;
	int y;
};

struct trapeze {
	int A[2];
	int B[2];
	int C[2];
	int D[2];
};

struct colour {
	int red;
	int green;
	int blue;
};

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include "the_draw.h"
#include "the_io.h"