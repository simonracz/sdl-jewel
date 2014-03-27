//
//  AssetManager.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 25/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "AssetManager.h"
#include "SDL2_image/SDL_image.h"

namespace jewel {

const int AssetManager::TEXTURE_BG = 0;
const int AssetManager::TEXTURE_GEMS = 1;
	
AssetManager::AssetManager(SDL_Renderer* renderer) : renderer(renderer)
{
	//empty
}

AssetManager::~AssetManager()
{
	releaseAssets();
}

bool AssetManager::loadAssets()
{
	//the loading order and names are hardwired now
	SDL_Texture* texture = IMG_LoadTexture(renderer, "bg.png");
	if (!texture) {
		return false;
	}
	textures.push_back(texture);
	
	texture = IMG_LoadTexture(renderer, "gems.png");
	if (!texture) {
		SDL_DestroyTexture(textures[0]);
		textures.clear();
		return false;
	}
	textures.push_back(texture);
	
	assetsLoaded = true;
	return true;
}

void AssetManager::releaseAssets()
{
	if (assetsLoaded) {
		for (auto texture : textures) {
			SDL_DestroyTexture(texture);
		}
		textures.clear();
	}
}

SDL_Texture* AssetManager::getTexture(int id)
{
	return textures[id];
}

} //namespace