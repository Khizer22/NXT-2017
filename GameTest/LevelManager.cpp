#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager() {
	currentLevel = 0;
	levelLoaded = false;

	selectR = 1;
	selectG = 1;
	selectB = 1;	
	selected = 1;
}

LevelManager::~LevelManager() {}

void LevelManager::LoadLevel() {
	if (!levelLoaded) {
		if (currentLevel == 0)
		{
			//Menu
			selectBody.CreateBody(APP_VIRTUAL_WIDTH / 2 - 30, APP_VIRTUAL_HEIGHT / 2 + 10, 10, 10, -10);
		}
		else if (currentLevel == 1)
		{		
			//ProgressLines-------------------------------------------------------------------------------------
			ProgressLines = { {} ,{},{} ,{},{} };
			ProgressLines.at(0).CreateBody(880, 300, 20, 300, -1);
			//ProgressLines.at(0).isTrigger = true;
			ProgressLines.at(1).CreateBody(1480, 1200, 1200, 50, -1);
			ProgressLines.at(2).CreateBody(3200, 1700, 50, 600, -1);
			ProgressLines.at(3).CreateBody(4080, 1100, 340, 50, -1);
			ProgressLines.at(4).CreateBody(4080, 700, 340, 50, -1);

			//Convert Virtual Coordinates to Screen Coordinates
			for (int i = 0; i < ProgressLines.size(); i++) {
				ProgressLines.at(i).SetCoordinates(ProgressLines.at(i).GetPosX() + ProgressLines.at(i).GetLength() / 2, ProgressLines.at(i).GetPosY() + ProgressLines.at(i).GetHeight() / 2);
				ProgressLines.at(i).SetColour(0.1f, 0.1f, 1);
			}

			//RoadBlocks----------------------------------------------------------------------------------------
			RoadBlocks = { {},{} ,{} ,{} ,{},{},{} ,{},{},{},{} ,{} ,{},{},{},{},{},{},{},{},{},{},{},{} ,{},{} };
		
			//Wall One Side
			RoadBlocks.at(0).CreateBody(0 ,0, 20, 600,1);
			RoadBlocks.at(1).CreateBody(0, 580, 1300, 20, 3);
			RoadBlocks.at(2).CreateBody(1280, 600 - 800, 20, 800, 2);
			RoadBlocks.at(3).CreateBody(1280, 600 - 800, 800, 20, 3);
			RoadBlocks.at(4).CreateBody(2060, 600 - 800, 20, 800, 1);
			RoadBlocks.at(5).CreateBody(1480, 600 , 600, 20, 4);
			RoadBlocks.at(6).CreateBody(1480, 600, 20, 1200, 1);
			RoadBlocks.at(7).CreateBody(1480, 1800, 900, 20, 3);
			RoadBlocks.at(8).CreateBody(2380, 1800, 20, 500, 1); //*
			RoadBlocks.at(9).CreateBody(2380, 2300, 2000, 20, 3);
			RoadBlocks.at(10).CreateBody(4380, -200, 20, 2500, 2); //*
			RoadBlocks.at(11).CreateBody(4380 - 900, -200, 900, 20, 4);
			RoadBlocks.at(12).CreateBody(4380 - 900, -200 - 800, 20, 800, 2);
			RoadBlocks.at(13).CreateBody(4380 - 900, -200 - 800, 1000, 20, 3);
			RoadBlocks.at(14).CreateBody(4480 , -1500, 20, 500, 2);

			//Wall Other Side
			RoadBlocks.at(15).CreateBody(600, 0, 20, 300, 2);
			RoadBlocks.at(16).CreateBody(600, 300, 300, 20, 4);
			RoadBlocks.at(17).CreateBody(880, -500, 20, 800, 1);
			RoadBlocks.at(18).CreateBody(880, -500, 1800, 20, 4);
			RoadBlocks.at(19).CreateBody(2680, -500, 20, 2200, 2);
			RoadBlocks.at(20).CreateBody(2680, 1700, 1400, 20, 4);
			RoadBlocks.at(21).CreateBody(4060, 200, 20, 1500, 1);
			RoadBlocks.at(22).CreateBody(4060 - 900, 200, 900, 20, 3);
			RoadBlocks.at(23).CreateBody(4060 - 900, -1500, 20, 1700, 1);
			RoadBlocks.at(24).CreateBody(4060 - 900, -1500, 1320, 20, 4);

			RoadBlocks.at(25).CreateBody(0,0, 600, 20, 4);

			//Convert Virtual Coordinates to Screen Coordinates
			for (int i = 0; i < RoadBlocks.size(); i++) {
				RoadBlocks.at(i).SetCoordinates(RoadBlocks.at(i).GetPosX() + RoadBlocks.at(i).GetLength() / 2, RoadBlocks.at(i).GetPosY() + RoadBlocks.at(i).GetHeight()/2);
			}

			//Road---------------------------------------------------------------------------------------------
			Roads = { {},{} ,{},{},{},{},{},{},{},{},{} };
			Roads.at(0).CreateBody(0, 0, 600, 600, 5);
			Roads.at(1).CreateBody(600, 300, 700, 300, 5);
			Roads.at(2).CreateBody(880, -500, 420, 1100, 5);
			Roads.at(3).CreateBody(1300, -500, 1400, 320, 5);
			Roads.at(4).CreateBody(2060, -180, 640, 800, 5);
			Roads.at(5).CreateBody(1480, 600, 1220, 1220, 5);
			Roads.at(6).CreateBody(2380, 1700, 2020, 620, 5);
			Roads.at(7).CreateBody(4060, 200, 340, 1500, 5);
			Roads.at(8).CreateBody(3160, -200, 1240, 420, 5);
			Roads.at(9).CreateBody(3160, -1500, 340, 1720, 5);
			Roads.at(10).CreateBody(3500, -1500, 1000, 520, 5);

			//(1480, 1800, 900, 20, 3)
			//Roads.at(0).isVisible = false;

			//Convert Virtual Coordinates to Screen Coordinates
			for (int i = 0; i < Roads.size(); i++) {
				Roads.at(i).SetCoordinates(Roads.at(i).GetPosX() + Roads.at(i).GetLength() / 2, Roads.at(i).GetPosY() + Roads.at(i).GetHeight() / 2);
				Roads.at(i).SetColour(1, 0.1f, 0.1f);
			}

			//Asteroids---------------------------------------------------------------------------------------------
			AsteroidsBody = { {},{},{},{},{},{},{},{},{},{} };
			AsteroidsBody.at(0).CreateBody(500, 500, 100, 100, -9);
			AsteroidsBody.at(1).CreateBody(1500,1500, 100, 100, -9);
			AsteroidsBody.at(2).CreateBody(880, -400, 100, 100, -9);
			AsteroidsBody.at(3).CreateBody(1300, -350, 100, 100, -9);
			AsteroidsBody.at(4).CreateBody(2060, -180, 100, 100, -9);
			AsteroidsBody.at(5).CreateBody(1480, 600, 100, 100, -9);
			AsteroidsBody.at(6).CreateBody(2380, 1700, 100, 100, -9);
			AsteroidsBody.at(7).CreateBody(4060, 200, 100, 100, -9);
			AsteroidsBody.at(8).CreateBody(3160, -200, 100, 100, -9);
			AsteroidsBody.at(9).CreateBody(3160, -1500, 100, 100, -9);

			//Convert Virtual Coordinates to Screen Coordinates
			for (int i = 0; i < AsteroidsBody.size(); i++) {
				AsteroidsBody.at(i).SetCoordinates(AsteroidsBody.at(i).GetPosX() + AsteroidsBody.at(i).GetLength() / 2, AsteroidsBody.at(i).GetPosY() + AsteroidsBody.at(i).GetHeight() / 2);
				AsteroidsBody.at(i).SetColour(1, 0.3f, 0.5f);
			}


			//FinishLine---------------------------------------------------------------------------------------------
			exitBody = { {} };
			exitBody.at(0).CreateBody(3700, -1500, 500, 500, 10);
			exitBody.at(0).SetColour(0.3f, 1, 0.6f);
			exitBody.at(0).SetCoordinates(exitBody.at(0).GetPosX() + exitBody.at(0).GetLength() / 2, exitBody.at(0).GetPosY() + exitBody.at(0).GetHeight() / 2);
			
			//Stars---------------------------------------------------------------------------------------------
			CreateStars();
		}
		else if (currentLevel == 3)
		{

		}
		levelLoaded = true;
	}
}

