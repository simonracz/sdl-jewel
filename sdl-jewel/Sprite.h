//
//  Sprite.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Sprite__
#define __sdl_jewel__Sprite__

#include "SDL2/SDL.h"

namespace jewel {

class Action;

/**
 * A general Sprite class
 */
class Sprite {
public:
	Sprite();
	Sprite(SDL_Texture* texture);
	Sprite(SDL_Texture* texture, SDL_Rect* texturePosition);
	
	~Sprite();
	
	static void setRenderer(SDL_Renderer* renderer);
	
	void setTexture(SDL_Texture* texture);
	void setTexture(SDL_Texture* texture, SDL_Rect* texturePosition);
	
	/**
	 * It can run only one Action at a time.
	 * The Sprite object does NOT own the Action object.
	 */
	bool runAction(Action* action);
	void removeActions();
	
	bool setBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
	void setAlpha(Uint8 alpha = 255);
	
	void draw(int x, int y);
	void draw(SDL_Rect* destination);
	
	int getWidth() {return width;}
	int getHeight() {return height;}
private:
	static SDL_Renderer* renderer;
	
	SDL_Texture* texture{nullptr};
	SDL_Rect texturePosition{};
	int width{0};
	int height{0};
	bool fullTexture{true};
	Action* action{nullptr};
};
	
} //namespace

#endif /* defined(__sdl_jewel__Sprite__) */
