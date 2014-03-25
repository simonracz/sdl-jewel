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
#include "Node.h"

namespace jewel {

enum class Direction : char {
	Up,
	Down,
	Left,
	Right
};

/**
 * This class represent the model. It is closely tied to the Node class.
 */
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
	
	Node& up(int index);
	Node& down(int index);
	Node& left(int index);
	Node& right(int index);
	
	Node& up(const Node& node);
	Node& down(const Node& node);
	Node& left(const Node& node);
	Node& right(const Node& node);
	
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
	
} //namespace


#endif /* defined(__sdl_jewel__Table__) */
