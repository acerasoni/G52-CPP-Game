#include "header.h"

#include <ctime>

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "BouncingBallMain.h"
#include "SimpleDemo.h"
#include "Demo1Main.h"
#include "Demo2Main.h"
#include "Demo3Main.h"
#include "Demo4Main.h"
#include "PsyagceEngine.h"


const int BaseScreenWidth = 1120;
const int BaseScreenHeight = 580;


int main(int argc, char *argv[])
{
	int iResult;

	// Send random number generator with current time
	::srand(time(0));

	// Needs just one of the two following lines:
	//SimpleDemo oMain;
	//Demo1Main oMain;
	//Demo2Main oMain;
	//Demo3Main oMain;
	//Demo4Main oMain;
   // BouncingBallMain oMain;
    PsyagceEngine oMain;


	char buf[1024];
	sprintf( buf, "Wolf Assault");
	iResult = oMain.Initialise( buf, BaseScreenWidth, BaseScreenHeight, "Quicksand-Regular.ttf", 28 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();


	return iResult;
}
