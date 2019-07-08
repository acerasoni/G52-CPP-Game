#pragma once
#include "DisplayableObject.h"
#include "header.h"
#include "templates.h"

class PsyagceEngine;

class ArrowObject :
	public DisplayableObject
{
public:
	ArrowObject(PsyagceEngine* pEngine, int iX, int iY);
	~ArrowObject();

	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	int m_iColour;

	PsyagceEngine* m_pMainEngine;
};

