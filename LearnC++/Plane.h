#pragma once

#include "GameObject.h"

class Plane : public GameObject
{
public:
	virtual ~Plane() {}
	void setTexture(SDL_Texture* texture);

	virtual void draw(SDL_Renderer* renderer);
	virtual void update();

private:
	SDL_Texture* texture = nullptr;
};