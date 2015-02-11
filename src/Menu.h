#ifndef MENU_H
#define MENU_H

#include "BaseEngine.h"

//#pragma once

class Menu : public BaseEngine
{
public:
	Menu()
	: BaseEngine( 6 )
	{}

	virtual void SetupBackgroundBuffer();

	void MouseDown( int iButton, int iX, int iY );
	void KeyDown(int iKeyCode);
};
#endif
