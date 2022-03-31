//------------------------------------------------------------------------
//Asteroid Driving School
// By Khizer Mahboob
// Game.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include "Player.h"
#include "PhysicsBody.h"
#include "LevelManager.h"
#include <vector>
//------------------------------------------------------------------------
#include "app\app.h"

//Initialize Class
Player* player = new Player(30,50,1,1,1);
PhysicsBody* playerBody = new PhysicsBody();

LevelManager* levelManager = new LevelManager();

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	player->SetColour(0.5f, 1, 0.5f);

	//playerBody->SetID(6);
	playerBody->SetStatic(false);
	playerBody->CreateBody(player->GetPosX(),player->GetPosY(),player->GetLength(),player->GetHeight(),6);

	levelManager->TransverseLevel(0);

	App::PlaySoundW("sounds/start.wav", false);
}

//------------------------------------------------------------------------+
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//Moves virtual coordinates of the player 
	if (levelManager->GetLevel() != 0 && levelManager->GetLevel() != 3) {
		player->Movement();
		//Moves PlayerBody with player	
		playerBody->BackgroundMovement(player->GetPosX(), player->GetPosY());
	}
	
	//Update Level Props
	levelManager->UpdateLevel(player->GetPosX(),player->GetPosY(),&player->currentArmor,&player->gameMode);

	//Process Collisions with all Props/Walls and PlayerBody
	playerBody->Collision(levelManager->RoadBlocks,&player->currentSpeedX,&player->currentSpeedY,&player->currentArmor,&player->currentFuel,&player->victory);
	playerBody->Collision(levelManager->ProgressLines, &player->currentSpeedX, &player->currentSpeedY, &player->currentArmor, &player->currentFuel, &player->victory);
	playerBody->Collision(levelManager->exitBody, &player->currentSpeedX, &player->currentSpeedY, &player->currentArmor, &player->currentFuel, &player->victory);
	playerBody->Collision(levelManager->AsteroidsBody, &player->currentSpeedX, &player->currentSpeedY, &player->currentArmor, &player->currentFuel, &player->victory);
	//Effect Player with Collision
	player->ComputeCollision(playerBody->virtualX, playerBody->virtualY);

	if (player->isDead)
		levelManager->TransverseLevel(3);
	if (player->victory == 1) {
		levelManager->TransverseLevel(4);
	}

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	if (levelManager->GetLevel() == 1)
		player->DrawPlayer();
	//playerBody->DrawBody();	

	levelManager->DrawLevel();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	delete player;
	delete playerBody;
	delete levelManager;
}