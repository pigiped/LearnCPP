#include "Plane.h"
#include "GameObject.h"

void Plane::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
void Plane::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { (int)x,(int)y,32,21 };
	SDL_RenderCopy(renderer, this->texture, nullptr, &rect);
}
void Plane::update()
{
	x -= 2;
}
