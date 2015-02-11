#pragma once
#include "header.h"
#include "JPGImage.h"
#include "displayableobject.h"
#include "player.h"
#include "templates.h"

class zombie :
	public DisplayableObject
{
public:
	//zombie(BaseEngine* pEngine, int intZombieType, char zombieFile[12]);
	zombie(BaseEngine* pEngine);
	~zombie(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
	void zombieAI();
	int AImoveX, AImoveY, movementFactor;
	char cZombieType;
	char filename[12];
	bool trackerZombie;
	ImageData zombiesprite; 
};

