#include "header.h"

#include "PsyagceTileManager.h"



PsyagceTileManager::PsyagceTileManager(void)
	: TileManager(40, 40)
{
	id = 0;
	grass.LoadImage("tiles/grass.png");
	dirt.LoadImage("tiles/dirt.png");
	pause.LoadImage("tiles/pause.png");
	inventory.LoadImage("tiles/inventory.png");
	help.LoadImage("tiles/help.png");
	save.LoadImage("tiles/save.png");
}


PsyagceTileManager::~PsyagceTileManager()
{
	std::cout << "~PsyagceTileManager" << std::endl;
	grass.FreeData();
	dirt.FreeData();
	pause.FreeData();
	inventory.FreeData();
	help.FreeData();
	save.FreeData();
}

void PsyagceTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{

	// New implementation draws things of different sizes
	switch (GetValue(iMapX, iMapY))
	{
	case 0:
		dirt.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, dirt.GetWidth(), dirt.GetHeight());
		break;
	case 1:
		grass.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, grass.GetWidth(), grass.GetHeight());
		break;
	case 2:
		pause.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, pause.GetWidth(), pause.GetHeight());
		break;
	case 3:
		inventory.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, inventory.GetWidth(), inventory.GetHeight());
		break;
	case 4:
		save.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, save.GetWidth(), save.GetHeight());
		break;
	case 5:
		help.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, save.GetWidth(), save.GetHeight());
		break;
	case 6:
	case 7:
	case 8:
		break;
	}
}

void PsyagceTileManager::SetID(int id)
{
	this->id = id;
}

void PsyagceTileManager::FreeFrames()
{
	grass.FreeData();
	dirt.FreeData();
	pause.FreeData();
	inventory.FreeData();
	help.FreeData();
	save.FreeData();
}