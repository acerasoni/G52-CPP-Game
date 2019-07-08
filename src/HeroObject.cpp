#include "header.h"
#include "templates.h"
#include "HeroObject.h"
#include "JPGImage.h"



HeroObject::HeroObject(BaseEngine *pEngine, int iMapX, int iMapY)
	: SpriteObject(pEngine, iMapX, iMapY)
{
	ifstream in("settings/player.txt");
	if (in) {
		in >> inventory.gold;
		in >> inventory.exp;
		in >> inventory.level;
		in >> stats.hp;
		printf("Yes");
	}
	else
	{
		printf("No\n");
		stats.hp = 120;
		inventory.gold = 0;
		inventory.exp = 0;
		inventory.level = 0;
		
	}

	stats.stamina = 120;
	stats.speed = 10;
	stats.baseAttack = 25;
	inventory.agility = 10;
	inventory.str = 10;
	inventory.intelli = 10;

	attackCounter = 0;
	booster = 0;
	animation = 0;
	idletimer = 50;
	hitbox.sourceX = m_iCurrentScreenX;
	hitbox.sourceY = m_iCurrentScreenY;
	hitbox.width = 118;
	hitbox.height = 80;
	actiontimer = 0;
	turned = false;
	attacking = false;
	jumping = false;


	InitInventory();
	im2[0].LoadImage("hero/paladin/idle.png");
	im[0].ShrinkFrom(&im2[0], 3);
	im2[1].LoadImage("hero/paladin/walk.png");
	im[1].ShrinkFrom(&im2[1], 3);
	im2[2].LoadImage("hero/paladin/attack.png");
	im[2].ShrinkFrom(&im2[2], 3);
	im2[3].LoadImage("hero/paladin/dead.png");
	im[3].ShrinkFrom(&im2[3], 3);
	im2[4].LoadImage("hero/paladin/jump.png");
	im[4].ShrinkFrom(&im2[4], 3);
	//m_iCurrentScreenX = m_iPreviousScreenX = GetEngine()->GetWindowWidth() / 2 - im[0].GetWidth();
	m_iCurrentScreenX = m_iPreviousScreenX = 200;
	m_iCurrentScreenY = m_iPreviousScreenY = iMapY;
	stamina = new StatsBar(pEngine, stats.stamina, "stamina", m_iCurrentScreenX, m_iCurrentScreenY);
	health = new StatsBar(pEngine, stats.hp, "health", m_iCurrentScreenX, m_iCurrentScreenY);
	stamina = new StatsBar(pEngine, stats.stamina, "stamina", m_iCurrentScreenX, m_iCurrentScreenY);
	exp = new StatsBar(pEngine, inventory.exp, "exp", m_iCurrentScreenX, m_iCurrentScreenY);
	
	SetVisible(true);
}


HeroObject::~HeroObject()
{
	for (int i = 0; i < 8; i++)
	{
	//inventory.p[i]->sprite.FreeData();
	currm[i]->FreeData();
	}
	

	
}

