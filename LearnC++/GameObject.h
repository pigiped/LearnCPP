#pragma once

#include "SDL.h"
#include "SDL_Image.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

	//questi metodi dovranno essere overridati dai figli
	virtual void draw(SDL_Renderer* rend)=0;	//con =0 si dice che i metodi in GameObject 
	virtual void update()=0;					//non hanno implementazione
												// il che rende GameObject una classe  puramente
	void setPos(float x, float y);				//virtuale/astratta
	float getX();
	float getY();

protected:
	float x = 0, y = 0;

};

