#include "header.h"
#include "templates.h"
#include "StatsBar.h"



StatsBar::StatsBar(BaseEngine* pEngine, int startval, std::string stat, int m_iPosX, int m_iPosY)
	: DisplayableObject(pEngine)
{
	m_pMainEngine = pEngine;
	current = startval;
	m_iStartDrawPosX =  0;
	name = stat;

	if (name == "stamina")
	{
		uiColor = 0xff751a;
		m_iStartDrawPosY = m_iPosY;
		m_iStartDrawPosX = m_iPosX;
		m_iDrawHeight = m_iStartDrawPosY + 7;
	}
	else if (name == "health")
	{
		uiColor = 0xff1a1a;
		m_iStartDrawPosY = m_iPosY - 10;
		m_iStartDrawPosX = m_iPosX;
		m_iDrawHeight = m_iStartDrawPosY + 7;
	}
	else if (name == "exp")
	{
		uiColor = 0x00cc00;
		m_iStartDrawPosY = m_iPosY - 20;
		m_iStartDrawPosX = m_iPosX;
		m_iDrawHeight = m_iStartDrawPosY + 7;
	}
		
	



	SetVisible(true);
}


StatsBar::~StatsBar()
{
}

	void StatsBar::Draw()
	{
		if (name == "health") 
		{
			buffer = "Health: " + std::to_string(current);
			sprintf(buf, buffer.c_str());
			m_pMainEngine->DrawForegroundString(m_iStartDrawPosX, m_iStartDrawPosY - 40, buf, uiColor, NULL);
		}
		
		m_pMainEngine->DrawForegroundRectangle(m_iStartDrawPosX, m_iStartDrawPosY, current + m_iStartDrawPosX, m_iDrawHeight, uiColor);
		
		StoreLastScreenPositionForUndraw();
	}

	void StatsBar::DoUpdate(int iCurrentTime)
	{

	}

	void StatsBar::UpdateStats(int newval, int posX, int posY)
	{
		if (newval < 0)
			current = 0;
		else
			current = newval;




		if (name == "exp")
			m_iStartDrawPosY = posY - 20;
		else if (name == "health")
			m_iStartDrawPosY = posY - 10;
		else if (name == "stamina")
			m_iStartDrawPosY = posY;
		

		m_iDrawHeight = m_iStartDrawPosY + 7;
		m_iStartDrawPosX = posX;

	}