void HeroObject::Draw() {
	
	if (static_cast<PsyagceEngine*>(GetEngine())->returnState() == 1)
	{

	stamina->Draw();
	health->Draw();
	exp->Draw();
	

	}




	if (idletimer < 0)
	{
		animation = 0;
	}
	
	if (animation == 2)
	{
		m_iCurrentScreenY -= 23;
	}

	if (jumping)
		Jump(iJumpTimer);

	   
	 
	 //   im2 = im[animation];

	if (static_cast<PsyagceEngine*>(GetEngine())->returnState() == 3)
	{
		m_iCurrentScreenX = 160;
		m_iCurrentScreenY = 105;
		for (int i = 0; i < 8; i++)
		{
			inventory.p[i]->Draw();
		}

	}
			if (im[animation].IsLoaded())
			{
				if (!turned)
					im[animation].RenderImageWithMask(GetEngine()->GetForeground(), 0, ((im[animation].GetHeight() / 20) * frame), m_iCurrentScreenX, m_iCurrentScreenY, im[animation].GetWidth(), (im[animation].GetHeight() / 20));
				else
					im[animation].RenderImageWithMask(GetEngine()->GetForeground(), 0, (im[animation].GetHeight() / 20) * frame + (im[animation].GetHeight() / 2), m_iCurrentScreenX, m_iCurrentScreenY, im[animation].GetWidth(), (im[animation].GetHeight() / 20));
			}
	
	
	StoreLastScreenPositionForUndraw();
	booster = 0;
	hitbox.sourceX = m_iCurrentScreenX;
	hitbox.sourceY = m_iCurrentScreenY;


	if (animation == 2)
	{
		m_iCurrentScreenY += 23;
		if (frame == 9)
			attacking = false;
	}

	idletimer--;

	if (actiontimer > 0)
		actiontimer--;

	m_iDrawHeight = (im[animation].GetHeight() / 20);
	m_iDrawWidth = im[animation].GetWidth();

	/*GetEngine()->DrawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + hitbox.width,
		m_iCurrentScreenY + hitbox.height,
		0x00ff00);*/

	if (stats.stamina < 120)
		stats.stamina = stats.stamina + 1;



}

void HeroObject::DoUpdate(int iCurrentTime)
{

	if (attackCounter > 0)
		attackCounter--;
//	std::cout << attackCounter << std::endl;
	stats.armor = 0 + (inventory.level * 10);
	inventory.agility = 10 + (inventory.level * 5);
	inventory.str = 10 + (inventory.level * 5);
	inventory.intelli = 10 + (inventory.level * 5);
	stats.baseAttack = 25 + (inventory.level * 5) + ((inventory.agility + inventory.str + inventory.intelli) / 100);

	for (int i = 0; i < 8; i++)
	{
		stats.baseAttack += inventory.p[i]->attack;
		stats.armor += inventory.p[i]->armor;
		inventory.agility += inventory.p[i]->agility;
		inventory.str += inventory.p[i]->str;
		inventory.intelli += inventory.p[i]->intelli;
	}
		


	if (inventory.exp >= 120)
	{
		inventory.level++;
		inventory.exp = inventory.exp % 120;
		static_cast<PsyagceEngine*>(GetEngine())->upAlert = 40;
	}

	IncrementFrame();

	if (actiontimer == 0 && static_cast<PsyagceEngine*>(GetEngine())->returnState() == 1)
	{
		/*if (GetEngine()->IsKeyPressed(SDLK_w))
		{
			m_iCurrentScreenY -= 3;
			animation = 1;
			idletimer = 20;
		}
		if (GetEngine()->IsKeyPressed(SDLK_s))
		{
			m_iCurrentScreenY += 3;
			animation = 1;
			idletimer = 20;
		}*/
		if (GetEngine()->IsKeyPressed(SDLK_e))
		{
			//printf("%d\n", jumping);
			if (!jumping && onGround)
			{
				jumping = true;
				animation = 4;
			}
		
			idletimer = 20;
		}

		if (GetEngine()->IsKeyPressed(SDLK_q))
		{
			if (attackCounter == 0)
			{
				animation = 2;
				idletimer = 10; // ticks before attack stop automatically
				actiontimer = 10; // ticks before you can manually stop attack
				iFrameCounter = 0;

				for (int x = 0; x < static_cast<PsyagceEngine*>(GetEngine())->objects; x++)
				{
					curr = static_cast<SpriteObject*>(GetEngine()->GetDisplayableObject(x));
					if (curr != NULL)
					{
						if (curr->isEnemy())
						{
							if (std::abs(this->hitbox.sourceY - curr->hitbox.sourceY) <= 30 && std::abs(this->hitbox.sourceX - curr->hitbox.sourceX) <= 70)
							{
								curr->setFight(true);
								curr->UpdateHealth(this->stats.baseAttack - curr->stats.armor);
								curr->UpdateFrame(0);

							}
							else
							{
								curr->setFight(false);
							}
						}
					}
				}


				attacking = true;
				attackCounter = 20;
			}
		}


		
	
		if (GetEngine()->IsKeyPressed(SDLK_SPACE))
		{
			if (stats.stamina > 0)
			{
				booster = 3;
				stats.stamina = stats.stamina - 2;
			}
		}
		
		if (GetEngine()->IsKeyPressed(SDLK_a))
		{
			if(!jumping && !attacking)
			animation = 1;

			if(turned == false)
				turned = true;
			
			m_iCurrentScreenX -= stats.speed + booster;
		
			idletimer = 25;

		}

		if (GetEngine()->IsKeyPressed(SDLK_d))
		{
			if (!jumping && !attacking)
			animation = 1;

			if (turned == true)
				turned = false;
			
		
					m_iCurrentScreenX += stats.speed + booster;
			

			idletimer = 25;

		}

		if (!jumping && static_cast<PsyagceEngine*>(GetEngine())->returnState() == 1)
		{
			Gravity();
		}

	}


	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;


/*	if (m_iCurrentScreenY < 375)
	m_iCurrentScreenY = 375;
	if (m_iCurrentScreenY > 480)
	m_iCurrentScreenY = 480;*/
	// Ensure that the object gets redrawn on the display, if something changed*/
//	printf("%d, %d, hero \n", this->hitbox.sourceY, this->hitbox.sourceX);
//	printf("%d hero\n", m_iCurrentScreenY);



	stamina->UpdateStats(stats.stamina, m_iCurrentScreenX, m_iCurrentScreenY);
	health->UpdateStats(stats.hp, m_iCurrentScreenX, m_iCurrentScreenY);
	exp->UpdateStats(inventory.exp, m_iCurrentScreenX, m_iCurrentScreenY);


		RedrawObjects();
	
}



