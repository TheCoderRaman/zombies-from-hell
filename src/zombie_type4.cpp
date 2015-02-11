#include "zombie_type4.h"

// zombie type 4 is smart, and moves quickly 
// specifically, movementFactor = 2 and uses tracker AI (moves towards player's location)

zombie_type4::zombie_type4(BaseEngine* pEngine)
	: zombie(pEngine)
{
	this->trackerZombie = true; //this is a generic stupid zombie
	this->movementFactor = 2; //faster zombie
	this->zombiesprite.LoadImage( "zombie3.png" );
	// Record the size as both height and width 
	m_iDrawWidth = 53;
	m_iDrawHeight = 115;

	int randfactorforspawn = rand()%300;
	m_iCurrentScreenX = randfactorforspawn + m_iDrawWidth; //random spawn, but stay well within border
	m_iCurrentScreenY = randfactorforspawn + m_iDrawHeight; //random spawn, but stay well within border

	this->SetVisible(false); //starts off not visible - changed to visible when the zombie spawns in
}


zombie_type4::~zombie_type4(void)
{
}
