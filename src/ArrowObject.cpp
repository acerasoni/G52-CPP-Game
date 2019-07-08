#include "header.h"
#include "templates.h"
#include "ArrowObject.h"
#include "PsyagceEngine.h"


ArrowObject::ArrowObject(PsyagceEngine* pEngine, int iX, int iY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -50;
	m_iStartDrawPosY = -50;

	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;

	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = iX;
	m_iPreviousScreenY = m_iCurrentScreenY = iY;

	m_iColour = 0x8d94a0;

	// And make it visible
	SetVisible(true);
}


ArrowObject::~ArrowObject()
{
}


void ArrowObject::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	m_pMainEngine->DrawForegroundOval(
		m_iCurrentScreenX - 50,
		m_iCurrentScreenY - 50,
		m_iCurrentScreenX + 49,
		m_iCurrentScreenY + 49,
		m_iColour /*rand() % 0xffffff*/);

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();
}


void ArrowObject::DoUpdate(int iCurrentTime)
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	m_iCurrentScreenX = m_iPreviousScreenX + 1;

	printf("%d, %d", m_iPreviousScreenX, m_iPreviousScreenX);
	//m_iCurrentScreenY = m_iPreviousScreenY + 1;

	//m_iCurrentScreenX = m_iPreviousScreenX + (rand() % 121 - 60) / 30;
	//m_iCurrentScreenY = m_iPreviousScreenY + (rand() % 121 - 60) / 30;

	// Ensure not off the screen
	if (m_iCurrentScreenX < 50)
		m_iCurrentScreenX = 50;
	if (m_iCurrentScreenX >= 1150)
		m_iCurrentScreenX = 1150;
	if (m_iCurrentScreenY >= 550)
		m_iCurrentScreenY = 550;
	if (m_iCurrentScreenY < 50)
		m_iCurrentScreenY = 50;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}