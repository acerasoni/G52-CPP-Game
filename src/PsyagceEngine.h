#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "JPGImage.h"
#include "PsyagceTileManager.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class PsyagceEngine :
	public BaseEngine
{
public:
	PsyagceEngine();
	~PsyagceEngine();
	void SetupBackgroundBuffer();
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
	void DrawStringsUnderneath();
	void UnDrawStrings();
	void DrawStringsOnTop();
	int InitialiseObjects();
	int SpriteCounter;
	vector<int> PlatformPos;
	void GameAction();
	void UpdateBackground();
	void LoadBackground();
	void UndrawObjects();
	void CleanUp();
	void DrawObjects();
	bool CheckTiles(int iPosX, int iPosY);
	void SaveStats();
	void LoadStats();
	void UpdatePlatforms();
	void NewGame();
	void SetState(int state);

	std::string map, buffer;
	char buf[128];
	int mode; // [0] mode 0 = easy, 1 = medium, 2 = hard, [1]
	//vector<EnemyObject*> enemies; // Enemies loaded up from saved file.

	enum State { stateInit, stateMain, statePaused, stateMenu, stateEnd };
	int returnState();
	int m_iPauseStarted;
	int objects;
	int oldY, oldX;
	int upAlert;
	int frame, old;
	bool platDirection[2];
	PsyagceTileManager& GetTileManager() { return m_oTiles; }
	//PsyagceTileManager& GetTileManager() { return m_oPlatform; } 
	PsyagceTileManager m_oPlatform;
	PsyagceTileManager m_oPlatformTwo;

private:
	PsyagceTileManager m_oTiles;
	PsyagceTileManager m_oInventory;
	PsyagceTileManager m_oPause;
	PsyagceTileManager m_oSave;
	PsyagceTileManager m_oHelp;
	
	ImageData im;
	ImageData background[8];
	int iFrameCounter, iFrameRate, iFrame, saveAlert;

	State m_state;
};

