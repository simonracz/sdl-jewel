//
//  Action.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Action__
#define __sdl_jewel__Action__

#include <vector>
#include <set>
#include <functional>

namespace jewel {
		
class ActionSystem;
class Sprite;
	
class Action {
friend class ActionSystem;
private:
	static void initActions(ActionSystem* system);
	void removeFromSprite();
protected:
	//max 1000 concurrent Actions
	static std::set<int> freeIds;
	static ActionSystem* actionSystem;
	
	int id;
	Sprite* sprite{nullptr};
	Action* parentAction{nullptr};
	
	Action();
	
	virtual void setParentAction(Action* action);
	
	/**
	 * Returns false if it's finished.
	 *
	 * The Sprite parameter is required for the container Actions.
	 * It is used only internally.
	 */
	virtual bool process(float delta, Sprite* sprite = nullptr) = 0;
	
	/**
	 * Returns true if it's finished.
	 */
	virtual bool isFinished() = 0;
public:
	virtual ~Action();
	virtual float getMaxTime() = 0;
	
	inline bool operator<(const Action& theOther);
	
	virtual void setSprite(Sprite* sprite);
	void startAction();
	void pauseAction();
	
	static Action* wait(float delta);
	static Action* moveBy(float delta, int x, int y);
	static Action* moveTo(float delta, int x, int y);
	static Action* alphaTo(float delta, int alpha);
	static Action* callFunction(std::function<void(void*)> fnct, void* payload);
	static Action* sequence(std::vector<Action*>& actions);
	static Action* group(std::set<Action*>& actions);
};

bool Action::operator<(const Action& theOther)
{
	return (id < theOther.id);
}
		
}

#endif /* defined(__sdl_jewel__Action__) */
