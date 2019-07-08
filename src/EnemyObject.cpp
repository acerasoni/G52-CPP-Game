#include "header.h"
#include "templates.h"
#include "EnemyObject.h"
#include "HeroObject.h"
#include <time.h> 

EnemyObject::EnemyObject(BaseEngine *pEngine, int iMapX, int iMapY, int identifier, int speed)
	: SpriteObject(pEngine, iMapX, iMapY)
{

	switch (static_cast<PsyagceEngine*>(GetEngine())->mode)
	{
	case 0 :
		stats.baseAttack = 2;
		iSpeed = speed;
		fight = false;
		stats.armor = 0;
		break;
	case 1:
		stats.baseAttack = 4;
		iSpeed = 1 + speed;
		fight = true;
		stats.armor = 25;
		break;
	case 2:
		stats.baseAttack = 6;
		iSpeed = 2 + speed;
		fight = true;
		stats.armor = 40;
		break;
	}
	
	//printf("%d", iSpeed);
	
	id = identifier;
	stats.stamina = 0;

	ifstream in("settings/enemy.txt");
	if (in) {
		in >> stats.hp;
		in >> expvalue;
	}
	else
	{
		stats.hp = 150;
		expvalue = 25;
	}


	hitbox.sourceX = m_iCurrentScreenX;
	hitbox.sourceY = m_iCurrentScreenY;
	hitbox.width = 130;
	hitbox.height = 69;

	actiontimer = 0;
	attackSpeed = 40;
	attackCounter = 0;

	respawnTimer = 150;
	fight = true;
	animation = 0;
	idletimer = 50;
	turned = true;
	attacking = false;
	jumping = false;

	switch (static_cast<PsyagceEngine*>(GetEngine())->mode)
	{
	case 0:
	case 1:
		im2[1].LoadImage("hero/wolf/walk.png");
		im[1].ShrinkFrom(&im2[1], 2);
		break;
	case 2:
		im2[1].LoadImage("hero/wolf/run.png");
		im[1].ShrinkFrom(&im2[1], 2);
		break;
	}
	im2[0].LoadImage("hero/wolf/idle.png");
	im[0].ShrinkFrom(&im2[0], 2);
	im2[2].LoadImage("hero/wolf/attack.png");
	im[2].ShrinkFrom(&im2[2], 2);
	im2[3].LoadImage("hero/wolf/dead.png");
	im[3].ShrinkFrom(&im2[3], 2);
	im[4].LoadImage("hero/wolf/dead.png");
	im2[4].LoadImage("hero/wolf/dead.png");

	m_iCurrentScreenX = m_iPreviousScreenX = iMapX;
	m_iCurrentScreenY = m_iPreviousScreenY = iMapY;
	curr = static_cast<HeroObject*>(GetEngine()->GetDisplayableObject(0));
	health = new StatsBar(pEngine, stats.hp, "health", m_iCurrentScreenX, m_iCurrentScreenY);
	SetVisible(true);
}


EnemyObject::~EnemyObject()
{
}

void EnemyObject::Draw()
{
	
	if (!hidden)
	{
		//std::cout << id << std::endl;
		if (IsVisible())
		{


			//printf("%d, %d\n", turned, idletimer);
			hitbox.sourceX = m_iCurrentScreenX;
			hitbox.sourceY = m_iCurrentScreenY;

			health->Draw();

			if (idletimer == 0)
				animation = 0;

			if (animation == 2)
			{
				m_iCurrentScreenY -= 40;
			}

			if (jumping)
				Jump(iJumpTimer);

			//im2 = im[animation];

			if (!turned)
				im[animation].RenderImageWithMask(GetEngine()->GetForeground(), 0, ((im[animation].GetHeight() / 20) * frame), m_iCurrentScreenX, m_iCurrentScreenY, im[animation].GetWidth(), (im[animation].GetHeight() / 20));
			else
				im[animation].RenderImageWithMask(GetEngine()->GetForeground(), 0, (im[animation].GetHeight() / 20) * frame + (im[animation].GetHeight() / 2), m_iCurrentScreenX, m_iCurrentScreenY, im[animation].GetWidth(), (im[animation].GetHeight() / 20));
			//	printf("%d, %d\n", im2.GetHeight() / 20, im2.GetWidth());

			


			//printf("%d, enemy number %d\n", frame, id);
			if (animation == 3 && frame == 9)
			{
				SetVisible(false);
				HeroObject * curr = static_cast<HeroObject*>(GetEngine()->GetDisplayableObject(0));
				curr->IncrementExp(expvalue);
				curr->inventory.gold += expvalue * 2;
			}

			//printf("%d, %d\n", animation, frame);
			StoreLastScreenPositionForUndraw();

			m_iDrawHeight = (im[animation].GetHeight() / 20);
			m_iDrawWidth = im[animation].GetWidth();

			if (animation == 2)
			{
				m_iCurrentScreenY += 40;
			}

			idletimer--;
			if (actiontimer > 0)
				actiontimer--;

		}
		else {
			if (respawnTimer == 0)
			{
				InitStats();
				SetVisible(true);
			}
			else
				respawnTimer--;

		}
	}
}

