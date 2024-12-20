#pragma once

#include "SDL.h"
#include "SDL_image.h"

class BouncyBall
{
public:
	void setTexture(SDL_Texture* texture);
	void draw(SDL_Renderer* renderer);
	void update();

	void setPos(float x, float y);
	void setElasticity(float e);

private:
	SDL_Texture* texture = nullptr;
	float x = 0, y = 0;
	float dy = 0;
	float elasticity = 0.5;
	const float gravity = 0.02;
};

