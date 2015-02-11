#pragma once
#include "header.h"

// This is a basic implementation, without fancy stuff

#include "BaseEngine.h"
#include "MyProjectMain.h"

#include "JPGImage.h"
#include "TileManager.h"
#include "DisplayableObject.h"

#include "player.h"

//#include "zombie.h" //zombie.h is included in subclasses below. Need #pragma once in these header files or code will break
#include "zombie_type1.h"
#include "zombie_type2.h"
#include "zombie_type3.h"
#include "zombie_type4.h"

#include "drinkPowerup.h"

//#include <stdlib.h>
#include <iostream>
#include <fstream> //for files
#include <string>
using namespace std;


enum messagestate //used to determine what (if any) message should be displayed onscreen
{
	s_intro,
	s_nomessage,
	s_warning,
	s_gameover
};

enum zombiestate //used for zombie spawns
{
	zs_spawning,
	zs_clear
};

enum gamestate //used for game state - e.g. gameover or not 
{
	g_intro,
	g_inplay,
	g_highscores,
	g_gameover
};


messagestate mesg_STATE = s_intro; 
zombiestate zomb_STATE = zs_clear;
gamestate game_STATE = g_intro;



void MyProjectMain::handleHighscores() 
{
	//opening highscores file for output
	ofstream file("highscores.txt", ios::beg); 

	//if the user's score beat the previous high score
	if ( finalscore > previoushighscore ) { 

		//update highscore
		file << finalscore << endl; 
		printf("%d highscore\n", finalscore);
	}

	else { 
		//rewrite old highscore
		file << previoushighscore << endl;
	}

	//we are finished with the highscores file so close it
	file.close();
}




// COLLISION DETECTION. 
// The idea is that a collision only counts if the zombie is close enough to bite
// therefore, a player can freely move past a zombie's lower half, but if they get close to the arms/head then they get bitten

void MyProjectMain::checkCollision() { 

	//find out player's current coordinates for comparison to the zombies' coordinates

	//players centre x coord
	int pCentreX = this->m_ppDisplayableObjects[0]->GetXCentre() - 200; 
	//players centre y coord
	int	pCentreY = this->m_ppDisplayableObjects[0]->GetYCentre(); 

	//temp storage of zombie coordinates
	int zombieX, zombieY; 


	//iterate through zombie objects
	for ( int i = 1; i <= this->numObjects - 1; i++ ) { 

		//only do collision detection if the zombie has spawned (been set to visible)
		if ( this->m_ppDisplayableObjects[i]->IsVisible() == true ) { 

			zombieX = this->m_ppDisplayableObjects[i]->GetXCentre();

			//if the zombie is really close on the x axis
			if ( zombieX > pCentreX - 20 && zombieX < pCentreX + 20  ) { 

				zombieY = this->m_ppDisplayableObjects[i]->GetYCentre();

				//if the zombie is also close on the y axis then this counts as a bite - game over
				if ( zombieY > pCentreY - 20 && zombieY < pCentreY + 70 ) { 

					//GAME OVER
					this->bitten = true; //if bitten, the player has lost

					printf("Collision detected! Player x %d y %d, zombie %d x %d y %d.\n", 
						pCentreX, pCentreY, i, zombieX, zombieY);

					return; 
				}
			}
		}
	}



	// check collisions of any powerup that has spawned
	if ( this->m_ppDisplayableObjects[12]->IsVisible() == true ) {

		//record current x position of drink powerup
		int drinksX = this->m_ppDisplayableObjects[12]->GetXCentre();

		// check X axis collision
		if ( drinksX > pCentreX - 20  &&  drinksX < pCentreX + 20 ) {

			//record current y position of drink powerup
			int drinksY = this->m_ppDisplayableObjects[12]->GetYCentre();

			// check y axis collision
			if ( drinksY > pCentreY - 30  &&  drinksY < pCentreY + 30 ) {

				// the player will 'pick up' the powerup and gain increased speed

				//make the powerup invisible
				this->m_ppDisplayableObjects[12]->SetVisible(false);

				//temporarily increase player movement speed
				dynamic_cast<player*>(m_ppDisplayableObjects[0])->movementFactor = 4;
				
				printf("That drink rehydrated you! +1 movement speed boost\n");
			}
		}
	}

}




/*
Do any setup of back buffer prior to locking the screen buffer
Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
*/
void MyProjectMain::SetupBackgroundBuffer()
{
	ImageData bg;
	bg.LoadImage( "background_apoc.jpg" ); //apocalyptic road background
	bg.RenderImageWithMask( this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight() );

}




