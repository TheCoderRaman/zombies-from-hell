#include "zombie_type3.h"

// zombie type 3 is smart, but moves slowly (also uses different sprite)
// specifically, movementFactor = 1 and uses tracker AI (moves towards player's location)

zombie_type3::zombie_type3(BaseEngine* pEngine)
	: zombie(pEngine)
{
	this->trackerZombie = true; //this is a generic stupid zombie
	this->movementFactor = 1; //faster zombie
	this->zombiesprite.LoadImage( "zombie3.png" );
	// Record the size as both height and width 
	m_iDrawWidth = 53;
	m_iDrawHeight = 115;

	int randfactorforspawn = rand()%300;
	m_iCurrentScreenX = randfactorforspawn + m_iDrawWidth; //random spawn, but stay well within border
	m_iCurrentScreenY = randfactorforspawn + m_iDrawHeight; //random spawn, but stay well within border

	this->SetVisible(false); //starts off not visible - changed to visible when the zombie spawns in
}


zombie_type3::~zombie_type3(void)
{
}
