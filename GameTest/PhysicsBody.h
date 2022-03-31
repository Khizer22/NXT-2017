#pragma once
#ifndef _PHYSICSBODY_H_
#define _PHYSICSBODY_H_
//-----------------------------
#include "App\app.h"
#include "Line.h"
#include <vector>
#include <math.h>  
//-----------------------------

class PhysicsBody {
public:
	PhysicsBody();
	~PhysicsBody();

	void CreateBody(float x, float y, float length, float height, int ID);
	void DrawBody();
	void BackgroundMovement(float playerX,float playerY);
	void Collision(std::vector<PhysicsBody> bodies, float* currentMoveSpeedX,float* currentMoveSpeedY,float* playerArmor,float* playerFuel,int* playerVictory);
	
	//Set Values
	void SetID(int _ID);
	void SetColour(float r, float g, float b);
	void SetStatic(bool isStatic);
	void SetCoordinates(float x,float y);

	//Get Values
	float GetPosX();
	float GetPosY();
	float GetLength();
	float GetHeight();

	//Stats
	bool isVisible;
	bool isTrigger;
	bool isStatic;

	//Box Walls from Lines
	Line wallLeft;
	Line wallRight;
	Line wallTop;
	Line wallBottom;

	//Player 
	float virtualX, virtualY;
	int hitID;
	bool wootWin;
private:
	int ID;	 //1 = Left Wall, 2 = Right Wall, 3 = Top Wall, 4 = Bottom Wall, 5 = Road, 6 = Player....

	float x, y, length, height , startingX, startingY;
	float r, g, b;

	//TEST
	int size;
};


#endif