void HeroObject::IncrementExp(int value)
{
	inventory.exp += value;
}
 
void HeroObject::InitInventory()
{


	currm[0] = new ImageData();
	currm[0]->LoadImage("hero/items/basicweapon.png");
	inventory.p[0] = new Equipment(GetEngine(), 0);
	inventory.p[0]->SetHero(currm[0]);

	currm[1] = new ImageData();
	currm[1]->LoadImage("hero/items/basicchest.png");
	inventory.p[1] = new Equipment(GetEngine(), 1);
	inventory.p[1]->SetHero(currm[1]);

	currm[2] = new ImageData();
	currm[2]->LoadImage("hero/items/basicgreave.png");
	inventory.p[2] = new Equipment(GetEngine(), 2);
	inventory.p[2]->SetHero(currm[2]);

	currm[3] = new ImageData();
	currm[3]->LoadImage("hero/items/basicbelt.png");
	inventory.p[3] = new Equipment(GetEngine(), 3);
	inventory.p[3]->SetHero(currm[3]);

	currm[4] = new ImageData();
	currm[4]->LoadImage("hero/items/basicgloves.png");
	inventory.p[4] = new Equipment(GetEngine(), 4);
	inventory.p[4]->SetHero(currm[4]);

	currm[5] = new ImageData();
	currm[5]->LoadImage("hero/items/basicbracelet.png");
	inventory.p[5] = new Equipment(GetEngine(), 5);
	inventory.p[5]->SetHero(currm[5]);

	currm[6] = new ImageData();
	currm[6]->LoadImage("hero/items/basichelmet.png");
	inventory.p[6] = new Equipment(GetEngine(), 6);
	inventory.p[6]->SetHero(currm[6]);

	currm[7] = new ImageData();
	currm[7]->LoadImage("hero/items/basicboots.png");
	inventory.p[7] = new Equipment(GetEngine(), 7);
	inventory.p[7]->SetHero(currm[7]);
}

