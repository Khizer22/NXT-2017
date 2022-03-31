#include "stdafx.h"
#include "Player.h"

Player::Player(float _baseLength, float _height, float _r, float _g, float _b) {
	//Init Values
	x = 0;
	y = 0;
	baseLength = _baseLength;
	height = _height;
	r = _r;
	g = _g;
	b = _b;
	gameMode = 1;

	//Stats
	maxArmor = 100;
	currentArmor = maxArmor;
	maxFuel = 100;
	currentFuel = maxFuel;
	isDead = false;
	victory = 0;

	//Movement Speed
	moving = false;
	accX = 0.1f;
	accY = 0.1f;
	maxSpeed = 10;
	currentSpeedX = 0;
	currentSpeedY = 0;
	moveTowardsX = 0;
	moveTowardsY = 0;

	//Turn Speed
	turnSpeed = 0.1f;
	angle = 0;
	
	//Effects 
	drawBoostLines = false;
}

Player::~Player() {}
	
void Player::DrawPlayer() {
	if (isDead == false) {
		//Rendering Lines 
		App::DrawLine(leftWing.x1 + APP_VIRTUAL_WIDTH / 2, leftWing.y1 + APP_VIRTUAL_HEIGHT / 2, leftWing.x2 + APP_VIRTUAL_WIDTH / 2, leftWing.y2 + APP_VIRTUAL_HEIGHT / 2, r, g, b);   //Left wing
		App::DrawLine(rightWing.x1 + APP_VIRTUAL_WIDTH / 2, rightWing.y1 + APP_VIRTUAL_HEIGHT / 2, rightWing.x2 + APP_VIRTUAL_WIDTH / 2, rightWing.y2 + APP_VIRTUAL_HEIGHT / 2, r, g, b);  //Right wing
		App::DrawLine(baseWing.x1 + APP_VIRTUAL_WIDTH / 2, baseWing.y1 + APP_VIRTUAL_HEIGHT / 2, baseWing.x2 + APP_VIRTUAL_WIDTH / 2, baseWing.y2 + APP_VIRTUAL_HEIGHT / 2, r, g, b);   //Base wing
	}

	//BoostLines
	if (drawBoostLines)
	{
		App::DrawLine(boostLine1.x1 + APP_VIRTUAL_WIDTH / 2, boostLine1.y1 + APP_VIRTUAL_HEIGHT / 2, boostLine1.x2 + APP_VIRTUAL_WIDTH / 2, boostLine1.y2 + APP_VIRTUAL_HEIGHT / 2, 1, 1, 0);   //boost Line 1
		App::DrawLine(boostLine2.x1 + APP_VIRTUAL_WIDTH / 2, boostLine2.y1 + APP_VIRTUAL_HEIGHT / 2, boostLine2.x2 + APP_VIRTUAL_WIDTH / 2, boostLine2.y2 + APP_VIRTUAL_HEIGHT / 2, 1, 1, 0);   //boost Line 2
		App::DrawLine(boostLine3.x1 + APP_VIRTUAL_WIDTH / 2, boostLine3.y1 + APP_VIRTUAL_HEIGHT / 2, boostLine3.x2 + APP_VIRTUAL_WIDTH / 2, boostLine3.y2 + APP_VIRTUAL_HEIGHT / 2, 1, 1, 0);   //boost Line 3
	}

	//UI
	char dawg[44];
	int naan = currentArmor;
	sprintf(dawg, "%d", naan);
	char paan[44] = "armor: ";
	strcat(paan, dawg);

	App::Print(350, 300, paan, 1, 1, 1);

	char dawg2[44];
	int naan2 = currentFuel;
	sprintf(dawg2, "%d", naan2);
	char paan2[44] = "Fuel: ";
	strcat(paan2, dawg2);

	App::Print(350, 350, paan2, 1, 1, 1);
}

