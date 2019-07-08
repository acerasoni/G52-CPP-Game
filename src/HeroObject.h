#pragma once
#include "SpriteObject.h"
#include "StatsBar.h"
#include "EnemyObject.h"
#include "Equipment.h"
#include "JPGImage.h"
#include <sys/stat.h>


class HeroObject :
	public SpriteObject
{
public:
	HeroObject(BaseEngine *pEngine, int iMapX, int iMapY);
	~HeroObject();


	class Inventory {


	public:
		
		Equipment *p[8]; // 0 = weapon, 1 = chest piece, 2 = pants, 3 = belt, 4 = gloves, 5 = bracelet, 6 = hat, 7 = shoes
		int gold;
		int level;
		int exp;
		int agility;
		int str;
		int intelli;

	};

public:

	Inventory inventory;
	void Draw();
	void DoUpdate(int iCurrentTime);
	int booster;
	int attackCounter;
	std::string buffer;
	std::string name;
	char buf[128];
	StatsBar *exp;
	void IncrementExp(int value);
	void InitInventory();
	ImageData* currm[8];
	

};

