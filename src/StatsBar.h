#pragma once
#include "DisplayableObject.h"
#include "PsyagceEngine.h"
#include <string>

class StatsBar :
	public DisplayableObject
{
public:
	StatsBar(BaseEngine* pEngine, int startval, std::string stat, int m_iPosX, int m_iPosY);
	~StatsBar();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void UpdateStats(int newval, int posX, int posY);
	int current;

private:

	
	BaseEngine* m_pMainEngine;
	unsigned int uiColor;
	std::string name;
	std::string buffer;
	char buf[128];
};

