#include "header.h"
#include "Menu.h"
#include "BaseEngine.h"
#include "JPGImage.h"

void Menu::SetupBackgroundBuffer()
{
	ImageData bg;
	bg.LoadImage( "axk02u_cpp_menu.jpg" ); //load the custom menu image
	bg.RenderImageWithMask( this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight() );
}

void Menu::MouseDown( int iButton, int iX, int iY ) //user will press on the 'Play' text to continue to game
{
	//coordinates for play 'button' region: top left x 386 y 492, bottom right x 504 y 555

	//detecting if play button clicked
	if ( iX >= 386 && iX <= 504) { 
		if ( iY >= 492 && iY <= 555) {

			//exitcode 1 indicates to move to on to game stage
			SetExitWithCode( 1 ); 
		}
	}
}

void Menu::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
		// End program when escape is pressed 
		case SDLK_ESCAPE: 

			 //exitcode 0 indicates to exit the whole program
			SetExitWithCode( 0 );
			break;

		// Pressing return is an alternative way to start the game
		case SDLK_RETURN:
			SetExitWithCode( 1 );
			break;
	}
}

