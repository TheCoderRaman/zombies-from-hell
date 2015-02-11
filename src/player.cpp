#include "header.h"
#include "player.h"
#include "zombie.h"
#include "templates.h"
#include "header.h"
#include <cmath>

int playersX, playersY; //variables will be accessed externally for zombie AI and collision checks


player::player(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	//load player sprite
	this->playersprite.LoadImage( "player.png" );

	// Record the size as both height and width 
	m_iDrawWidth = 36;
	m_iDrawHeight = 91;

	//set movement factor ( this determines how fast the player moves )
	this->movementFactor = 3;

	m_iCurrentScreenX = m_iPreviousScreenX = 400 - m_iDrawWidth; //spawn in centre of screen (x)
	m_iCurrentScreenY = m_iPreviousScreenY = 300 - m_iDrawHeight; //spawn in centre of screen (y)

	m_iStartDrawPosX = playersX = m_iCurrentScreenX;
	m_iStartDrawPosX = playersY = m_iCurrentScreenY;

	// And make it visible
	SetVisible(true); 
	printf("Player initialised. Avoid the zombies!\n");
}


player::~player(void)
{
}

void player::Draw(void)
{
	this->playersprite.RenderImageWithMask( GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight );
}



void player::DoUpdate(int iCurrentTime)
{
	// if arrow keys or WASD are pressed move the player in appropriate direction
	if	( GetEngine()->IsKeyPressed(SDLK_UP) || GetEngine()->IsKeyPressed(SDLK_w) )
		m_iCurrentScreenY -= this->movementFactor;

	if( GetEngine()->IsKeyPressed(SDLK_DOWN	) || GetEngine()->IsKeyPressed(SDLK_s) )
		m_iCurrentScreenY += this->movementFactor;

	if	( GetEngine()->IsKeyPressed(SDLK_LEFT) || GetEngine()->IsKeyPressed(SDLK_a) )
		m_iCurrentScreenX -= this->movementFactor;

	if	( GetEngine()->IsKeyPressed(SDLK_RIGHT) || GetEngine()->IsKeyPressed(SDLK_d) )
		m_iCurrentScreenX += this->movementFactor;
	

	//this code stops the player from going off the edge of the screen
	if	( m_iCurrentScreenX < 0 )
		m_iCurrentScreenX = 0;

	if	( m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth )
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;

	if	( m_iCurrentScreenY < 0 )
		m_iCurrentScreenY = 0;

	if	( m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight; 

	//update variables for zombie tracking
	playersX = m_iCurrentScreenX;
	playersY = m_iCurrentScreenY;

	// redrawing whole screen is handled here
	RedrawWholeScreen();
}