#pragma once
#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_
//-----------------------------
#include "App\app.h"
#include <math.h>
#include "PhysicsBody.h"
#include "Line.h"

//-----------------------------

class LevelManager {
public:
	LevelManager();
	~LevelManager();

	void LoadLevel(); // 0 - Menu, 1 - Level-1......
	void TransverseLevel(int newLevel);
	void DrawLevel();
	void UpdateLevel(float playerX , float playerY, float* playerArmor,int* gameMode);

	int GetLevel();

	std::vector<PhysicsBody> RoadBlocks;	
	std::vector<PhysicsBody> ProgressLines;
	std::vector<PhysicsBody> exitBody;
	std::vector<PhysicsBody> AsteroidsBody;

private:
	std::vector<PhysicsBody> Roads;
	std::vector<Line> Stars;

	void CreateStars();

	int currentLevel;
	bool levelLoaded;

	//Menu Select
	float selectR, selectG, selectB;
	PhysicsBody selectBody;
	int selected;

};

#endif