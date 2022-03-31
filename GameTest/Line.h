#pragma once
#ifndef _LINE_H_
#define _LINE_H_
//-----------------------------
#include "App\app.h"
#include <math.h>  
//-----------------------------

class Line {
public:
	Line();
	Line(float x1, float y1, float x2, float y2);
	~Line();

	void SetLines(float x1, float y1, float x2, float y2);
	void SetColour(float r, float g, float b);

	float x1, x2, y1, y2, r, g, b;
private:
};

#endif