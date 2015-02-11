#include "header.h"

#include "templates.h"

// Needs one of the following #includes, to include the class definition
//#include "BouncingBallMain.h"
#include "Menu.h"
#include "MyProjectMain.h"
//#include "Demo2Main.h"
//#include "Demo2aMain.h"
//#include "Demo3Main.h"
#include "time.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600



int main(int argc, char *argv[])
{
	int iResult;
	srand(time(NULL)); //need this line otherwise rand will always return same numbers!

	// Needs just one of the two following lines:
	//BouncingBallMain oMain;
	Menu menu;
	MyProjectMain oMain;
	//Demo2Main oMain;
	//Demo2aMain oMain;
	//Demo3Main oMain;


	char buf[1024];
	sprintf( buf, "Alastair Kerr G52CPP : Size %d x %d", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT );


	// MENU STATE
	iResult = menu.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24);
	iResult = menu.MainLoop();
	menu.Deinitialise();

	// GAME STATE
	if ( iResult == 1 ) //if player pressed play start the game
	{
		iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24);
		iResult = oMain.MainLoop();
		oMain.Deinitialise();
	}


	return iResult;
}
