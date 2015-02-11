#include "header.h"
#include "drinkPowerup.h"


drinkPowerup::drinkPowerup(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	//load drink sprite
	this->drinksprite.LoadImage( "drink.png" );

	// Record the size as both height and width 
	m_iDrawWidth = 22;
	m_iDrawHeight = 33;

	//random position on screen
	m_iCurrentScreenX = rand()%650 + 50;
	m_iCurrentScreenY = rand()%450 + 50;

	//we don't want the powerup to start off visible
	this->SetVisible(false); 
}


drinkPowerup::~drinkPowerup(void)
{
}


void drinkPowerup::updateRandomPositionAndMakeVisible(void)
{
	//make invisible first
	this->SetVisible(false);

	//random position on screen
	m_iCurrentScreenX = rand()%650 + 50;
	m_iCurrentScreenY = rand()%450 + 50;

	//and set visible
	this->SetVisible(true);
}

void drinkPowerup::Draw(void)
{
	//don't draw if the powerup hasn't spawned or has been taken
	if ( ! this->IsVisible()) 
		return;
	this->drinksprite.RenderImageWithMask( GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight );
}
