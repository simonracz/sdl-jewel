//
//  LogicSystem.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "LogicSystem.h"
#include "Table.h"
#include "RenderingComponent.h"
#include "Entity.h"
#include <cmath>
#include "Action.h"

namespace jewel {

LogicSystem::LogicSystem(Table* table, Sprite* aLongLivedSprite) : table(table), lSprite(aLongLivedSprite)
{

}

void LogicSystem::setInputHandler(InputHandler* inputHandler)
{
	this->inputHandler = inputHandler;
}
	
LogicSystem::~LogicSystem()
{

}

void LogicSystem::nodeTouchedAt(int index)
{
	std::cout << "node touched at " << index << "\n";
	
	if (hasSelection) {
		if ((std::abs(selectedIndex - index) == 1) || (std::abs(selectedIndex - index) == 8)) {
			inputHandler->setProcessing(false);
			entities[selectedIndex]->getComponent<RenderingComponent>()->selected = false;
			hasSelection = false;
			startSwapping(selectedIndex, index);
		} else {
			entities[selectedIndex]->getComponent<RenderingComponent>()->selected = false;
			entities[index]->getComponent<RenderingComponent>()->selected = true;
			selectedIndex = index;
		}
	} else {
		entities[index]->getComponent<RenderingComponent>()->selected = true;
		selectedIndex = index;
		hasSelection = true;
	}
}

void LogicSystem::nodeSlidTo(int index, Direction direction)
{
	switch (direction) {
		case Direction::Left:
			std::cout << "node at index " << index << " slid to left\n";
			break;
		case Direction::Right:
			std::cout << "node at index " << index << " slid to right\n";
			break;
		case Direction::Up:
			std::cout << "node at index " << index << " slid to up\n";
			break;
		case Direction::Down:
			std::cout << "node at index " << index << " slid to down\n";
			break;
	}
	
}
	
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}
	
void LogicSystem::startSwapping(int index1, int index2)
{
	std::cout << "start swapping\n";
	Sprite* sprite1 = entities[index1]->getComponent<RenderingComponent>()->sprite;
	Sprite* sprite2 = entities[index2]->getComponent<RenderingComponent>()->sprite;
	
	int x1 = - 80 * sgn(index1 - index2) * (std::abs(index1 - index2) % 8);
	int x2 =   80 * sgn(index1 - index2) * (std::abs(index1 - index2) % 8);
	int y1 = - 80 * sgn((index1 - index2)/8);
	int y2 =   80 * sgn((index1 - index2)/8);
	
	sprite1->runAction(Action::moveBy(1.0, x1, y1));
	sprite2->runAction(Action::moveBy(1.0, x2, y2));
	
	std::deque<Action*>* d = new std::deque<Action*>();
	d->push_back(Action::wait(1.0));
	//d->push_back(Action::callFunction(std::bind(&LogicSystem::cbResetInput, this, std::placeholders::_1), nullptr));
	d->push_back(Action::callFunction([&](void*){
		inputHandler->setProcessing(true);
	}, nullptr));
	lSprite->runAction(Action::sequence(d));
}

void LogicSystem::cbResetInput(void* payload)
{
	inputHandler->setProcessing(true);
}
	
void LogicSystem::addEntity(int index, artemis::Entity* entity)
{
	entities[index] = entity;
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
