//
//  Sprite.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Sprite.h"
#include "Action.h"

namespace jewel {

SDL_Renderer* Sprite::renderer = nullptr;
	
void Sprite::setRenderer(SDL_Renderer* renderer)
{
	Sprite::renderer = renderer;
}
	
Sprite::Sprite()
{
	//empty
}

Sprite::Sprite(SDL_Texture* texture) : texture{texture}
{
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

Sprite::Sprite(SDL_Texture* texture, const SDL_Rect& texturePosition) : texture{texture}, texturePosition(texturePosition), fullTexture{false}
{
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

Sprite::~Sprite()
{
	removeAndDeleteAction();
}
	
SDL_Texture* Sprite::getTexture()
{
	return texture;
}

void Sprite::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
	fullTexture = true;
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

void Sprite::setTexture(SDL_Texture* texture, const SDL_Rect& texturePosition)
{
	this->texture = texture;
	this->texturePosition = texturePosition;
	fullTexture = false;
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

Uint8 Sprite::getAlpha()
{
	return alpha;
}
	
void Sprite::setAlpha(Uint8 alpha)
{
	this->alpha = alpha;
}
	
void Sprite::setPosition(int x, int y)
{
	spritePosition.x = x;
	spritePosition.y = y;
}
	
void Sprite::setPosition(SDL_Point* point)
{
	spritePosition = *point;
}

void Sprite::translate(int x, int y)
{
	spritePosition.x+=x;
	spritePosition.y+=y;
}
	
SDL_Point Sprite::getPosition()
{
	return spritePosition;
}
	
int Sprite::getPosX()
{
	return spritePosition.x;
}
	
int Sprite::getPosY()
{
	return spritePosition.y;
}

void Sprite::draw()
{
	SDL_Rect dRect;
	dRect.x = spritePosition.x;
	dRect.y = spritePosition.y;
	dRect.w = width;
	dRect.h = height;
	
	draw(dRect);
}
	
void Sprite::draw(int x, int y)
{
	SDL_Rect dRect;
	dRect.x = x;
	dRect.y = y;
	dRect.w = width;
	dRect.h = height;
	
	draw(dRect);
}

void Sprite::draw(const SDL_Rect& destination)
{
	SDL_assert(Sprite::renderer != nullptr);

	if (fullTexture) {
		SDL_RenderCopy(renderer, texture, NULL, &destination);
	} else {
		SDL_RenderCopy(renderer, texture, &texturePosition, &destination);
	}
}
	
void Sprite::runAction(Action* action)
{
	this->action = action;
	action->setSprite(this);
	action->startAction();
}

Action* Sprite::removeAction()
{
	Action* temp = action;
	if (action) {
		action->setSprite(nullptr);
		action = nullptr;
	}
	return temp;
}
	
void Sprite::removeAndDeleteAction()
{
	if (action) {
		action->setSprite(nullptr);
		delete action;
		action = nullptr;
	}
}

} //namespace