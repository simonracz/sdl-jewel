//
//  AssetManager.h
//  sdl-jewel
//
//  Created by Simon Racz on 25/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__AssetManager__
#define __sdl_jewel__AssetManager__

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <vector>

namespace jewel {

class AssetManager {
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> textures;
	TTF_Font* font;
	bool assetsLoaded{false};
public:
	AssetManager(SDL_Renderer* renderer);
	~AssetManager();
	
	static const int TEXTURE_BG;
	static const int TEXTURE_GEMS;
		
	bool loadAssets();
	void releaseAssets();
	TTF_Font* getFont();
	bool isAssetsLoaded() {return assetsLoaded;}
	
	//or with a data driven approach
	//bool loadAssets(std::string assetDescriptor);
	
	SDL_Texture* getTexture(int id);
};
	
} //namespace

#endif /* defined(__sdl_jewel__AssetManager__) */
