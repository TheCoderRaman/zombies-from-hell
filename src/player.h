#pragma once
#include "header.h"
#include "JPGImage.h"
#include "displayableobject.h"
class player :
	public DisplayableObject
{
public:
	player(BaseEngine* pEngine);
	~player(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	ImageData playersprite;
	int movementFactor;
};

