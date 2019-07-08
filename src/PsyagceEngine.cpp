#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "PsyagceEngine.h"
#include "BaseEngine.h"
#include "PsyagceTileManager.h"
#include "TileManager.h"
#include "ArrowObject.h"
#include "HeroObject.h"
#include "EnemyObject.h"
#include <string>
#include "Demo4Object.h"
#include <iostream>
#include <time.h> 

PsyagceEngine::PsyagceEngine()
	: upAlert(0), old(0), oldX(0), oldY(0), saveAlert(0), iFrameCounter(0), iFrame(0), frame(0), m_state(stateInit)
{

	map = "forest";
	iFrameRate = 4; // Framerate for animated background

	platDirection[0] = true; // true right, false left
	platDirection[1] = false;

	ifstream in("settings/settings.txt", ios::in);
	in >> mode;

	int number;
	while (in >> number) {
		//Add the number to the end of the array
		PlatformPos.push_back(number);
	}
	in.close();

}


PsyagceEngine::~PsyagceEngine()
{
}


void PsyagceEngine::SetupBackgroundBuffer()
{
	
	switch (m_state)
	{
	case stateInit:

		FillBackground(0);
		im.LoadImage("backgrounds/startscreen.png");
		im.RenderImage(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
		
		{
			const char* data[] = {
				
				"bbbbbbbbbbbbbbbbbbbbbbbbbbbb",
				"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaaaaaaaaaaaaaaa" };

			// Specify how many tiles wide and high
			m_oTiles.SetSize(28, 4);
			// Set up the tiles
			for (int x = 0; x < 28; x++)
				for (int y = 0; y < 4; y++)
					m_oTiles.SetValue(x, y, data[y][x] - 'a');

			const char plata[] = {
				"bbbbbb",
			 };

			m_oPlatform.SetSize(6, 1);
			// Set up the tiles
			for (int x = 0; x < 6; x++)
					m_oPlatform.SetValue(x, 0, plata[x] - 'a');

			m_oPlatformTwo.SetSize(6, 1);
			// Set up the tiles
			for (int x = 0; x < 6; x++)
				m_oPlatformTwo.SetValue(x, 0, plata[x] - 'a');

			m_oInventory.SetSize(1, 1);
			m_oPause.SetSize(1, 1);
			m_oSave.SetSize(1, 1);
			m_oHelp.SetSize(1, 1);
			// Set up the tiles
			m_oPause.SetValue(0, 0, 2);
			m_oInventory.SetValue(0, 0, 3);
			m_oSave.SetValue(0, 0, 4);
			m_oHelp.SetValue(0, 0, 5);
	
		}
			// Specify the screen x,y of top left corner
			m_oTiles.SetBaseTilesPositionOnScreen(0, 460);
			m_oPlatform.SetBaseTilesPositionOnScreen(PlatformPos[0], 400);
			m_oPlatformTwo.SetBaseTilesPositionOnScreen(PlatformPos[1], 300);
			m_oInventory.SetBaseTilesPositionOnScreen(780, 10);
			m_oPause.SetBaseTilesPositionOnScreen(860, 10);
			m_oSave.SetBaseTilesPositionOnScreen(940, 10);
			m_oHelp.SetBaseTilesPositionOnScreen(1020, 10);
			LoadBackground();	
			
			break;
			
		

	case stateMain:
		FillBackground(0);

		//buffer = "backgrounds/" + map + ".png";
		//sprintf(buf, buffer.c_str());
	
		 
		background[frame].RenderImage(this->GetBackground(), 0, 0, 0, 0, 1120, background[frame].GetHeight());

		m_oTiles.DrawAllTiles(this,this->GetBackground(),0, 0, 27, 2);
		m_oPlatform.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		m_oPlatformTwo.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		m_oInventory.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oPause.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oSave.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oHelp.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		return;
	case statePaused:
		FillBackground(0);
		im.LoadImage("backgrounds/pause.png");
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 304, 54, im.GetWidth(), im.GetHeight());
		m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 27, 2);
		m_oPlatform.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		m_oPlatformTwo.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		//m_oInventory.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oPause.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		//m_oSave.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		//m_oHelp.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		break;
	case stateMenu:
		FillBackground(0);
		background[frame].RenderImage(this->GetBackground(), 0, 0, 0, 0, 1120, background[frame].GetHeight());
		m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 27, 2);
		m_oPlatform.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		m_oPlatformTwo.DrawAllTiles(this, this->GetBackground(), 0, 0, 5, 0);
		m_oInventory.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oPause.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oSave.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		m_oHelp.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 0);
		DrawBackgroundRectangle(120, 58, 1000, 522, 0xf5f5dc);
		DrawBackgroundRectangle(120, 58, 1000, 78, 0x000000);
		DrawBackgroundRectangle(120, 58, 140, 522, 0x000000);
		DrawBackgroundRectangle(120, 502, 1000, 522, 0x000000);
		DrawBackgroundRectangle(980, 78, 1000, 522, 0x000000);
		DrawBackgroundRectangle(290, 78, 310, 193, 0x000000);
		DrawBackgroundRectangle(120, 193, 310, 213, 0x000000);
		im.LoadImage("hero/items/armorplace.png");
		im.RenderImageWithMask(GetBackground(), 0, 0, 410, 228, im.GetWidth(), im.GetHeight());
		DrawBackgroundRectangle(410, 218, 683, 228, 0x000000);
		DrawBackgroundRectangle(400, 218, 410, 501, 0x000000);
		DrawBackgroundRectangle(684, 218, 694, 501, 0x000000);
		break;
	case stateEnd:
		im.LoadImage("background/dead.png");
		im.RenderImage(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
	
	}
}