/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int MyProjectMain::InitialiseObjects()
{

	//record start point of this stage in ticks
	initialTime = SDL_GetTicks(); 

	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();
	
	// Create an array one element larger than the number of objects that you want.
	this->m_ppDisplayableObjects = new DisplayableObject*[14]; 
	
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.


	//the entries have been manually set in a way to create variety and challenge - i.e. different zombie types 
	//initially my game implemented random zombies but this was unreliable and meant the game could randomly be incredibly easy or hard
	//this implementation ensures a balanced game each time

	this->m_ppDisplayableObjects[0] = new player(this); //player object

	//start off with zombie type 1 (slow and stupid)
	this->m_ppDisplayableObjects[1] = new zombie_type1(this);  

	//later, spawn a type 2 - stupid but faster
	this->m_ppDisplayableObjects[2] = new zombie_type2(this); 

	//then, spawn a type 3 - slow but smart
	this->m_ppDisplayableObjects[3] = new zombie_type3(this); 

	//spawning various type 1 and 2 zombies 
	this->m_ppDisplayableObjects[4] = new zombie_type1(this); 
	this->m_ppDisplayableObjects[5] = new zombie_type1(this); 
	this->m_ppDisplayableObjects[6] = new zombie_type2(this); 
	this->m_ppDisplayableObjects[7] = new zombie_type1(this); 
	this->m_ppDisplayableObjects[8] = new zombie_type1(this); 

	//type 4 - fast and smart - this is where it gets really hard!
	this->m_ppDisplayableObjects[9] = new zombie_type4(this); 

	// add another slower tracking zombie 
	this->m_ppDisplayableObjects[10] = new zombie_type3(this); 

	//type 4 again, if the player is somehow still alive, this should finish them off... muahahaha 
	this->m_ppDisplayableObjects[11] = new zombie_type4(this);
	

	//entry for the powerup as this is also a displayable object
	this->m_ppDisplayableObjects[12] = new drinkPowerup(this);

	this->m_ppDisplayableObjects[13] = NULL;

	//start off with 1 enemy - more are spawned as time goes on
	this->currentZombies = 1; 

	//spawnLock is set to true when a zombie is spawning in order to avoid multiple spawns - we want this to be false for now
	this->spawnLock = false; 

	//record number of objects
	this->numObjects = 12;
	printf("Number of objects %d \n", this->numObjects);

	return this->numObjects; 
}




/* Draw text labels */
void MyProjectMain::DrawStrings()
{
	// Build the string to print
	char scoredisplay[128], message[128], midscreen[128];

	//displaying seconds survived 
	if (mesg_STATE != s_gameover) 
	{
		//display score in seconds (how much time has passed since game state began)
		sprintf( scoredisplay, "You've survived for %d seconds!", ((GetTime()/1000) - (initialTime/1000)) ); 

		// Then draw to top of screen
		DrawScreenString( 170, 10, scoredisplay, 0xFFFFFF, NULL );
	}


	//handling which message (if any) to display based on message state
	if (mesg_STATE == s_intro) 
	{
		//display intro message
		sprintf(message, "Zombies are coming! Run!");
		DrawScreenString(230, 55, message, 0xFFFFFF, NULL );
	}

	//display message alerting player to new zombie spawn
	if ( mesg_STATE == s_warning ) { 

		sprintf(midscreen, "A new zombie has spawned!");
		DrawScreenString(200, 285, midscreen, 0xFFFFFF, NULL );
	}

	//display gameover messages and display final score
	else if (mesg_STATE == s_gameover) 
	{
		sprintf(scoredisplay, "Game over! You survived %d seconds", this->finalscore);
		sprintf(message, "You got bitten! Bad luck!");

		//if it's a new highscore  print out a congratulatory message :)
		if ( this->finalscore > this->previoushighscore ) { 
			sprintf(midscreen, "Wow! You just beat your highscore of %d seconds!", this->previoushighscore);

		//if the old highscore is better, print out a message saying so
		} else {
			sprintf(midscreen, "You failed to beat your highscore of %d seconds.", this->previoushighscore);
		}

		// Draw gameover strings to screen
		DrawScreenString( 170, 10, scoredisplay, 0xFFFFFF, NULL );
		DrawScreenString(230, 55, message, 0xFFFFFF, NULL );
		DrawScreenString(40, 285, midscreen, 0xFFFFFF, NULL );
	}

	//note: if mesg_STATE == s_nomessage, then no string is built for 'message' (other text will still display)
}






/* Overridden GameAction to control various elements of the program


Handles states and general running of the game 
e.g. intro stage to set up game elements such as first zombie
	 functional elements of highscores are dealt with here
	 changing states as appropriate and ensuring the correct method calls are made
	 zombie spawns are handled here
	 gameover is also handled here (although messages on screen are handled in DrawStrings separately using states set here)

*/