void LevelManager::DrawLevel() {
	if (currentLevel == 0)
	{
		selectBody.DrawBody();

		App::Print(470, 700, "Asteroid Driving School",0.4f,0.9f,1);
		App::Print(800, 650, "W - Move Foward",0.1f,1,1);
		App::Print(800, 600, "S - Space Brakes",0.1f, 1, 1);
		App::Print(70, 650, "Avoid hitting the walls,");
		App::Print(70, 600, "DO NOT hit the Pink-Square Asteroids");
		App::Print(70, 550, "Find the Finish Line");
		App::Print(70, 500, "Enjoy");
		App::Print(APP_VIRTUAL_WIDTH/2 - 10, APP_VIRTUAL_HEIGHT/2, "Normal                          -W", selectR, selectG, selectB);
		App::Print(APP_VIRTUAL_WIDTH / 2 - 10, APP_VIRTUAL_HEIGHT / 2 - 100, "Hard                             -S", selectR, selectG, selectB);
	}
	else if (currentLevel == 1) {

		//Progress Lines
		for (int i = 0; i < ProgressLines.size(); i++) {
			ProgressLines.at(i).DrawBody();
		}		
		
		for (int i = 0; i < RoadBlocks.size(); i++) {
			RoadBlocks.at(i).DrawBody();
		}
		/*
		for (int i = 0; i < Roads.size(); i++) {
			Roads.at(i).DrawBody();			
		}
		*/

		for (int i = 0; i < AsteroidsBody.size(); i++)
		{
			AsteroidsBody.at(i).DrawBody();
		}

		for (int i = 0; i < Stars.size(); i++) {
			int computeAllRoads = 0;
			//For each Star, Check ALL Roads 
			for (int q = 0; q < Roads.size(); q++) {
				if (
					Stars.at(i).x1 > Roads.at(q).GetPosX() - Roads.at(q).GetLength() / 2
					&& Stars.at(i).x1 < Roads.at(q).GetPosX() + Roads.at(q).GetLength() / 2
					&& Stars.at(i).y1 > Roads.at(q).GetPosY() - Roads.at(q).GetHeight() / 2
					&& Stars.at(i).y1  < Roads.at(q).GetPosY() + Roads.at(q).GetHeight() / 2
					) {
					computeAllRoads++;
				}
			}
			if (computeAllRoads <= 0)
				App::DrawLine(Stars.at(i).x1, Stars.at(i).y1, Stars.at(i).x2, Stars.at(i).y2);			
		}

		exitBody.at(0).DrawBody();
	}
	else if (currentLevel == 3)
	{
		App::Print(500, 400, "YOU DIED", 1, 1, 1);
		App::Print(450, 300, "Press Esc to Exit",1,1,1);
	}
	else if (currentLevel == 4)
	{
		App::Print(480, 500, "YOU WON", 0.5f, 0.8f, 1);
		App::Print(380, 450, "Congratulations on completing the game", 1, 1, 1);
	}
}