void PsyagceEngine::MouseDown(int iButton, int iX, int iY)
{
	std::cout << iX << " " << iY << std::endl;
	int price = 0;
	int gold = static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.gold;
	int count = -10;
		 
	switch (m_state)
	{
	case stateInit:
		if(iX > 69 && iY > 373)
		if(iX < 155 && iY < 406)
			SetExitWithCode(0);

		if (iX > 69 && iY > 312) {
			if (iX < 289 && iY < 349)
			{
				// Go to state main
				m_state = stateMain;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
			
			}
		}


		if (iX > 69 && iY > 252)
		{
			if (iX < 284 && iY < 289)
			{
						NewGame();
						LoadStats();
					// Go to state main
				m_state = stateMain;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				
			}
			
		}
			

	
		break;
	case stateMain:
	case stateMenu:
	case statePaused:
		for (int i = 0; i < 8; i++)
		{
			if (static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc)
			{
				price = static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->price;
				count = i;
			}
			std::cout << count << std::endl;
		}
		for (int i = 0; i < 8; i++)
		{
			if (static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->IsClicked(iX, iY))
			{
				if (static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc)
					static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc = false;
				else
					static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc = true;
			}
			else
				static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc = false;

		}
		if (iX >= 945 && iX <= 945 + 32)
		{
			if (iY >= 460 && iY <= 460 + 32)
			{
				//std::cout << gold << price << std::endl;
				if (gold >= price)
				{

					if (count >= 0)
					{
						static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[count]->Upgrade();
						static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[count]->desc = true;
					}
				}

			}
		}
		//std::cout << iX << iY << std::endl;
		if (m_oInventory.IsValidTilePosition(iX, iY))
		{

			switch (m_state) {
			case stateMain:
				// Go to state menu
				m_state = stateMenu;
				oldX = static_cast<HeroObject*>(GetDisplayableObject(0))->ReturnX();
				oldY = static_cast<HeroObject*>(GetDisplayableObject(0))->ReturnY();
				for (int i = 1; i < objects; i++)
				{
					static_cast<EnemyObject*>(GetDisplayableObject(i))->hidden = true;
				}
				static_cast<HeroObject*>(GetDisplayableObject(0))->updatePosition(160, 105);
				static_cast<HeroObject*>(GetDisplayableObject(0))->idletimer = 0;
				old = static_cast<HeroObject*>(GetDisplayableObject(0))->turned;
				static_cast<HeroObject*>(GetDisplayableObject(0))->turned = false;
				// Work out what this does. 
				m_iPauseStarted = GetTime();
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			case stateMenu:
				// Go to state main
				m_state = stateMain;
				static_cast<HeroObject*>(GetDisplayableObject(0))->updatePosition(oldX, oldY);
				static_cast<HeroObject*>(GetDisplayableObject(0))->turned = old;
				for (int i = 1; i < objects; i++)
				{
					static_cast<EnemyObject*>(GetDisplayableObject(i))->hidden = false;
				}
				// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
				IncreaseTimeOffset(m_iPauseStarted - GetTime());
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;

			case statePaused:
				break;
			}
		}

		if (m_oPause.IsValidTilePosition(iX, iY))
		{
			switch (m_state) {
			case stateMain:
				// Go to state paused
				m_state = statePaused;
				// Work out what this does. 
				m_iPauseStarted = GetTime();
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			case statePaused:
				// Go to state main
				m_state = stateMain;
				// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
				IncreaseTimeOffset(m_iPauseStarted - GetTime());
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			}
		}

		if (m_oHelp.IsValidTilePosition(iX, iY))
			printf("Help\n");
		if (m_oSave.IsValidTilePosition(iX, iY))
		{
			saveAlert = 50;
			SaveStats();
		}
		break;
	}
	

}




