#include "header.h"
#include "templates.h"
#include "Equipment.h"
#include "PsyagceEngine.h"
#include "HeroObject.h"



Equipment::Equipment(BaseEngine* pEngine, int id)
	: DisplayableObject(pEngine)
{

	this->agility = 0;
	this->str = 0;
	this->intelli = 0;

	this->price = 300;
	desc = false;
	
	upgrade = 0;
	if(upgrade == 0)
		name == "Basic";
	type = id;

	
	switch (type)
	{
	case 0:
		typeitem = " Weapon";
		m_iCurrentScreenX = 151;
		m_iCurrentScreenY = 296;
		this->attack = 20;
		armor = 0;
		break;
	case 1:
		typeitem = " Chestplate";
		m_iCurrentScreenX = 235;
		m_iCurrentScreenY = 296;
		this->attack = 5;
		armor = 20;
		break;
	case 2:
		typeitem = " Greave";
		m_iCurrentScreenX = 235;
		m_iCurrentScreenY = 363;
		this->attack = 5;
		armor = 10;
		break;
	case 3:
		typeitem = " Belt";
		m_iCurrentScreenX = 317;
		m_iCurrentScreenY = 363;
		this->attack = 5;
		armor = 5;
		break;
	case 4:
		typeitem = " Gloves";
		m_iCurrentScreenX = 151;
		m_iCurrentScreenY = 363;
		this->attack = 5;
		armor = 5;
		break;
	case 5:
		typeitem = " Bracelet";
		m_iCurrentScreenX = 317;
		m_iCurrentScreenY = 296;
		this->attack = 0;
		armor = 5;
		break;
	case 6:
		typeitem = " Helmet";
		m_iCurrentScreenX = 235;
		m_iCurrentScreenY = 228;
		this->attack = 0;
		armor = 10;
		break;
	case 7:
		typeitem = " Boots";
		m_iCurrentScreenX = 235;
		m_iCurrentScreenY = 431;
		this->attack = 0;
		armor = 5;
		break;
	}


}


Equipment::~Equipment()
{
}

void Equipment::Draw()
{

		//std::cout << type << std::endl;
	
		pHero->RenderImage(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, pHero->GetWidth(), pHero->GetHeight());
		
		if (desc)
			PrintDesc();
	
}

void Equipment::DoUpdate()
{
	//std::cout << "Hello" << std::endl;
	RedrawObjects();
}

void Equipment::Upgrade()
{
	if (upgrade < 3)
	{
		if (static_cast<HeroObject*>(GetEngine()->GetDisplayableObject(0))->inventory.gold >= price)
			static_cast<HeroObject*>(GetEngine()->GetDisplayableObject(0))->inventory.gold -= price;
		std::cout << type << std::endl;
		attack += 10;
		price += 200;
		upgrade++;
		armor += 5;
		agility += 5;
		str += 5;
		intelli += 5;
	}

	
	LoadFrames();

	if (upgrade == 1)
		name = "Wizard's";
	if (upgrade == 2)
		name = "Ranger's";
	if (upgrade == 3)
		name = "Knight's";
}

void Equipment::SetName(std::string name)
{
	this->name = name;
}

void Equipment::SetAttack(int attack)
{
	this->attack = attack;
}

void Equipment::SetPrice(int price)
{
	this->price = price;
}

void Equipment::SetHero(ImageData* pHero)
{
	this->pHero = pHero;
}

bool Equipment::IsClicked(int iX, int iY)
{
	if (iX >= m_iCurrentScreenX && iX <= m_iCurrentScreenX + 64)
	{
		if (iY >= m_iCurrentScreenY && iY <= m_iCurrentScreenY + 64)
			return true;
		else
			return false;
	}
	else
		return false;

}

void Equipment::PrintDesc()
{
	GetEngine()->DrawForegroundRectangle(412, 230, 673, 501, 0xf5f5dc);

	pHero->RenderImage(GetEngine()->GetForeground(), 0, 0, 410, 228, pHero->GetWidth(), pHero->GetHeight());
	
	if (upgrade < 3)
	{
	buffer = "UP Price ";
	buffer += std::to_string(price);
	}
	else
	{
		buffer = "UP Compelete.";
	}
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(490, 240, buf, 0x000000, NULL);

	buffer = name + typeitem;
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 300, buf, 0x000000, NULL);

	buffer = "Attack ";
	buffer += std::to_string(attack);
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 340, buf, 0x000000, NULL);

	buffer = "Armor ";
	buffer += std::to_string(armor);
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 370, buf, 0x000000, NULL);

	buffer = "Agility ";
	buffer += std::to_string(agility);
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 400, buf, 0x000000, NULL);

	buffer = "Strength ";
	buffer += std::to_string(str);
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 430, buf, 0x000000, NULL);

	buffer = "Intelligence ";
	buffer += std::to_string(intelli);
	sprintf(buf, buffer.c_str());
	GetEngine()->DrawForegroundString(420, 460, buf, 0x000000, NULL);
	
}

void Equipment::LoadFrames()
{
	switch (type)
	{
	case 0:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicweapon.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard0.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight0.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger0.png");
		break;
	case 1:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicchest.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard1.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight1.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger1.png");
		break;
	case 2:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicgreave.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard2.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight2.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger2.png");
		break;
	case 3:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicbelt.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard3.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight3.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger3.png");
		break;
	case 4:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicgloves.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard4.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight4.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger4.png");
		break;
	case 5:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicbracelet.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard5.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight5.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger5.png");
		break;
	case 6:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basichelmet.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard6.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight6.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger6.png");
		break;
	case 7:
		if(upgrade == 0)
			pHero->LoadImage("hero/items/basicboots.png");
		if (upgrade == 1)
			pHero->LoadImage("hero/items/wizard7.png");
		if (upgrade == 2)
			pHero->LoadImage("hero/items/knight7.png");
		if (upgrade == 3)
			pHero->LoadImage("hero/items/ranger7.png");
		break;

	}
}