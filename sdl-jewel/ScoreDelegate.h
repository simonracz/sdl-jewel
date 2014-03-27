//
//  ScoreDelegate.h
//  sdl-jewel
//
//  Created by Simon Racz on 27/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__TextDelegate__
#define __sdl_jewel__TextDelegate__

namespace jewel {

class ScoreDelegate {
public:
	virtual void addScore(int score) = 0;
};

} //namespace

#endif /* defined(__sdl_jewel__TextDelegate__) */
