#pragma once
#include "TileManager.h"
#include "JPGImage.h"
class PsyagceTileManager :
	public TileManager
{
public:
	PsyagceTileManager(void);
	~PsyagceTileManager(void);

	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
	 
	void SetID(int id);
	void FreeFrames();
private: 
	ImageData grass, dirt, pause, inventory, help, save;
	int id;
};