int PsyagceEngine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(4);
	objects = 4;
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
		// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
		// order to work out where the end of the array is.
		//StoreObjectInArray(0, new HeroObject(this));
	srand(time(NULL));
	int speed = rand() % 4;
		StoreObjectInArray(0, new HeroObject(this, 600, 300));
		StoreObjectInArray(1, new EnemyObject(this, 800, 300, 1, speed));
		speed = rand() % 4;
		StoreObjectInArray(2, new EnemyObject(this, 600, 300, 2, speed ));
		speed = rand() % 4;
		StoreObjectInArray(3, new EnemyObject(this, 400, 300, 3, speed));
     	StoreObjectInArray(4, NULL);

		LoadStats();

	return 0;
}

void PsyagceEngine::UnDrawStrings()
{
	// Clear the top of the screen, since we about to draw text on it.
	CopyBackgroundPixels(0, 0, GetWindowWidth(), GetWindowHeight());
}

void PsyagceEngine::DrawStringsUnderneath()
{
	switch (m_state)
	{
	case stateInit:
		break;
	case stateMain:
		break;
	case statePaused:
		DrawForegroundString(420, 50, "Paused. Click unpause to continue", 0xffffff, NULL);
		break;
	}

	
}

void PsyagceEngine::KeyDown(int iKeyCode)
{
	// NEW SWITCH on current state
	switch (iKeyCode)
	{
	//case SDLK_ESCAPE: // End program when escape is pressed
	//	SaveStats();
	//	SetExitWithCode(0);
	//	break;
	case SDLK_ESCAPE: // End program when escape is pressed
		//for (int i = 0; i < objects; i++)
		//{
		//	delete static_cast<SpriteObject*>(GetDisplayableObject(i));
		//}
		CleanUp();
		SetExitWithCode(0);
		break;
	case SDLK_p: // SPACE Pauses
		switch (m_state)
		{
		//case stateInit:
			// Go to state main
		//	m_state = stateMain;
			// Force redraw of background
		//	SetupBackgroundBuffer();
			// Redraw the whole screen now
		//	Redraw(true);
		//	break;
		case stateMain:
			// Go to state paused
			m_state = statePaused;
			// Work out what this does. 
			m_iPauseStarted = GetTime();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case statePaused:
			// Go to state main
			m_state = stateMain;
			// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
			IncreaseTimeOffset(m_iPauseStarted - GetTime());
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		} // End switch on current state
		break; // End of case SPACE
	}
}
/* Overridden GameAction which can be modified */

