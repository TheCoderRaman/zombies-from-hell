//#include "header.h"
#include "zombie.h"
//#include "JPGImage.h"
#include <cmath>


extern int playersX, playersY; //keep track of players position for use in AI



zombie::zombie(BaseEngine* pEngine)
	: DisplayableObject(pEngine)	
{

	this->trackerZombie = true; // true = clever AI chasing player, false = dumb AI bouncing around screen

	zombiesprite.LoadImage( "zombie2.png" );
	movementFactor = 1; // 1 - slow, 2 - medium, 3 - fast; higher than that = crazy fast (player movementFactor = 3)

	// Record the size as both height and width 
	m_iDrawWidth = 53;
	m_iDrawHeight = 115;

	int randfactorforspawn = rand()%300;
	m_iCurrentScreenX = randfactorforspawn + m_iDrawWidth; //random spawn, but stay well within border
	m_iCurrentScreenY = randfactorforspawn + m_iDrawHeight; //random spawn, but stay well within border

	this->SetVisible(false); //starts off not visible - changed to visible when the zombie spawns in
}




zombie::~zombie(void)
{
}



void zombie::Draw()
{
	if ( ! this->IsVisible()) //don't draw if the zombie isn't meant to have spawned yet
		return;
	zombiesprite.RenderImageWithMask( GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight );
}




void zombie::DoUpdate(int iCurrentTime)
{
	if ( this->IsVisible() ) { //only if the zombie has spawned

		//make sure the zombie isn't moving off screen for any reason
		if ( m_iCurrentScreenX < 0 )
			m_iCurrentScreenX = 0;

		else if ( m_iCurrentScreenX > 800 )
			m_iCurrentScreenX = 800;


		if ( m_iCurrentScreenY < 0 )
			m_iCurrentScreenY = 0;

		else if ( m_iCurrentScreenY > 600 )
			m_iCurrentScreenY = 600;

		//CALL zombieAI() to work out where to move
		zombieAI(); 

		//and then move in the set direction
		m_iCurrentScreenX += this->AImoveX;
		m_iCurrentScreenY += this->AImoveY;
	}
}





void zombie::zombieAI() //handle the zombie AI
{
	/* 'CLEVER' ZOMBIE AI
	(type 3 and 4): can always sense the player and decides which direction to move in order to follow player */

	if ( this->trackerZombie == true ) {
		int randomFactor = rand()%50; //element of randomness used to slightly reduce predictability of zombie movements

		//AI tracking on x axis
		if ( (m_iCurrentScreenX < 0 ) || 
			( m_iCurrentScreenX < playersX &&
			(playersX - m_iCurrentScreenX) > randomFactor ) ) { 
				//first check finds out relative player position, second introduces some randomness
			
				this->AImoveX = this->movementFactor; //move positive on x axis
		}

		else if (m_iCurrentScreenX > playersX && 
			(m_iCurrentScreenX - playersX) > randomFactor) 
			{ //first check finds out relative player position, second introduces some randomness
			
				this->AImoveX = - this->movementFactor; //move negative on x axis
		}

		//AI tracking on y axis
		if ( ( m_iCurrentScreenY < 0 ) || 
			( m_iCurrentScreenY < playersY &&
			(playersY - m_iCurrentScreenY) > randomFactor ) )
			{ //first check finds out relative player position, second introduces some randomness
			
				this->AImoveY = this->movementFactor; //move positive on y axis
		}

		else if (m_iCurrentScreenY > playersY &&
			(m_iCurrentScreenY - playersY) > randomFactor) 
			{ //first check finds out relative player position, second introduces some randomness
			
				this->AImoveY = - this->movementFactor; //move negative on y axis
		}
	}



	/* 'STUPID' ZOMBIE AI (AI for types 1 and 2 zombies)
	moves within region of screen without much intelligence 
	(although can sense a close player and give chase temporarily until the player gets far away) */

	else {  

		//basic 'bounce' movement defined here (if reach end of screen, bounce back)
		if ( m_iCurrentScreenX < 1 )
			this->AImoveX = movementFactor;

		else if ( m_iCurrentScreenX > 750 )
			this->AImoveX = - movementFactor;


		if ( m_iCurrentScreenY < 1 )
			this->AImoveY = movementFactor; 

		else if ( m_iCurrentScreenY > 500 )
			this->AImoveY = - movementFactor;


		//but, the zombie senses the player if they get too close! 
		//'Stupid' type 1 and 2 zombies have worse senses than types 3 and 4, but are still a threat!

		int differenceonx = m_iCurrentScreenX - playersX ;

		if ( differenceonx > - 150 && differenceonx < 150 ) 
			{//user is close on the x axis! Check y axis as well now...

			int differenceony = m_iCurrentScreenY - playersY;

			if ( differenceony > - 150  && differenceony < 150 ) 
				{ //user is close on the y axis as well!
				
				//player got noticed, the zombie will try and catch them!
				if (differenceonx < 0)
					this->AImoveX = this->movementFactor; //appropriate direction to chase player
				else 
					this->AImoveX = - this->movementFactor; //appropriate direction to chase player

				if (differenceony < 0)
					this->AImoveY = this->movementFactor; //appropriate direction to chase player
				else
					this->AImoveY = - this->movementFactor; //appropriate direction to chase player

			}
		}
	}
	
}