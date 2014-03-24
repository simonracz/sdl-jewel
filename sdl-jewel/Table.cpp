//
//  Table.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Table.h"

namespace jewel {

Node Table::nullNode = Node(Node::END, NodeType::Green, Node::END, Node::END, Node::END, Node::END);

Table::Table()
{
	//build the 8x8 table
}
	
//returns Node::END for empty Nodes
Node& Table::up(int index)
{
	int ret = nodes[index].up();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[nodes[index].up()];
}

Node& Table::down(int index)
{
	return nodes[nodes[index].down()];
}
	
Node& Table::left(int index)
{
	return nodes[nodes[index].left()];
}
	
Node& Table::right(int index)
{
	return nodes[nodes[index].right()];
}

Node& Table::getNode(int index)
{
	return nodes[index];
}

int Table::getWidth()
{
	return width;
}
	
int Table::getHeight()
{
	return height;
}

bool Table::checkSwap(int first, int second)
{
	swapElements(first, second);
	std::set<std::pair<int,Direction>> results;
	check(results);
	swapElements(first, second);
	
	return (results.size()!=0);
}
	
void Table::swapElements(int first, int second)
{
	std::swap(nodes[first].type, nodes[second].type);
}

//Results returns pairs
//first element is a Node index
//second element is the direction
void Table::check(std::set<std::pair<int,Direction>>& results)
{
	
}

void Table::applyNextStep(std::set<int>& newNodes)
{
	
}
	
} //namespace