void PsyagceEngine::DrawStringsOnTop()
{

	switch (m_state)
	{
	case stateMain:
		if (upAlert > 0)
		{
			DrawForegroundString(450, 80, "Level UP", 0x000000, NULL);
			upAlert--;
		}
		
		if (saveAlert > 0)
		{
			DrawForegroundString(450, 50, "Game saved", 0xffffff, NULL);
			saveAlert--;
		}
		break;
	case stateMenu:
		
		buffer = "Name: " + static_cast<HeroObject*>(GetDisplayableObject(0))->name;
		sprintf(buf, buffer.c_str());
		DrawForegroundString(330, 90, buf, 0x000000, NULL);

		buffer = "Level: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.level);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(560, 90, buf, 0x000000, NULL);

		buffer = "Gold: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.gold);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(730, 90, buf, 0x000000, NULL);

		buffer = "HP: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.hp);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(330, 130, buf, 0x000000, NULL);

		buffer = "Exp: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.exp);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(330, 170, buf, 0x000000, NULL);

		DrawForegroundRectangle(470, 135, 950, 160, 0xff9999);
		DrawForegroundRectangle(470, 135, 470 + ((470 / 100) * ((static_cast<HeroObject*>(GetDisplayableObject(0))->stats.hp / 12) * 10)), 160, 0xff1a1a);

		DrawForegroundRectangle(470, 175, 950, 200, 0xb0f442);
		DrawForegroundRectangle(470, 175, 470 + ((470 / 100) * ((static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.exp / 12) * 10)), 200, 0x00cc00);

		im.LoadImage("hero/items/gold.png");
		im.RenderImageWithMask(GetForeground(), 0, 0, 945, 460, im.GetWidth(), im.GetHeight());
		
		DrawForegroundRectangle(740, 463, 940, 488, 0xF0E68C);
		int price = 0;
		int gold = static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.gold;
		for (int i = 0; i < 8; i++)
		{
			if (static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->desc)
				price = static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->price;
		}


		if (price != 0)
		{
			if (gold > price)
				gold = price;
			//std::cout << 740 + ((200 / 100) * (gold / (price / 100))) << std::endl;
			DrawForegroundRectangle(740, 463, 740 + ((200/100) * (gold / (price/100))), 488, 0xFFD700);
		}
		

		/*buffer = "Attack: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.baseAttack);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(400, 228, buf, 0x000000, NULL);

		buffer = "Armor: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.armor);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(400, 270, buf, 0x000000, NULL);

		buffer = "Speed: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.speed);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(400, 312, buf, 0x000000, NULL);*/

		im.LoadImage("hero/items/placeholder.png");
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 130, 225, im.GetWidth(), im.GetHeight());

		buffer = "Hero Statistics";
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 218, buf, 0x000000, NULL);

		buffer = "Attack: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.baseAttack);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 258, buf, 0x000000, NULL);


		buffer = "Armor: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->stats.armor);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 298, buf, 0x000000, NULL);


		buffer = "Agility: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.agility);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 338, buf, 0x000000, NULL);


		buffer = "Strength: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.str);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 378, buf, 0x000000, NULL);


		buffer = "Intelligence: " + std::to_string(static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.intelli);
		sprintf(buf, buffer.c_str());
		DrawForegroundString(740, 418, buf, 0x000000, NULL);


		//DrawForegroundRectangle(470, 135, 950, 160, 0xdb6030);
		//DrawForegroundRectangle(470, 175, 950, 200, 0x000000);
		break;
	}
}

void PsyagceEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToActWithSleep())
		return;

	// Don't act for another 15 ticks
	SetTimeToAct(25);

	switch (m_state)
	{
	case stateInit:
	case statePaused:
		break;
	case stateMenu:
		static_cast<HeroObject*>(GetDisplayableObject(0))->updatePosition(160, 105);
		static_cast<HeroObject*>(GetDisplayableObject(0))->animation = 1;
		GetDisplayableObject(0)->DoUpdate(GetModifiedTime());
		break;
	case stateMain:
		UpdateBackground();
		// Tell all objects to update themselves
		UpdateAllObjects(GetModifiedTime());
		if (static_cast<HeroObject*>(GetDisplayableObject(0))->stats.hp <= 0)
		{
			SetExitWithCode(0);
		}
		break;
	}


}

