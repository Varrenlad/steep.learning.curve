#pragma once
#include "the_include.h"
int validate_trapeze(trapeze);
int validate_trapeze(trapeze, trapeze);
int validate_colour(colour); 
int validate_input(trapeze, colour, colour);
int validate_input(trapeze, colour, colour, colour);
int validate_input(trapeze, trapeze, colour, colour, colour, colour);
int get_type(FILE *);
int validate_type(int);
int get_data(FILE *, trapeze *, colour *, colour *);
int get_data(FILE *, trapeze *, colour *, colour *,
					colour *);
int get_data(FILE *, trapeze *, trapeze *, colour *, 
					colour *, colour *, colour *);


int validate_trapeze(trapeze t) {
	if (t.C[1] - t.D[1] != 0 && t.A[1] - t.B[1] != 0) {
		if (((t.C[0] - t.D[0]) / (t.C[1] - t.D[1])) !=
			((t.A[0] - t.B[0]) / (t.A[1] - t.B[1]))) //check if slopes are equal
			return 1;
	}
	if (t.B[0] < t.A[0] && t.C[0] > t.D[0] ||
		t.B[0] > t.A[0] && t.C[0] < t.D[0]) //wrong placed x i
		return 1;
	//Sumfin else?
	return 0;
}

int validate_trapeze(trapeze inner, trapeze outer) {
	if (inner.A[0] > outer.A[0] ||
		inner.A[1] < outer.A[1] ||
		inner.B[0] < outer.B[0] ||
		inner.B[1] < outer.B[1] ||
		inner.C[0] < outer.C[0] ||
		inner.C[1] > outer.C[1] ||
		inner.D[0] > outer.D[0] ||
		inner.D[1] > outer.D[1])
		return 1;
	return 0;
}

int validate_colour(colour c) {
	if (c.blue  < 0 || c.blue  > 255 ||
		c.green < 0 || c.green > 255 ||
		c.red   < 0 || c.red   > 255)
		return 1;
	return 0;
}

//For contoured
int validate_input(trapeze t, colour cBG, colour cTrapeze) {
	if (validate_trapeze(t)  || 
		validate_colour(cBG) || 
		validate_colour(cTrapeze))
		return 1;
	return 0;
}

//For filled
int validate_input(trapeze t, colour cBG, colour cBrush, colour cPen) {
	if (validate_trapeze(t)   || validate_colour(cBG) ||
		validate_colour(cPen) || validate_colour(cBrush))
		return 1;
	return 0;
}

//For cut
int validate_input(trapeze outer, trapeze inner, colour cTrapeze, 
				colour cBG, colour cPen1, colour cPen2) {
	if (validate_trapeze(outer) || validate_trapeze(inner)   ||
		validate_colour(cBG)    || validate_colour(cTrapeze) ||
		validate_colour(cPen1)  || validate_colour(cPen2)    ||
		validate_trapeze(inner, outer))
		return 1;
	return 0;
}

int validate_type(int type) {
	if (type > 7 || type < 0)
		return 1;
	return 0;
}

void get_colour(FILE *fp, colour *cModify) {
	fscanf(fp, "%d%d%d", &(cModify->red), &(cModify->green), &(cModify->blue));
}

void get_coords(FILE *fp, trapeze *t) {
	fscanf(fp, "%d%d%d%d%d%d%d%d", &(t->A[0]), &(t->A[1]), &(t->B[0]), &(t->B[1]),
		&(t->C[0]), &(t->C[1]), &(t->D[0]), &(t->D[1]));
}

int get_type(FILE *fp) {
	int i;
	fscanf(fp, "%d", &i);
	return i;
}

int get_data(FILE *fp, trapeze *t, colour *cPen, colour *cBG) {
	get_colour(fp, cBG);
	get_colour(fp, cPen);
	get_coords(fp, t);
	if (validate_input(*t, *cBG, *cPen))
		return 1;
	return 0;
}

int get_data(FILE *fp, trapeze *t, colour *cPen, colour *cBG, 
					colour *cBrush) {
	get_colour(fp, cBG);
	get_colour(fp, cPen);
	get_colour(fp, cBrush);
	get_coords(fp, t);
	if (validate_input(*t, *cBG, *cBrush, *cPen))
		return 1;
	return 0;
}

int get_data(FILE *fp, trapeze *outer, trapeze *inner, colour *cBG,
					colour *cBrush, colour *cPenOuter, colour *cPenInner){
	get_colour(fp, cBG);
	get_colour(fp, cPenOuter);
	get_colour(fp, cPenInner);
	get_colour(fp, cBrush);
	get_coords(fp, outer);
	get_coords(fp, inner);
	if (validate_input(*outer, *inner, *cBG, *cBrush, *cPenOuter, *cPenInner))
		return 1;
	return 0;
}