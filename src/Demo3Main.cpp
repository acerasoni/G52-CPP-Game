#include "header.h"

#include "BaseEngine.h"

#include "Demo3Object.h"
#include "Demo3ObjectFinished.h"

#include "Demo3Main.h"

#include "JPGImage.h"

#include "TileManager.h"


Demo3Main::Demo3Main(void)
{
}

Demo3Main::~Demo3Main(void)
{
}

void Demo3Main::SetupBackgroundBuffer()
{
	FillBackground( 0 );

	const char* data[] = {
		"bbbbbbbbbbbbbbb",
		"baeaeadadaeaeab",
		"babcbcbcbcbibeb",
		"badadgdadhdadhb",
		"bgbcbcbcbibcbeb",
		"badadadadadadab",
		"bfbcbibcbcbcbeb",
		"bahadadhdadadab",
		"bfbcbcbibcbibeb",
		"badadadadadadab",
		"bbbbbbbbbbbbbbb" };

	// Specify how many tiles wide and high
	m_oTiles.SetSize( 15, 11 ); 
	// Set up the tiles
	for ( int x = 0 ; x < 15 ; x++ )
		for ( int y = 0 ; y < 11 ; y++ )
			m_oTiles.SetValue( x, y, data[y][x]-'a' );

		//	m_oTiles.SetValue( x, y, rand()%10 );

	for ( int y = 0 ; y < 11 ; y++ )
	{
		for ( int x = 0 ; x < 15 ; x++ )
			printf("%d ", m_oTiles.GetValue(x,y) );
		printf("\n" );
	}

	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen( 25, 40 );
//	m_oTiles.SetBaseTilesPositionOnScreen( 10, 10 );

	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	m_oTiles.DrawAllTiles( this, 
		this->GetBackground(), 
		0, 0, 14, 10 );
}

int Demo3Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Creates an array one element larger than the number of objects that you want.
	CreateObjectArray(5);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	StoreObjectInArray(0, new Demo3ObjectFinished(this, 1, 1));
	StoreObjectInArray(1, new Demo3Object(this, 9, 9));
	StoreObjectInArray(2, new Demo3Object(this, 13, 9));
	StoreObjectInArray(3, new Demo3Object(this, 9, 5));
	StoreObjectInArray(4, new Demo3Object(this, 13, 5));

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(5, NULL);

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;
}







/* Draw text labels */
void Demo3Main::DrawStringsUnderneath()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetWindowWidth(), 30/*Height*/ );
	DrawForegroundString( 150, 10, "Tile placement example", 0xffffff, NULL );
}


/* Overridden GameAction to ensure that objects use the modified time */
void Demo3Main::GameAction()
{
	// If too early to act then do nothing
	if ( !IsTimeToAct() ) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct( 1 );

	UpdateAllObjects( GetTime() );
}


// Override to add a node at specified point
void Demo3Main::MouseDown( int iButton, int iX, int iY )
{
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void Demo3Main::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}