void PsyagceEngine::UpdateBackground()
{
	
	iFrameCounter++;
	if (iFrameCounter % iFrameRate == 0)
	{
		iFrame++;
		frame = iFrame % 8;
		SetupBackgroundBuffer();
		Redraw(true);
	}

	//printf("%d\n", parallaxOffset);
}

void PsyagceEngine::UndrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::UndrawObjects();
}

void PsyagceEngine::DrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::DrawObjects();
}

/*void PsyagceEngine::DeleteEnemy(int enemy)
{
	//delete static_cast<EnemyObject*> (GetDisplayableObject(enemy));
	StoreObjectInArray(enemy, NULL);
}*/

void PsyagceEngine::LoadBackground()
{
	/*for (int i = 0; i < 60; i++)
	{
		if (i < 10)
		{
			buffer = "backgrounds/frames/frame_0";
			buffer += std::to_string(i) + "_delay-0.03s.png";
			std::cout << buffer << std::endl;
		}
		else
		{
			buffer = "backgrounds/frames/frame_";
			buffer += std::to_string(i) + "_delay-0.03s.png";
			std::cout << buffer << std::endl;
		}
		
		sprintf(buf, buffer.c_str());
		background[i].LoadImage(buf);
	}*/
	background[0].LoadImage("backgrounds/frames/1.png");
	background[1].LoadImage("backgrounds/frames/2.png");
	background[2].LoadImage("backgrounds/frames/3.png");
	background[3].LoadImage("backgrounds/frames/4.png");
	background[4].LoadImage("backgrounds/frames/5.png");
	background[5].LoadImage("backgrounds/frames/6.png");
	background[6].LoadImage("backgrounds/frames/7.png");
	background[7].LoadImage("backgrounds/frames/8.png");
}

bool PsyagceEngine::CheckTiles(int iPosX, int iPosY)
{
	if (m_oTiles.IsValidTilePosition(iPosX, iPosY+1))
	{
		return true;
	}
	else if(m_oPlatform.IsValidTilePosition(iPosX, iPosY + 1) ){
		return true;
	}
	else if (m_oPlatformTwo.IsValidTilePosition(iPosX, iPosY + 1)) {
		return true;
	}
	else {
		return false;
	}
}

