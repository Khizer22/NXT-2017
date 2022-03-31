#include "stdafx.h"
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {
	isVisible = true;
	isTrigger = false;
	isStatic = true;
	ID = 1;
	r = 1;
	g = 1;
	b = 1;
	
	//TEMP
	size = 0;
	virtualX = 0;
	virtualY = 0;
	hitID = 0;
	wootWin = false;
}
PhysicsBody::~PhysicsBody() {

}

void PhysicsBody::CreateBody(float _x, float _y, float _length, float _height ,int _ID) {
	ID = _ID;
	x = _x;
	y = _y;
	startingX = x;
	startingY = y;
	length = _length;
	height = _height;

	/*
	if (_ID < 5) {
		//Origin Point at Top-Left
		wallLeft.SetLines(0, 0, 0, -(height));
		wallRight.SetLines(length, 0, length, -height);
		wallTop.SetLines(0, 0, length, 0);
		wallBottom.SetLines(0, -height, length, -height);
	}
	else
	{
		//Origin point in Center
		wallLeft.SetLines(-(length / 2), -(height / 2), -(length / 2), height / 2);
		wallRight.SetLines(length / 2, -(height / 2), length / 2, height / 2);
		wallTop.SetLines(-(length / 2), height / 2, length / 2, height / 2);
		wallBottom.SetLines(-(length / 2), -(height / 2), length / 2, -(height / 2));
	}	
	*/

	wallLeft.SetLines(-(length / 2), -(height / 2), -(length / 2), height / 2);
	wallRight.SetLines(length / 2, -(height / 2), length / 2, height / 2);
	wallTop.SetLines(-(length / 2), height / 2, length / 2, height / 2);
	wallBottom.SetLines(-(length / 2), -(height / 2), length / 2, -(height / 2));

	if (ID == 5)
	{
		isTrigger = true;
	}
}

void PhysicsBody::BackgroundMovement(float playerX, float playerY) {
	if (ID < 6 || ID == 10) {
		x = -playerX + startingX;
		y = -playerY + startingY;
	}
	else if (ID == 6)
	{
		x = APP_VIRTUAL_WIDTH/2;
		y = APP_VIRTUAL_HEIGHT/2;

		virtualX = playerX;
		virtualY = playerY;
	}
}

void PhysicsBody::Collision(std::vector<PhysicsBody> bodies, float* currentMoveSpeedX,float* currentMoveSpeedY,float* playerArmor,float* playerFuel,int* playerVictory) {
	size = bodies.size();

	if (!isStatic) {
		for (int i = 0; i < size; i++) {
			if (x + length / 2 > bodies.at(i).x - bodies.at(i).length / 2
				&& x - length / 2 < bodies.at(i).x + bodies.at(i).length / 2
				&& y + height / 2 > bodies.at(i).y - bodies.at(i).height / 2
				&& y - height / 2 < bodies.at(i).y + bodies.at(i).height / 2
				&& bodies.at(i).isTrigger == false
				)				
				{				
					if (bodies.at(i).ID == 1) {
						virtualX += 10;
						*currentMoveSpeedX = -*currentMoveSpeedX/2;
						*playerArmor -= abs(*currentMoveSpeedX * 2);
						App::PlaySoundW("sounds/hurt.wav", false);
					}
					else if (bodies.at(i).ID == 2)
					{
						virtualX -= 10;
						*currentMoveSpeedX = -*currentMoveSpeedX/2;
						*playerArmor -= abs(*currentMoveSpeedX * 2);
						App::PlaySoundW("sounds/hurt.wav", false);
					}
					else if (bodies.at(i).ID == 3)
					{
						virtualY -= 10;
						*currentMoveSpeedY = -*currentMoveSpeedY/2;
						*playerArmor -= abs(*currentMoveSpeedY * 2);
						App::PlaySoundW("sounds/hurt.wav", false);
					}
					else if (bodies.at(i).ID == 4)
					{
						virtualY += 10;
						*currentMoveSpeedY = -*currentMoveSpeedY/2;	
						*playerArmor -= abs(*currentMoveSpeedY * 2);
						App::PlaySoundW("sounds/hurt.wav", false);
					}
					else if (bodies.at(i).ID == -1)
					{
						//Add Fuel
						bodies.at(i).isTrigger = true;    //<<wont work because it is not a direct reference =(
						bodies.at(i).isVisible = false;
						bodies.at(i).SetColour(1,0.1f, 0.1f);
						if (*playerFuel < 300)
							*playerFuel += 50;
					}
					else if (bodies.at(i).ID == 10)
					{
						if (!wootWin) {
							//Victory
							*currentMoveSpeedY = 0;
							*currentMoveSpeedY = 0;
							App::PlaySoundW("sounds/win2.wav", false);
							App::PlaySoundW("sounds/win.wav", false);
							*playerVictory = 1;
						}
						wootWin = true;
					}
					else if (bodies.at(i).ID == -9)
					{
						//Asteroids
						*currentMoveSpeedX -= 1;
						*currentMoveSpeedY -= 1;
						*playerArmor -= 2;
						if (*playerArmor > 0)
							App::PlaySoundW("sounds/hurt.wav", false);
					}
				}
		}
	}	
}

void PhysicsBody::DrawBody() {
	if (isVisible) {
		App::DrawLine(wallLeft.x1 + x, wallLeft.y1 + y, wallLeft.x2 + x, wallLeft.y2 + y,r,g,b);
		App::DrawLine(wallRight.x1 + x, wallRight.y1 + y, wallRight.x2 + x, wallRight.y2 + y, r, g, b);
		App::DrawLine(wallTop.x1 + x, wallTop.y1 + y, wallTop.x2 + x, wallTop.y2 + y, r, g, b);
		App::DrawLine(wallBottom.x1 + x, wallBottom.y1 + y, wallBottom.x2 + x, wallBottom.y2 + y, r, g, b);
	}
}

void PhysicsBody::SetCoordinates(float _x, float _y) {
	x = _x;
	y = _y;
	startingX = x;
	startingY = y;
}

float PhysicsBody::GetPosX() {
	return x;
}
float PhysicsBody::GetPosY() {
	return y;
}

float PhysicsBody::GetLength() {
	return length;
}

float PhysicsBody::GetHeight() {
	return height;
}

void PhysicsBody::SetID(int _ID) {
	ID = _ID;
}

void PhysicsBody::SetStatic(bool _isStatic) {
	isStatic = _isStatic;
}

void PhysicsBody::SetColour(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
}