void LevelManager::UpdateLevel(float playerX,float playerY,float* playerArmor,int* gameMode) {
		
	if (currentLevel != 0 && currentLevel != 3) {
		for (int i = 0; i < ProgressLines.size(); i++) {
			ProgressLines.at(i).BackgroundMovement(playerX, playerY);
		}

		for (int i = 0; i < RoadBlocks.size(); i++) {
			RoadBlocks.at(i).BackgroundMovement(playerX, playerY);
		}

		for (int i = 0; i < Roads.size(); i++) {
			Roads.at(i).BackgroundMovement(playerX, playerY);
		}

		for (int i = 0; i < AsteroidsBody.size(); i++)
		{
			AsteroidsBody.at(i).BackgroundMovement(playerX,playerY);
		}

		exitBody.at(0).BackgroundMovement(playerX, playerY);

	}
	else if (currentLevel == 3)
	{
	}
	else if (currentLevel == 0)
	{
		if (App::IsKeyPressed('W')) {
			selectBody.SetCoordinates(APP_VIRTUAL_WIDTH / 2 - 30, APP_VIRTUAL_HEIGHT / 2 + 10);
			selected = 1;
		}
		else if (App::IsKeyPressed('S')) {
			selectBody.SetCoordinates(APP_VIRTUAL_WIDTH / 2 - 30, APP_VIRTUAL_HEIGHT / 2 - 90);
			selected = 2;
		}
		if (selected == 1) {
			if (App::IsKeyPressed(VK_RETURN)) {
				*playerArmor = 75;
				*gameMode = 1;
				TransverseLevel(1);
				App::PlaySoundW("sounds/click.wav", false);
			}
		}
		else if (selected == 2) {
			if (App::IsKeyPressed(VK_RETURN)) {
				*playerArmor = 25;
				*gameMode = 2;
				TransverseLevel(1);
				App::PlaySoundW("sounds/click.wav", false);
			
			}
		}	

	}
	else if (currentLevel == 4)
	{

	}
}

