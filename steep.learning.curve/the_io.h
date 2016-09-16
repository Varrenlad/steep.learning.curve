#pragma once
#include "the_include.h"
int validate_trapeze(trapeze t, RECT rt);
int validate_trapeze(trapeze inner, trapeze outer);
int validate_colour(colour c); 
int validate_input(trapeze t, colour cBGColour, colour cTrapezeColour, RECT rt);
int validate_input(trapeze outer, trapeze inner, colour cTrapezeColour,
					colour cBGColour, RECT rt);
int  get_type(FILE *fp);
void get_data(FILE *fp, trapeze *t, colour *cTrapezeColour, colour *cBGColour);
void get_data(FILE *fp, trapeze *outer, trapeze *inner, colour *cTrapezeColour, 
					colour *cBGColour);


int validate_trapeze(trapeze t, RECT rt) {
	if (rt.right < t.A[0] || t.A[0] < 0)
		return 0;
	if (rt.right < t.B[0] || t.B[0] < 0)
		return 0;
	if (rt.right < t.C[0] || t.C[0] < 0)
		return 0;
	if (rt.right < t.D[0] || t.D[0] < 0)
		return 0;
	if (rt.bottom < t.A[1] || t.A[1] < 0)
		return 0;
	if (rt.bottom < t.B[1] || t.B[1] < 0)
		return 0;
	if (rt.bottom < t.C[1] || t.C[1] < 0)
		return 0;
	if (rt.bottom < t.D[1] || t.D[1] < 0)
		return 0;
	if (t.C[1] - t.D[1] != t.B[1] - t.A[1]) //check parallel top and bottom bars
		return 0;
	if (t.B[0] < t.A[0] && t.C[0] > t.D[0] ||
		t.B[0] > t.A[0] && t.C[0] < t.D[0]) //wrong placed x i
		return 0;
	//Sumfin else?
	return 1;
}

int validate_trapeze(trapeze inner, trapeze outer) {
	if (inner.A[0] > outer.A[0])
		return 0;
	if (inner.A[1] > outer.A[1])
		return 0;
	if (inner.B[0] > outer.B[0])
		return 0;
	if (inner.B[1] > outer.B[1])
		return 0;
	if (inner.C[0] > outer.C[0])
		return 0;
	if (inner.C[1] > outer.C[1])
		return 0;
	if (inner.D[0] > outer.D[0])
		return 0;
	if (inner.D[1] > outer.D[1])
		return 0;
	return 1;
}

int validate_colour(colour c) {
	if (c.blue < 0 || c.blue > 255)
		return 0;
	if (c.green < 0 || c.green > 255)
		return 0;
	if (c.red < 0 || c.red > 255)
		return 0;
	return 1;
}

//For contoured and filled
int validate_input(trapeze t, colour cBGColour, colour cTrapezeColour, RECT rt) {
	if (!validate_trapeze(t, rt) || !validate_colour(cBGColour) || 
		!validate_colour(cTrapezeColour))
		return 0;
	return 1;
}

//For cut
int validate_input(trapeze outer, trapeze inner, colour cTrapezeColour, 
				colour cBGColour, RECT rt) {
	if (!validate_trapeze(outer, rt) || !validate_trapeze(inner, rt) ||
		!validate_colour(cBGColour) || !validate_colour(cTrapezeColour) ||
		!validate_trapeze(inner, outer))
		return 0;
	return 1;
}

int get_type(FILE *fp) {
	int i;
	fscanf(fp, "%d", &i);
	return i;
}

void get_data(FILE *fp, trapeze *t, colour *cTrapezeColour, colour *cBGColour) {
	fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&(t->A[0]), &(t->A[1]), &(t->B[0]), &(t->B[1]),
		&(t->C[0]), &(t->C[1]), &(t->D[0]), &(t->D[1]),
		&(cTrapezeColour->red), &(cTrapezeColour->green), &(cTrapezeColour->blue),
		&(cBGColour->red), &(cBGColour->green), &(cBGColour->blue));
}

void get_data(FILE *fp, trapeze *outer, trapeze *inner, colour *cTrapezeColour, 
				colour *cBGColour) {
	fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&(inner->A[0]), &(inner->A[1]), &(inner->B[0]), &(inner->B[1]),
		&(inner->C[0]), &(inner->C[1]), &(inner->D[0]), &(inner->D[1]),
		&(outer->A[0]), &(outer->A[1]), &(outer->B[0]), &(outer->B[1]),
		&(outer->C[0]), &(outer->C[1]), &(outer->D[0]), &(outer->D[1]),
		&(cTrapezeColour->red), &(cTrapezeColour->green), &(cTrapezeColour->blue),
		&(cBGColour->red), &(cBGColour->green), &(cBGColour->blue));
}