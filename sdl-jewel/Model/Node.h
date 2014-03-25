//
//  Node.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Node__
#define __sdl_jewel__Node__

#include "SDL2/SDL.h"
#include <utility>

namespace jewel {

enum class NodeType : char {
	Green = 0,
	Red,
	Yellow,
	Blue,
	Purple,
	None
};

/**
 * The Node class is closely tied to the Table class.
 *
 * The current maximum table size is 15x15.
 * Index 255 (Node::END) means there is no neighbor.
 * This Node is more general than needed. It supports complex levels, e.g. antigravity, empty fields etc.
 * An even more general Node could store a state too and switch it's neighbors and/or gravity based on it.
 */
struct Node{
public:
	Uint32 neighbors{0xFFFFFFFF};
	NodeType type{NodeType::None};
	Uint8 index{0};
	
	inline Node();
	inline Node(Uint8 index, NodeType type);
	inline Node(Uint8 index, NodeType type, Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	void setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	inline int up();
	inline int down();
	inline int left();
	inline int right();
	
	inline int getIndex();
	
	inline bool operator==(const Node& theOther);
	inline bool operator!=(const Node& theOther);
	
	inline void swap(Node& theOther);
	
	static const int END;
};

//Node implementation
int Node::up()
{
	return (neighbors & 0xFFU);
}
int Node::down()
{
	return ((neighbors>>8) & 0xFFU);
}
int Node::left()
{
	return ((neighbors>>16) & 0xFFU);
}
int Node::right()
{
	return ((neighbors>>24) & 0xFFU);
}
int Node::getIndex()
{
	return index;
}

Node::Node()
{
	//empty
}

Node::Node(Uint8 index, NodeType type) : index(index), type(type)
{
	//empty
}

Node::Node(Uint8 index, NodeType type, Uint8 up, Uint8 down, Uint8 left, Uint8 right) : index(index), type(type)
{
	setNeighbors(up, down, left, right);
}

bool Node::operator==(const Node& theOther)
{
	return (index == theOther.index);
}
bool Node::operator!=(const Node& theOther)
{
	return (index != theOther.index);
}

void Node::swap(Node& theOther)
{
	std::swap(index, theOther.index);
	std::swap(neighbors, theOther.neighbors);
	std::swap(type, theOther.type);
}

} //namespace
	
#endif /* defined(__sdl_jewel__Node__) */