void LevelManager::TransverseLevel(int newLevel) {
	currentLevel = newLevel;
	levelLoaded = false;

	//Destroy Vectors
	AsteroidsBody.clear();
	RoadBlocks.clear();
	Roads.clear();
	Stars.clear();

	LoadLevel();
}

int LevelManager::GetLevel() {
	return currentLevel;
}

void LevelManager::CreateStars() {
	
	Stars = { 
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{} };
	
	Stars.at(0).SetLines(150 - 2, 700 - 2, 150 + 2, 700 + 2);
	Stars.at(1).SetLines(150 + 2, 700 - 2, 150 - 2, 700 + 2);

	Stars.at(2).SetLines(300 - 2, 250 - 2, 300 + 2, 250 + 2);
	Stars.at(3).SetLines(300 + 2, 250 - 2, 300 - 2, 250 + 2);

	Stars.at(4).SetLines(500 - 2, 600 - 2, 500 + 2, 600 + 2);
	Stars.at(5).SetLines(500 + 2, 600 - 2, 500 - 2, 600 + 2);

	Stars.at(6).SetLines(632 - 2, 855 - 2, 632 + 2, 855 + 2);
	Stars.at(7).SetLines(632 + 2, 855 - 2, 632 - 2, 855 + 2);

	Stars.at(8).SetLines(400 - 2, 120 - 2, 400 + 2, 120 + 2);
	Stars.at(9).SetLines(400 + 2, 120 - 2, 400 - 2, 120 + 2);

	Stars.at(10).SetLines(850 - 2, 350 - 2, 850 + 2, 350 + 2);
	Stars.at(11).SetLines(850 + 2, 350 - 2, 850 - 2, 350 + 2);

	Stars.at(12).SetLines(990 - 2, 100 - 2, 990 + 2, 100 + 2);
	Stars.at(13).SetLines(990 + 2, 100 - 2, 990 - 2, 100 + 2);

	Stars.at(14).SetLines(200 - 2, 300 - 2, 200 + 2, 300 + 2);
	Stars.at(15).SetLines(200 + 2, 300 - 2, 200 - 2, 300 + 2);

	Stars.at(16).SetLines(400 - 2, 230 - 2, 400 + 2, 230 + 2);
	Stars.at(17).SetLines(400 + 2, 230 - 2, 400 - 2, 230 + 2);

	Stars.at(18).SetLines(879 - 2, 356 - 2, 879 + 2, 356 + 2);
	Stars.at(19).SetLines(879 + 2, 356 - 2, 879 - 2, 356 + 2);

	Stars.at(20).SetLines(546 - 2, 352 - 2, 546 + 2, 352 + 2);
	Stars.at(21).SetLines(546 + 2, 352 - 2, 546 - 2, 352 + 2);

	Stars.at(22).SetLines(243 - 2, 275 - 2, 243 + 2, 275 + 2);
	Stars.at(23).SetLines(243 + 2, 275 - 2, 243 - 2, 275 + 2);

	Stars.at(24).SetLines(643 - 2, 647 - 2, 643 + 2, 647 + 2);
	Stars.at(25).SetLines(643 + 2, 647 - 2, 643 - 2, 647 + 2);

	Stars.at(26).SetLines(253 - 2, 462 - 2, 253 + 2, 462 + 2);
	Stars.at(27).SetLines(253 + 2, 462 - 2, 253 - 2, 462 + 2);

	Stars.at(28).SetLines(734 - 2, 316 - 2, 734 + 2, 316 + 2);
	Stars.at(29).SetLines(734 + 2, 316 - 2, 734 - 2, 316 + 2);

	Stars.at(30).SetLines(523 - 2, 124 - 2, 523 + 2, 124 + 2);
	Stars.at(31).SetLines(523 + 2, 124 - 2, 523 - 2, 124 + 2);

	Stars.at(32).SetLines(1000 - 2, 370 - 2, 1000 + 2, 370 + 2);
	Stars.at(33).SetLines(1000 + 2, 370 - 2, 1000 - 2, 370 + 2);

	Stars.at(34).SetLines(426 - 2, 300 - 2, 426 + 2, 300 + 2);
	Stars.at(35).SetLines(426 + 2, 300 - 2, 426 - 2, 300 + 2);

	Stars.at(36).SetLines(258 - 2, 514 - 2, 258 + 2, 514 + 2);
	Stars.at(37).SetLines(258 + 2, 514 - 2, 258 - 2, 514 + 2);

	Stars.at(38).SetLines(924 - 2, 25 - 2, 924 + 2, 25 + 2);
	Stars.at(39).SetLines(924 + 2, 25 - 2, 924 - 2, 25 + 2);

	Stars.at(40).SetLines(37 - 2, 158 - 2, 37 + 2, 158 + 2);
	Stars.at(41).SetLines(37 + 2, 158 - 2, 37 - 2, 158 + 2);

	Stars.at(42).SetLines(783 - 2, 63 - 2, 783 + 2, 63 + 2);
	Stars.at(43).SetLines(783 + 2, 63 - 2, 783 - 2, 63 + 2);

	Stars.at(44).SetLines(678 - 2, 700 - 2, 678 + 2, 700 + 2);
	Stars.at(45).SetLines(678 + 2, 700 - 2, 678 - 2, 700 + 2);

	Stars.at(46).SetLines(890 - 2, 674 - 2, 890 + 2, 674 + 2);
	Stars.at(47).SetLines(890 + 2, 674 - 2, 890 - 2, 674 + 2);

	Stars.at(48).SetLines(843 - 2, 563 - 2, 843 + 2, 563 + 2);
	Stars.at(49).SetLines(843 + 2, 563 - 2, 843 - 2, 563 + 2);

	Stars.at(50).SetLines(789 - 2, 189 - 2, 789 + 2, 189 + 2);
	Stars.at(51).SetLines(789 + 2, 189 - 2, 789 - 2, 189 + 2);

	Stars.at(52).SetLines(123 - 2, 99 - 2, 123 + 2, 99 + 2);
	Stars.at(53).SetLines(123 + 2, 99 - 2, 123 - 2, 99 + 2);

	Stars.at(54).SetLines(55 - 2, 700 - 2, 55 + 2, 700 + 2);
	Stars.at(55).SetLines(55 + 2, 700 - 2, 55 - 2, 700 + 2);

	Stars.at(56).SetLines(25 - 2, 376 - 2, 25 + 2, 376 + 2);
	Stars.at(57).SetLines(25 + 2, 376 - 2, 25 - 2, 376 + 2);

	Stars.at(58).SetLines(46 - 2, 297 - 2, 46 + 2, 297 + 2);
	Stars.at(59).SetLines(46 + 2, 297 - 2, 46 - 2, 297 + 2);

	Stars.at(60).SetLines(996 - 2, 689 - 2, 996 + 2, 689 + 2);
	Stars.at(61).SetLines(996 + 2, 689 - 2, 996 - 2, 689 + 2);

	Stars.at(62).SetLines(411 - 2, 650 - 2, 411 + 2, 650 + 2);
	Stars.at(63).SetLines(411 + 2, 650 - 2, 411 - 2, 650 + 2);

	Stars.at(64).SetLines(562 - 2, 373 - 2, 562 + 2, 373 + 2);
	Stars.at(65).SetLines(562 + 2, 373 - 2, 562 - 2, 373 + 2);
	
	for (int i = 0; i < Stars.size(); i++) {
		Stars.at(i).SetColour(1,1,1);
	}
	
}