/*void EnemyObject::LoadFrames()
{
	switch (static_cast<PsyagceEngine*>(GetEngine())->mode)
	{
	case 0:
	case 1:
		im2.LoadImage("hero/wolf/walk.png");
		im[1].ShrinkFrom(&im2, 2);
		break;
	case 2:
		im2.LoadImage("hero/wolf/run.png");
		im[1].ShrinkFrom(&im2, 2);
		break;
	}
	im2.LoadImage("hero/wolf/idle.png");
	im[0].ShrinkFrom(&im2, 2);
	im2.LoadImage("hero/wolf/attack.png");
	im[2].ShrinkFrom(&im2, 2);
	im2.LoadImage("hero/wolf/dead.png");
	im[3].ShrinkFrom(&im2, 2);
}*/

void EnemyObject::UpdatePosition(int pixels)
{
	m_iCurrentScreenX -= pixels;
}

void EnemyObject::DoUpdate(int time)
{

	
	IncrementFrame();
	HeroObject * curr = static_cast<HeroObject*>(GetEngine()->GetDisplayableObject(0));

	
	if (actiontimer == 0)
	{
		if (stats.hp <= 25)
		{
		
				if (curr->ReturnX() > m_iCurrentScreenX)
				{

					turned = true;
					m_iCurrentScreenX -= iSpeed;
					animation = 1;
					idletimer = 20;
				}
				else
				{
					turned = false;
					m_iCurrentScreenX += iSpeed;
					animation = 1;
					idletimer = 20;
				}
				if (curr->ReturnX() == m_iCurrentScreenX)
				{
					turned = false;
					m_iCurrentScreenX += iSpeed;
					animation = 1;
					idletimer = 20;
				}	
		}
		else
		{
			if (fight)
			{
				if (std::abs(this->hitbox.sourceY - curr->hitbox.sourceY) <= 30 && std::abs(this->hitbox.sourceX - curr->hitbox.sourceX) <= 70)
				{
					attackCounter++;
					if (attackCounter % attackSpeed == 0)
					{
						curr->UpdateHealth(this->stats.baseAttack);
						curr->UpdateFrame(0);
						//printf("YAS %d\n", curr->stats.hp);
						animation = 2;
						idletimer = 30;
					}
				}

			}





			if (curr->ReturnX() != m_iCurrentScreenX)
			{
				//std::cout << id << " me " << m_iCurrentScreenX << " hero " << curr->ReturnX()  << std::endl;
				if (curr->ReturnX() > m_iCurrentScreenX)
				{
					if (curr->ReturnX() > m_iCurrentScreenX + 10)
					turned = false;
					m_iCurrentScreenX += iSpeed;
					animation = 1;
					idletimer = 20;
				}
				else if (curr->ReturnX() < m_iCurrentScreenX)
				{
					if (curr->ReturnX() < m_iCurrentScreenX + 10)
					turned = true;
					m_iCurrentScreenX -= iSpeed;
					animation = 1;
					idletimer = 20;
				}

			}

			if (curr->ReturnY() < m_iCurrentScreenY - 10)
			{
				if (std::abs(this->hitbox.sourceX - curr->hitbox.sourceX) <= 70)
				{
					//	printf("Yas\n");
					if (!jumping && onGround)
					{
						jumping = true;
						animation = 1;
						idletimer = 20;
					}
				}
			}
		}

		if (health->current <= 0)
		{
			animation = 3;
			idletimer = -1;
		}
		if (!jumping)
		{
			Gravity();
		}
	}
		
		
	if (m_iCurrentScreenX < 0)
	{
		m_iCurrentScreenX = 0;
		iBorder = true;
	}	
	else if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
	{
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
		iBorder = true;
	}
	else {
		iBorder = false;
	}

	health->UpdateStats(stats.hp, m_iCurrentScreenX, m_iCurrentScreenY);
	RedrawObjects();
	
		//printf("%d enemy\n", m_iCurrentScreenY);
}



bool EnemyObject::isEnemy()
{
	return true;
}

void EnemyObject::InitStats()
{
	stats.hp = 150;
	respawnTimer = 150;
	fight = true;
	animation = 0;
	idletimer = 50;
	turned = true;
	attacking = false;
	jumping = false;
}

