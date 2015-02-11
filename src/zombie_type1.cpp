#include "header.h"
//#include "zombie.h"
#include "zombie_type1.h"
//#include "displayableobject.h"

// zombie type 1 is the generic zombie type: slow and stupid 
// specifically, movementFactor = 1 and uses basic AI (bouncing around screen). Can sense the player if they come too close!

zombie_type1::zombie_type1(BaseEngine* pEngine)
	: zombie(pEngine)
{
	this->trackerZombie = false; //this is a generic stupid zombie
	this->movementFactor = 1; //slow zombie
	this->zombiesprite.LoadImage( "zombie1.png" );
	// Record the size as both height and width 
	m_iDrawWidth = 53;
	m_iDrawHeight = 115;

	int randfactorforspawn = rand()%300;
	m_iCurrentScreenX = randfactorforspawn + m_iDrawWidth; //random spawn, but stay well within border
	m_iCurrentScreenY = randfactorforspawn + m_iDrawHeight; //random spawn, but stay well within border

	this->SetVisible(false); //starts off not visible - changed to visible when the zombie spawns in

}


zombie_type1::~zombie_type1(void)
{
}
