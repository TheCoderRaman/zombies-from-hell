#pragma once
#include "header.h"
#include "JPGImage.h"
#include "displayableobject.h"

class drinkPowerup :
	public DisplayableObject
{
public:
	drinkPowerup(BaseEngine *pEngine);
	~drinkPowerup(void);

	void Draw(void);
	void updateRandomPositionAndMakeVisible(void);

	ImageData drinksprite;
};

