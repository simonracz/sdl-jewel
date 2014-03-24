//
//  Table.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Table__
#define __sdl_jewel__Table__

#include <vector>
#include <set>
#include <utility>
#include <random>
#include "SDL2/SDL.h"

namespace jewel {

enum class Direction : char {
	Up,
	Down,
	Left,
	Right
};

enum class NodeType : char {
	Green = 0,
	Red,
	Yellow,
	Blue,
	Purple,
	None
};

/**
 * The current maximum table size is 15x15
 * Index 255 means there is no neighbor
 * This Node is very general. It supports complex levels, e.g. antigravity
 * A more general Node could store a state too, e.g. it could change it's neighbors based on it's actual state.
 */
struct Node{
public:
	Uint32 neighbors{0xFFFFFFFF};
	NodeType type{NodeType::None};
	Uint8 index{0};
	
	Node();
	Node(Uint8 index, NodeType type);
	Node(Uint8 index, NodeType type, Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	inline void setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	inline int up();
	inline int down();
	inline int left();
	inline int right();
	
	inline int getIndex();
	
	bool operator==(const Node& theOther);
	bool operator!=(const Node& theOther);
	
	void swap(Node& theOther);
	
	static const int END = 255;
};


class Table {
private:
	std::vector<Node> nodes;
	int width;
	int height;
	std::vector<std::uniform_int_distribution<int>> distributions;
	std::mt19937 m;
public:
	//It creates the 8x8 demo level
	Table();
	
	//To load an arbitrary level from a data file
	//Table(std::string path);
	
	//returns Node::END for empty Nodes
	Node& up(int index);
	Node& down(int index);
	Node& left(int index);
	Node& right(int index);
	
	//This Node is used to fill in the possible gaps in the table.
	//It makes sure that the indexes are correct.
	static Node nullNode;
	
	Node& getNode(int index);
	
	int getWidth();
	int getHeight();
	
	bool checkSwap(int first, int second);
	void swapElements(int first, int second);
	
	//Results returns pairs
	//first element is a Node index
	//second element is the direction
	void check(std::set<std::pair<int,Direction>>& results);
	void applyNextStep(std::set<int>& newNodes);
private:
	//helper functions
	void fillTable();
	void filterColors(Node& node, std::set<NodeType>& allowedColors);
};

	
	
//Node implementation
int Node::up()
{
	return (neighbors & 0xFF);
}
int Node::down()
{
	return ((neighbors>>4) & 0xFF);
}
int Node::left()
{
	return ((neighbors>>8) & 0xFF);
}
int Node::right()
{
	return ((neighbors>>12) & 0xFF);
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

void Node::setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right)
{
	neighbors = up;
	Uint32 temp = down;
	neighbors |= (temp << 4);
	temp = left;
	neighbors |= (temp << 8);
	temp = right;
	neighbors |= (temp << 12);
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


#endif /* defined(__sdl_jewel__Table__) */
