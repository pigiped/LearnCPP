#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"

class BouncyBall : public GameObject
{
public:

	virtual ~BouncyBall() {}

	void setTexture(SDL_Texture* texture);
	virtual void draw(SDL_Renderer* renderer);
	virtual void update();

	void setElasticity(float e);

private:
	SDL_Texture* texture = nullptr;
	float dy = 0;
	float elasticity = 0.5;
	const float gravity = 0.02;
};

