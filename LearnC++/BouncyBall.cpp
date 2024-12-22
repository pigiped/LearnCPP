#include "BouncyBall.h"

void BouncyBall::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
void BouncyBall::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { (int)x,(int)y,32,32 };
	SDL_RenderCopy(renderer, this->texture, nullptr, &rect);
}
void BouncyBall::update()
{
	if (y+32 < 480)
	{
		y += dy;
		dy += gravity;
	}
	else
	{
		dy *= -elasticity;
		y += dy * 2;
		if (fabsf(dy) < 0.1)
		{
			//dy = 0;
		}
	}
}

void BouncyBall::setElasticity(float e)
{
	elasticity = e;
}
