#include "stdafx.h"
#include "Line.h"

Line::Line(float _x1,float _y1,float _x2,float _y2) {

	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;

}

Line::Line() {
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

Line::~Line() {}

void Line::SetLines(float _x1, float _y1, float _x2, float _y2) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}

void Line::SetColour(float _r, float _g, float _b) {
	r = _r;
	g = _g; 
	b = _b;

}