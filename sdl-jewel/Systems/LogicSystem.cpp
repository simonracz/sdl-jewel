//
//  LogicSystem.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "LogicSystem.h"

namespace jewel {
	

LogicSystem::LogicSystem()
{

}
LogicSystem::~LogicSystem()
{

}

void LogicSystem::setProcessing(bool process)
{
	processing = process;
}

bool LogicSystem::checkProcessing()
{
	return processing;
}

void LogicSystem::begin()
{

}
void LogicSystem::processEntities(artemis::ImmutableBag<artemis::Entity*> & bag)
{

}
void LogicSystem::end()
{
	processing = false;
}

	
} //namespace