void Player::Movement() {
	//Compute Inputs and Change Rotation
	moveTowardsX = leftWing.x2;
	moveTowardsY = leftWing.y2;
	float moveVector = sqrt(moveTowardsX * moveTowardsX + moveTowardsY * moveTowardsY);

	if (App::IsKeyPressed('D')) {
		angle -= 0.1f;
	}
	else if (App::IsKeyPressed('A')) {
		angle += 0.1f;
	}

	if (App::IsKeyPressed('W')) {
		/*
		if (sqrt(currentSpeedX * currentSpeedX + currentSpeedY * currentSpeedY) <= maxSpeed) {
			currentSpeedX += moveTowardsX / moveVector * accX;
			currentSpeedY += moveTowardsY / moveVector * accY;
		}
		else
		{
			currentSpeedX = moveTowardsX / moveVector * fabs(currentSpeedX);
			currentSpeedY = moveTowardsY / moveVector * fabs(currentSpeedY);
		}
		*/
		drawBoostLines = true;

		if (gameMode == 1)
			currentFuel -= 0.3f;
		else if (gameMode == 2)
			currentFuel -= 0.5f;

		currentSpeedX += moveTowardsX / moveVector * accX;
		currentSpeedY += moveTowardsY / moveVector * accY;

	}
	else if (App::IsKeyPressed('S')) {
		float xsign = copysignf(0.5f, currentSpeedX);
		float ysign = copysignf(0.5f, currentSpeedY);
		currentSpeedX -= xsign;
		currentSpeedY -= ysign;

		drawBoostLines = false;
	}
	else {
		drawBoostLines = false;
	}

	x += currentSpeedX;
	y += currentSpeedY;

	//Player Rotation
	//Left Wing
	leftWing.SetLines((-(baseLength / 2) * cos(angle)) - (-(height / 2) * sin(angle)),		//x1
		(-(height / 2) * cos(angle)) + (-(baseLength / 2) * sin(angle)),					//y1
		(0 * cos(angle)) - ((height / 2) * sin(angle)),										//x2
		((height / 2) * cos(angle)) + (0 * sin(angle))										//y2
	);
	//Right Wing
	rightWing.SetLines((baseLength / 2 * cos(angle)) - (-(height / 2) * sin(angle)),		//x1
		(-(height / 2) * cos(angle)) + (baseLength / 2 * sin(angle)),						//y1
		(0 * cos(angle)) - ((height / 2) * sin(angle)),										//x2
		((height / 2) * cos(angle)) + (0 * sin(angle))										//y2
	);
	//Base Wing
	baseWing.SetLines((-(baseLength / 2) * cos(angle)) - (-(height / 2) * sin(angle)),		//x1
		(-(height / 2) * cos(angle)) + (-(baseLength / 2) * sin(angle)),					//y1
		((baseLength / 2) * cos(angle)) - (-(height / 2) * sin(angle)),						//x2
		(-(height / 2) * cos(angle)) + ((baseLength / 2) * sin(angle))						//y2
	);

	//Boost Line 1
	boostLine1.SetLines((0 * cos(angle)) - (-(height / 2) * sin(angle)),					//x1
		(-(height / 2) * cos(angle)) + (0 / 2 * sin(angle)),								//y1
		(0 * cos(angle)) - (-(height)* sin(angle)),											//x2
		(-(height)* cos(angle)) + (0 * sin(angle))											//y2
	);

	boostLine2.SetLines((-(baseLength / 4) * cos(angle)) - (-(height / 2) * sin(angle)),	//x1
		(-(height / 2) * cos(angle)) + (-(baseLength / 4) / 2 * sin(angle)),				//y1
		(-(baseLength / 3) * cos(angle)) - (-(height)* sin(angle)),							//x2
		(-(height)* cos(angle)) + (-(baseLength / 3) * sin(angle))							//y2
	);

	boostLine3.SetLines(((baseLength / 4) * cos(angle)) - (-(height / 2) * sin(angle)),		//x1
		(-(height / 2) * cos(angle)) + ((baseLength / 4) / 2 * sin(angle)),					//y1
		((baseLength / 3) * cos(angle)) - (-(height)* sin(angle)),							//x2
		(-(height)* cos(angle)) + ((baseLength / 3) * sin(angle))							//y2
	);

	if (currentArmor <= 1 || currentFuel <= 1) {
		App::PlaySoundW("sounds/lose2.wav", false);
		isDead = true;
		currentArmor = 0;
		currentFuel = 0;
	}
	if (gameMode == 1) {
		if (currentFuel > 300)
			currentFuel = 300;
	}
	else if (gameMode == 2)
	{
		if (currentFuel > 250)
			currentFuel = 250;
	}

	//Color change by low armor
	if (currentArmor < 15)
	{
		SetColour(1, 0.3f, 0.3f);
	}
}

void Player::Damage(float damageAmount) {
	currentArmor -= damageAmount;
}

void Player::SetColour(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
}

void Player::ComputeCollision(float bodyX, float bodyY) {
	
	x = bodyX;
	y = bodyY;
}

void Player::SetCurrentSpeedX(float speed) {
	currentSpeedX = speed;
}
void Player::SetCurrentSpeedY(float speed) {
	currentSpeedY = speed;
}

float Player::GetMaxSpeed() {
	return maxSpeed;
}

float Player::GetCurrentSpeed() {
	return currentSpeedX;
}

float Player::GetPosX() {
	return x;
}

float Player::GetPosY() {
	return y;
}

float Player::GetLength() {
	return baseLength;
}

float Player::GetHeight() {
	return height;
}
