//
//  Table.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Table.h"
#include <chrono>

namespace jewel {

Node Table::nullNode = Node(Node::END, NodeType::None, Node::END, Node::END, Node::END, Node::END);
	
Table::Table()
{
	m = std::mt19937(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	distributions.emplace_back(std::uniform_int_distribution<int> (0,1));
	distributions.emplace_back(std::uniform_int_distribution<int> (0,2));
	distributions.emplace_back(std::uniform_int_distribution<int> (0,3));
	distributions.emplace_back(std::uniform_int_distribution<int> (0,4));

	//build the 8x8 table
	fillTable();
		
	std::set<NodeType> allowedColors{NodeType::Green, NodeType::Blue, NodeType::Purple, NodeType::Red, NodeType::Yellow};
	
	for (int i=63; i>=0; --i) {
		std::set<NodeType> tmpSet = allowedColors;
		Node node = nodes[i];
		filterColors(node, tmpSet);
		if (tmpSet.size() == 1) {
			node.type = *tmpSet.begin();
			continue;
		}
		
		auto dist = distributions[tmpSet.size() - 2];
		int rndColor = dist(m);
		for (auto it = tmpSet.begin(); it!=tmpSet.end(); ++it) {
			if (rndColor == 0) {
				node.type = *it;
				break;
			}
			
			--rndColor;
		}
	}
}
	
void Table::fillTable()
{
	nodes = std::vector<Node>(64);
	
	for (int i=7; i>=0; --i) {
		for (int j=7; j>=0; --j) {
			int ind = i*8 + j;
			nodes[ind].index = ind;
			nodes[ind].setNeighbors((i>0)?(ind-8):(Node::END),
									(i<7)?(ind+8):(Node::END),
									(j>0)?(ind-1):(Node::END),
									(j<7)?(ind+1):(Node::END)
									);
		}
	}
}

//To prevent an automatic gem crushing at startup.
void Table::filterColors(Node& node, std::set<NodeType>& allowedColors)
{
	Node neighbor = up(node.index);
	if ((neighbor.type != NodeType::None) && (up(neighbor.index)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = down(node.index);
	if ((neighbor.type != NodeType::None) && (down(neighbor.index)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = left(node.index);
	if ((neighbor.type != NodeType::None) && (left(neighbor.index)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = right(node.index);
	if ((neighbor.type != NodeType::None) && (right(neighbor.index)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
}
	
Node& Table::up(int index)
{
	int ret = nodes[index].up();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[ret];
}

Node& Table::down(int index)
{
	int ret = nodes[index].down();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[ret];

}
	
Node& Table::left(int index)
{
	int ret = nodes[index].left();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[ret];

}
	
Node& Table::right(int index)
{
	int ret = nodes[index].right();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[ret];

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
	//TODO
	//Smarter check
	//check only the two indexes
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