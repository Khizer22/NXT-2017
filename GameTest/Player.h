#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
//-----------------------------
#include "App\app.h"
#include "Line.h"
#include <math.h>  
//-----------------------------

class Player {

public:
	Player(float baseLength, float height, float r, float g, float b);
	~Player();

	//Get Values
	float GetPosX();
	float GetPosY();
	float GetMaxSpeed();
	float GetLength();
	float GetHeight();
	float GetCurrentSpeed();

	//Set Values
	void SetCurrentSpeedX(float speed);
	void SetCurrentSpeedY(float speed);

	//Colour
	void SetColour(float r, float g, float b);

	//Render
	void DrawPlayer();
	bool drawBoostLines;

	//Controls
	void Movement();

	void ComputeCollision(float bodyX,float bodyY);

	//Stats
	float currentSpeedX, currentSpeedY;
	float currentArmor;
	float currentFuel;

	//Damage
	void Damage(float damageAmount);
	bool isDead;

	//Victory
	int victory;

	//GameMode
	int gameMode;
private:
	//Stats
	float x;
	float y;
	float baseLength;
	float height;
	float maxArmor;
	float maxFuel;

	float r;
	float g;
	float b;
	
	bool moving;
	float maxSpeed;
	float accX, accY;
	float turnSpeed;

	Line leftWing;
	Line rightWing;
	Line baseWing;
	Line boostLine1;
	Line boostLine2;
	Line boostLine3;
	float angle;

	float moveTowardsX;
	float moveTowardsY;
};
#endif