void PsyagceEngine::SaveStats()
{
	HeroObject* curr = static_cast<HeroObject*> (GetDisplayableObject(0));
	ofstream myfile("settings/player.txt");
	if (myfile.is_open())
	{
		myfile << (curr)->ReturnX();
		myfile << "\n";
		myfile << (curr)->ReturnY();
		myfile << "\n";
		myfile << (curr)->turned;
		myfile << "\n";
		myfile << (curr)->jumping;
		myfile << "\n";
		myfile << (curr)->iJumpTimer;
		myfile << "\n";
		myfile << (curr)->jump;
		myfile << "\n";
		myfile << curr->stats.hp;
		myfile << "\n";
		myfile << curr->inventory.gold; 
		myfile << "\n";
		myfile << curr->inventory.level;
		myfile << "\n";
		myfile << curr->inventory.exp;
		myfile << "\n";
		myfile << curr->name;
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";

	Equipment* curre;
	ofstream myfile1("settings/equipments.txt");

	for (int i = 0; i < 8; i++)
	{
		curre = curr->inventory.p[i];
		if (myfile1.is_open())
		{
			myfile1 << curre->attack;
			myfile1 << "\n";
			myfile1 << curre->price;
			myfile1 << "\n";
			myfile1 << curre->upgrade;
			myfile1 << "\n";
			myfile1 << curre->armor;
			myfile1 << "\n";
			myfile1 << curre->agility;
			myfile1 << "\n";
			myfile1 << curre->str;
			myfile1 << "\n";
			myfile1 << curre->intelli;
			myfile1 << "\n";
			myfile1 << curre->desc;
			myfile1 << "\n";
			myfile1 << curre->type;
			myfile1 << "\n";
			myfile1 << curre->name;
			myfile1 << "\n";
		}
		else cout << "Unable to open file";
	}

	myfile1.close();


	ofstream myfile2("settings/enemy.txt");

	EnemyObject* currs;
	for (int i = 1; i < objects; i++)
	{
		currs = static_cast<EnemyObject*> (GetDisplayableObject(i));

		
		if (myfile2.is_open())
		{
			myfile2 << currs->ReturnX();
			myfile2 << "\n";
			myfile2 << currs->ReturnY();
			myfile2 << "\n";
			myfile2 << currs->turned;
			myfile2 << "\n";
			myfile2 << currs->jumping;
			myfile2 << "\n";
			myfile2 << (currs)->iJumpTimer;
			myfile2 << "\n";
			myfile2 << currs->jump;
			myfile2 << "\n";
			myfile2 << currs->stats.hp;
			myfile2 << "\n";
			myfile2 << currs->expvalue;
			myfile2 << "\n";
			myfile2 << currs->id;
			myfile2 << "\n";

			std::cout << currs->ReturnX() << " " << currs->ReturnY() << std::endl;
		}
		else cout << "Unable to open file";

		}
	myfile2.close();
	

	ofstream myfile3("settings/settings.txt");
	if (myfile3.is_open())
	{
		myfile3 << mode;
		myfile3 << "\n";
		myfile3 << PlatformPos[0];
		myfile3 << "\n";
		myfile3 << PlatformPos[1];
		myfile3 << "\n";
		myfile3.close();
	}
	else cout << "Unable to open file";
	}

void PsyagceEngine::LoadStats()
{
	HeroObject* curr = static_cast<HeroObject*> (GetDisplayableObject(0));
	
	ifstream in("settings/player.txt", ios::in);
	if (!in) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}
	int n = 0;
		in >> n;
		(curr)->SetX(n);
		in >> n;
		(curr)->SetY(n);
		in >> (curr)->turned;
		in >> (curr)->jumping;
		in >> (curr)->iJumpTimer;
		in >> (curr)->jump;
		in >> curr->stats.hp;
		in >> curr->inventory.gold;
		in >> curr->inventory.level;
		in >> curr->inventory.exp;
		in >> curr->name;
			in.close();

			
	Equipment* curre;
	ifstream in2("settings/equipments.txt", ios::in);
	if (!in2) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	for (int i = 0; i < 8; i++)
	{
		curre = curr->inventory.p[i];
		
		in2 >> curre->attack;
		in2 >> curre->price;
		in2 >> curre->upgrade;
		in2 >> curre->armor;
		in2 >> curre->agility;
		in2 >> curre->str;
		in2 >> curre->intelli;
		in2 >> curre->desc;
		in2 >> curre->type;
		in2 >> curre->name;
		curr->inventory.p[i]->LoadFrames();
	}

	in2.close();

	EnemyObject* currs;
	ifstream in3("settings/enemy.txt", ios::in);
	if (!in3) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	for (int i = 1; i < objects; i++)
	{
		currs = static_cast<EnemyObject*> (GetDisplayableObject(i));

		in3 >> n;
		currs->SetX(n);
		in3 >> n;
		currs->SetY(n);
		in3 >> currs->turned;
		in3 >> currs->jumping;
		in3 >> (currs)->iJumpTimer;
		in3 >> currs->jump;
		in3 >> currs->stats.hp;
		in3 >> currs->expvalue;
		in3 >> currs->id;
	}

	in3.close();

			
	}


	

