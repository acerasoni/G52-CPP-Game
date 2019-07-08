#pragma once
#include "JPGImage.h"
#include "DisplayableObject.h"
#include "StatsBar.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>



class SpriteObject :
	public DisplayableObject
{
public:
	SpriteObject(BaseEngine *pEngine, int iMapX, int iMapY);
	~SpriteObject();

	class Statistics {

	public:
		int hp;
		int baseAttack;
		int stamina;
		int armor;
		int speed;
	};


	class HitBox {
	public:
		int sourceX;
		int sourceY;
		int width;
		int height;

		int ReturnY()
		{
			return sourceY;
		}
		int ReturnX()
		{
			return sourceX;
		}
	};

protected:


	std::string spritename;
	std::string character;
	std::string extension;
	ImageData im[5]; // each array slot will store one action sprite. 0 = idle, 1 = walk, 2 = attack, 3 = dead, 4 = jump;
	ImageData im2[5];
	int iMapX, iMapY, actiontimer, iFrameCounter;
	

public:

	bool attacking;
	bool iBorder;
	bool jumping;
	int jump, prevFrame;
	//virtual void LoadFrames();
	virtual void Jump(int iJumpCounter);
	virtual void FreeFrames();
	void Dying();
	int frame, id;
	int animation;
	int iJumpTimer;
	HitBox hitbox;
	Statistics stats;
	StatsBar *stamina;
	StatsBar *health;
	bool dead;
	int respawnTimer, idletimer;

	//Utility functions for every sprite object 
	virtual bool isEnemy();
	virtual void InitStats();
	void IncrementFrame();
	void UpdateFrame(int frame);
	void UpdateHealth(int damage);
	bool fight, onGround;
	virtual void setFight(bool iFight);
	virtual void Gravity();
	void updatePosition(int x, int y);
	int ReturnX();
	int ReturnY();
	void SetX(int x);
	void SetY(int y);
	bool hidden;
	bool turned;
	SpriteObject * curr;
};



