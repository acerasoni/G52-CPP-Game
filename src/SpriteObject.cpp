#include "header.h"
#include "templates.h"
#include "SpriteObject.h"
#include "JPGImage.h"



SpriteObject::SpriteObject(BaseEngine* pEngine, int iMapX, int iMapY)
	: DisplayableObject(pEngine)
{
	iFrameCounter = 0;
	frame = 0;
	onGround = true;
	dead = false;
	iBorder = false;
	hidden = false;
}


SpriteObject::~SpriteObject()
{

    for (int i = 0; i < 5; i++)
	{
		im[i].FreeData();
		im2[i].FreeData();
	
	}
}

void SpriteObject::Dying()
{

}





/*
void SpriteObject::LoadFrames()
{
	
	im2.LoadImage("hero/paladin/idle.png");
	im[0].ShrinkFrom(&im2, 3);
	im2.LoadImage("hero/paladin/walk.png");
	im[1].ShrinkFrom(&im2, 3);
	im2.LoadImage("hero/paladin/attack.png");
	im[2].ShrinkFrom(&im2, 3);
	im2.LoadImage("hero/paladin/dead.png");
	im[3].ShrinkFrom(&im2, 3);
	im2.LoadImage("hero/paladin/jump.png");
	im[4].ShrinkFrom(&im2, 3);

}*/

bool SpriteObject::isEnemy()
{
	return false;
}

void SpriteObject::IncrementFrame()
{
	iFrameCounter++;
	frame = iFrameCounter % 10;

}

void SpriteObject::UpdateHealth(int damage)
{
	stats.hp -= damage;
	health->current = stats.hp;
}

void SpriteObject::UpdateFrame(int frame)
{
	iFrameCounter = frame;
}

void SpriteObject::Jump(int iJumpCounter)
{
	onGround = false;
	if (iJumpCounter < 8)
	{
		m_iCurrentScreenY -= 15;
		iJumpTimer += 1;
		
	}
	else if (iJumpCounter == 19)
	{
		Gravity();
		jumping = false;
		iJumpTimer = 0;
	}
	else
	{
		Gravity();
		iJumpTimer++;
	}
	

}

void SpriteObject::setFight(bool iFight)
{
	fight = iFight;
}

void SpriteObject::Gravity()
{
	PsyagceEngine* curr = static_cast<PsyagceEngine*>(GetEngine());
	if (!curr->CheckTiles(m_iCurrentScreenX + hitbox.width, m_iCurrentScreenY + hitbox.height) && !curr->CheckTiles(m_iCurrentScreenX, m_iCurrentScreenY + hitbox.height))
	{

		m_iCurrentScreenY += 10;
	}
	else {
		onGround = true;
		if (!this->isEnemy())
		{
			if (static_cast<PsyagceEngine*>(GetEngine())->m_oPlatform.IsValidTilePosition(m_iCurrentScreenX + hitbox.width, m_iCurrentScreenY + hitbox.height + 1))
				static_cast<PsyagceEngine*>(GetEngine())->UpdatePlatforms();
			if (static_cast<PsyagceEngine*>(GetEngine())->m_oPlatformTwo.IsValidTilePosition(m_iCurrentScreenX + hitbox.width, m_iCurrentScreenY + hitbox.height + 1))
				static_cast<PsyagceEngine*>(GetEngine())->UpdatePlatforms();
		}
	}

}

void SpriteObject::InitStats()
{

}

void SpriteObject::updatePosition(int x, int y)
{
	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;
}


void SpriteObject::FreeFrames()
{

	for (int i = 0; i < 5; i++)
	{
		im[i].FreeData();
		im2[i].FreeData();
	}
}

int SpriteObject::ReturnX()
{
	return m_iCurrentScreenX;
}

int SpriteObject::ReturnY()
{
	return m_iCurrentScreenY;
}

void SpriteObject::SetX(int x)
{
	m_iCurrentScreenX = x;
}

void SpriteObject::SetY(int y)
{
	m_iCurrentScreenY = y;
}