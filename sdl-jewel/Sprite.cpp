//
//  Sprite.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Sprite.h"

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

Sprite::Sprite(SDL_Texture* texture, SDL_Rect* texturePosition) : texture{texture}, texturePosition(*texturePosition), fullTexture{false}
{
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

Sprite::~Sprite()
{
	
}

void Sprite::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
	fullTexture = true;
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

void Sprite::setTexture(SDL_Texture* texture, SDL_Rect* texturePosition)
{
	this->texture = texture;
	this->texturePosition = *texturePosition;
	fullTexture = false;
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't get texture width and height");
	}
}

bool Sprite::setBlendMode(SDL_BlendMode blendMode)
{
	int ret = SDL_SetTextureBlendMode(texture, blendMode);
	return (ret==0);
}
	
void Sprite::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}
	
void Sprite::draw(int x, int y)
{
	SDL_Rect dRect;
	dRect.x = x;
	dRect.y = y;
	dRect.w = width;
	dRect.h = height;
	
	draw(&dRect);
}

void Sprite::draw(SDL_Rect* destination)
{
	SDL_assert(Sprite::renderer != nullptr);

	if (fullTexture) {
		SDL_RenderCopy(renderer, texture, NULL, destination);
	} else {
		SDL_RenderCopy(renderer, texture, &texturePosition, destination);
	}
}
	
bool Sprite::runAction(Action* action)
{
	return true;
}

void Sprite::removeActions()
{
	
}

} //namespace