void MyProjectMain::GameAction()
{

	// if the game is over, don't do anything
	if ( game_STATE == g_gameover )
		return; 


	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;


	// set the amount of ticks that need to pass before it's time to act
	// the higher the number the slower the pace of the game 
	// 10 ticks is very very quick in my experience, 100 is a good balance
	// note: the number of ticks is the number below * 10

	// Don't act for another 100 ticks
	SetTimeToAct( 10 ); 



	if ( game_STATE == g_intro ) { //initialise state for game - spawn first enemy

		//read previous highscore
		ifstream highscorefile("highscores.txt");

		//read in line as a string
		string score;
		getline(highscorefile, score, '\n');

		//convert string to int and store in previoushighscore
		this->previoushighscore = atoi(score.c_str()); 

		printf("Previous high score %d \n", this->previoushighscore);

		//1st zombie begins spawned
		this->m_ppDisplayableObjects[1]->SetVisible(true); 

		//change state to indicate game is now in the main running stage
		game_STATE = g_inplay;

		printf("Zombie 1 set visible\n\n");

		//increment the counter for zombies so that the correct array entries are referenced later
		currentZombies++; 
	}



	//if 3 seconds have passed since game starts remove intro message
	if ( mesg_STATE == s_intro && SDL_GetTicks() > (initialTime + 3000) ) { 

		//changing state stops the message displaying
		mesg_STATE = s_nomessage; 
	} 


	//if not currently in spawning state do further checks to see if we need to spawn a zombie
	if ( this->spawnLock == false && (zomb_STATE != zs_spawning ) ) { 
		
		//record game time thus far
		int time = SDL_GetTicks()/1000 - initialTime/1000;

		//use mod 10 to see if this is a multiple of 10 seconds (as this is when we want to spawn new zombies)
		if ( time != 0 && time % 10 == 0 ) { 

			//if the max number of enemies hasnt been reached, spawn one
			if ( this->currentZombies <= this->numObjects - 1 ) { 
			
				printf("Zombie Spawned! Time %d seconds, zombie number %d \n", (SDL_GetTicks()/1000 - this->initialTime/1000), currentZombies);
				
				//change state to indicate a spawn is happening
				zomb_STATE = zs_spawning; 

				//display warning to user that a new zombie has spawned
				mesg_STATE = s_warning;

				//engage lock so multiple spawns don't happen for this time period
				this->spawnLock = true;

				//spawn zombie
				this->m_ppDisplayableObjects[currentZombies]->SetVisible(true); 

				//and increment counter
				this->currentZombies++; 
			} 
		}


		// POWERUP SPAWN HANDLING 

		//piggyback this method to handle powerup spawning (avoid needing an extra state)
		//spawn a drink powerup every 30 seconds (which increases player speed temporarily)
		if ( time != 0  &&  time % 30 == 0 ) {

			//spawn powerup in a random place
			dynamic_cast<drinkPowerup*>(m_ppDisplayableObjects[12])->updateRandomPositionAndMakeVisible();

			printf("A drink powerup just spawned! Taking it will increase movement speed temporarily\n");
		}
	}


	// if the player has a powerup activated eventually we will want to reset their speed
	// determine if they have a powerup because their speed will = 4
	if ( dynamic_cast<player*>(m_ppDisplayableObjects[0])->movementFactor == 4 ) {

		// powerup's benefits end at every 15 second slot
		if ( (SDL_GetTicks()/1000 - initialTime/1000) % 15 == 0 ) {

			//set player speed back to 3
			dynamic_cast<player*>(m_ppDisplayableObjects[0])->movementFactor = 3;

			printf("\nYour speed boost from the drink has ended \n");
		}
	}


	//check whether it is safe to unlock the spawn code and change state
	if ( this->spawnLock == true  &&  zomb_STATE == zs_spawning  ) { 

		//record game time
		int time = SDL_GetTicks()/1000 - this->initialTime/1000;

		//if time mod 10 is not 0 then it is safe to unlock/change states
		if ( time % 10 != 0 ) { 

			printf("Spawn state reset at %d seconds with %d zombies onscreen so far\n\n", time, this->currentZombies - 1);
			this->spawnLock = false;

			//take warning message off screen
			mesg_STATE = s_nomessage; 

			//change state so that a zombie can spawn when next 10 second point is reached
			zomb_STATE = zs_clear; 
		}
	}


	//if game is over handle highscores 
	if ( game_STATE == g_highscores ) {

		//call the highscores method
		handleHighscores();

		//change state -  GAME OVER!
		game_STATE = g_gameover;

		printf("\nGAME OVER!!!! Previous highscore: %d. Score this session: %d.\n", this->previoushighscore, this->finalscore);
	}



	// THE FOLLOWING code will be executed repeatedly as the game runs
	// while game is running, update objects and check collisions
	// Tell all objects to update themselves

	if ( game_STATE != g_gameover ) {

		UpdateAllObjects( GetTime() );

		//check if player has collided with a zombie's upper body
		checkCollision();
		
		//bitten = false if no collisions and game continues, otherwise...
		if ( this->bitten == true) { 

			//change states to indicate game over

			//this state will ensure correct gameover messages are displayed
			mesg_STATE = s_gameover; 

			//change game state to handle high scores
			game_STATE = g_highscores; 

			//record how many seconds the user survived for highscore purposes
			this->finalscore = GetTime()/1000 - initialTime/1000; 
		}
	}
}






//Handle key presses here.

// all we need to check is if the player wants to pre-emptively exit the game by pressing Escape
// (player interaction is handled in player.cpp)

void MyProjectMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
		// End program when escape is pressed 
		case SDLK_ESCAPE: 
			SetExitWithCode( 0 );
			break;
	}
}
