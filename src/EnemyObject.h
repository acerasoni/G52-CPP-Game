#pragma once
#include "SpriteObject.h"
#include "StatsBar.h"


class EnemyObject :
	public SpriteObject
{


public:
	EnemyObject(BaseEngine *pEngine, int iMapX, int iMapY, int id, int speed);
	~EnemyObject();
	
	void Draw();
	void UpdatePosition(int pixels);
	bool isEnemy();
	void DoUpdate(int time);
	void InitStats();
	int expvalue;

private:

	int attackSpeed;
	int attackCounter;
	int iSpeed;
	

	
};