void PsyagceEngine::UpdatePlatforms()
{
	for (int i = 0; i < 2; i++)
	{
		if (platDirection[i])
			PlatformPos[i] += 1;
		else
			PlatformPos[i] -= 1;

	}
	

	if (PlatformPos[0] < 0)
	{
		PlatformPos[0] = 0;
		platDirection[0] = true;
	}
	if (PlatformPos[1] < 0)
	{
		PlatformPos[1] = 0;
		platDirection[1] = true;
	}
	if (PlatformPos[0] >= GetWindowWidth() - 250)
	{
		PlatformPos[0] = GetWindowWidth() - 250;
		platDirection[0] = false;
	}
	if (PlatformPos[1] >= GetWindowWidth() - 250)
	{
		PlatformPos[1] = GetWindowWidth() - 250;
		platDirection[1] = false;
	}

		m_oPlatform.SetBaseTilesPositionOnScreen(PlatformPos[0], 400);
		m_oPlatformTwo.SetBaseTilesPositionOnScreen(PlatformPos[1], 300);

}


int PsyagceEngine::returnState()
{
	return m_state;
}
 

void PsyagceEngine::CleanUp()
{


	for (int i = 0; i < 8; i++)
	{
		//std::cout << "free background " << std::endl;
		background[i].FreeData();

	}

	im.FreeData();
	

	//im2.FreeData();
	//im2.FreeData();
	//std::cout << "free im2" << std::endl;
	m_oTiles.FreeFrames();
	m_oPlatform.FreeFrames();
	m_oPlatformTwo.FreeFrames();
	m_oInventory.FreeFrames();
	m_oPause.FreeFrames();
	m_oSave.FreeFrames();
	m_oHelp.FreeFrames();
	DestroyOldObjects();
}

void PsyagceEngine::NewGame()
{
	ofstream myfile("settings/player.txt");

		if (myfile.is_open())
		{
			myfile << 300;
			myfile << "\n";
			myfile << 300;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 120;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << 0;
			myfile << "\n";
			myfile << "Paladinus";
		}
		else cout << "Unable to open file";

		myfile.close();



		ofstream myfile1("settings/equipments.txt");

		for (int i = 0; i < 8; i++)
		{
			if (myfile1.is_open())
			{
				myfile1 << 5;
				myfile1 << "\n";
				myfile1 << 200;
				myfile1 << "\n";
				myfile1 << 0;
				myfile1 << "\n";
				myfile1 << 5;
				myfile1 << "\n";
				myfile1 << 2;
				myfile1 << "\n";
				myfile1 << 2;
				myfile1 << "\n";
				myfile1 << 2;
				myfile1 << "\n";
				myfile1 << 0;
				myfile1 << "\n";
				myfile1 << i;
				myfile1 << "\n";
				myfile1 << "Basic";
				myfile1 << "\n";
				static_cast<HeroObject*>(GetDisplayableObject(0))->inventory.p[i]->LoadFrames();
			}
			else cout << "Unable to open file";
		}

		myfile1.close();


		ofstream myfile2("settings/enemy.txt");
		if (myfile2.is_open())
		{
			for (int i = 1; i < 4; i++)
			{
				myfile2 << 500;
				myfile2 << "\n";
				myfile2 << 200;
				myfile2 << "\n";
				myfile2 << 1;
				myfile2 << "\n";
				myfile2 << 0;
				myfile2 << "\n";
				myfile2 << 0;
				myfile2 << "\n";
				myfile2 << 0;
				myfile2 << "\n";
				myfile2 << 150;
				myfile2 << "\n";
				myfile2 << 50;
				myfile2 << "\n";
				myfile2 << i;
				myfile2 << "\n";
			}
		}

		else cout << "Unable to open file";

		myfile1.close();

		ofstream myfile3("settings/settings.txt");
		if (myfile3.is_open())
		{
			myfile3 << 2;
			myfile3 << "\n";
			myfile3 << 200;
			myfile3 << "\n";
			myfile3 << 300;
			myfile3 << "\n";
			myfile3.close();
		}
		else cout << "Unable to open file";
}

void PsyagceEngine::SetState(int state)
{
	switch (state)
	{
	case 0:
		m_state = stateInit;
		break;
	case 1:
		m_state = stateMain;
		break;
	case 2:
		m_state = statePaused;
		break;
	case 3:
		m_state = stateMenu;
		break;
	case 4:
		m_state = stateEnd;
		break;
	}
	
}