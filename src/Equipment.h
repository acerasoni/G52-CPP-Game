#pragma once
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "DisplayableObject.h"


class Equipment :
	public DisplayableObject
{
public:
	Equipment(BaseEngine* pEngine, int id);
	~Equipment();

	std::string name;
	std::string typeitem;
	int price;
	int attack;
	int armor;
	int agility;
	int intelli;
	int str;
	int upgrade;
	int type;
	bool desc;

	ImageData* pHero;
	std::string buffer;
	char buf[128];
	

	void Upgrade();
	void Draw();
	void DoUpdate();
	void LoadFrames();
	void SetName(std::string name);
	void SetAttack(int attack);
	void SetPrice(int price);
	void SetHero(ImageData* pHero);
	bool IsClicked(int iX, int iY);
	void PrintDesc();
};

