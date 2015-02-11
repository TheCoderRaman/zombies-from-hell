//#include "header.h"
#include "zombie_type2.h"

// zombie type 2 is stupid, but moves faster than type 1 (also uses different sprite)
// specifically, movementFactor = 2 and uses basic AI (bouncing around screen).  Can sense the player if they come too close!

zombie_type2::zombie_type2(BaseEngine* pEngine)
	: zombie(pEngine)
{
	this->trackerZombie = false; //this is a generic stupid zombie
	this->movementFactor = 2; //faster zombie
	this->zombiesprite.LoadImage( "zombie2.png" );
	// Record the size as both height and width 
	m_iDrawWidth = 53;
	m_iDrawHeight = 115;

	int randfactorforspawn = rand()%300;
	m_iCurrentScreenX = randfactorforspawn + m_iDrawWidth; //random spawn, but stay well within border
	m_iCurrentScreenY = randfactorforspawn + m_iDrawHeight; //random spawn, but stay well within border

	this->SetVisible(false); //starts off not visible - changed to visible when the zombie spawns in
}


zombie_type2::~zombie_type2(void)
{
}
