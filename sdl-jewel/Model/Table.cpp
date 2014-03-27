//
//  Table.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Table.h"
#include <chrono>
#include <iostream>

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
	width = 8;
	height = 8;

	std::set<NodeType> allowedColors{NodeType::Green, NodeType::Blue, NodeType::Purple, NodeType::Red, NodeType::Yellow};
	
	for (int i=63; i>=0; --i) {
		std::set<NodeType> tmpSet = allowedColors;
		Node& node = nodes[i];
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
			nodes[ind].gravityUp = (i>0)?(ind-8):(Node::END);
		}
	}
}

//To prevent an automatic gem crushing at startup.
void Table::filterColors(Node& node, std::set<NodeType>& allowedColors)
{
	Node neighbor = up(node);
	if ((neighbor != nullNode) && (up(neighbor)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = down(node);
	if ((neighbor != nullNode) && (down(neighbor)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = left(node);
	if ((neighbor != nullNode) && (left(neighbor)).type == neighbor.type) {
		allowedColors.erase(neighbor.type);
	}
	neighbor = right(node);
	if ((neighbor != nullNode) && (right(neighbor)).type == neighbor.type) {
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

Node& Table::gUp(int index)
{
	int ret = nodes[index].gUp();
	if (ret == Node::END) {
		return nullNode;
	}
	
	return nodes[ret];
}

Node& Table::gUp(const Node& node)
{
	return gUp(node.index);
}
	
Node& Table::up(const Node& node)
{
	return up(node.index);
}
Node& Table::down(const Node& node)
{
	return down(node.index);
}
Node& Table::left(const Node& node)
{
	return left(node.index);
}
Node& Table::right(const Node& node)
{
	return right(node.index);
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
	std::set<int> results;
	checkNode(getNode(first), results);
	checkNode(getNode(second), results);
	swapElements(first, second);
	
	return (results.size()!=0);
}
	
void Table::checkNode(const Node& node, std::set<int>& results)
{
	NodeType type = node.type;
	
	Node neighbor = up(node);
	if ((neighbor.type == type) && ((up(neighbor).type == type) || (down(node).type == type))) {
		results.insert(node.index);
		Node ne = node;
		for (int dist = 1; dist<7; ++dist) {
			ne = up(ne);
			if (ne.type != type) {
				break;
			}
			results.insert(ne.index);
		}
	}
	neighbor = down(node);
	if ((neighbor.type == type) && ((down(neighbor).type == type) || (up(node).type == type))) {
		results.insert(node.index);
		Node ne = node;
		for (int dist = 1; dist<7; ++dist) {
			ne = down(ne);
			if (ne.type != type) {
				break;
			}
			results.insert(ne.index);
		}
	}
	neighbor = left(node);
	if ((neighbor.type == type) && ((left(neighbor).type == type) || (right(node).type == type))) {
		results.insert(node.index);
		Node ne = node;
		for (int dist = 1; dist<7; ++dist) {
			ne = left(ne);
			if (ne.type != type) {
				break;
			}
			results.insert(ne.index);
		}
	}
	neighbor = right(node);
	if ((neighbor.type == type) && ((right(neighbor).type == type) || (left(node).type == type))) {
		results.insert(node.index);
		Node ne = node;
		for (int dist = 1; dist<7; ++dist) {
			ne = right(ne);
			if (ne.type != type) {
				break;
			}
			results.insert(ne.index);
		}
	}
}
	
void Table::swapElements(int first, int second)
{
	std::swap(nodes[first].type, nodes[second].type);
}

void Table::check(std::set<int>& results)
{
	for (int i = 63; i>=0; --i) {
		checkNode(getNode(i), results);
	}
}

void Table::applyNextStep(std::set<int>& nodesFell, std::set<int>& newNodes)
{
	std::set<int> results;
	for (int i = 63; i>=0; --i) {
		checkNode(getNode(i), results);
	}
	
	for (auto i : results) {
		getNode(i).type = NodeType::None;
	}
	
	for (int i=7; i>=0; --i) {
		bool found = false;
		for (int j=7; j>=0; --j) {
			if (found) {
				swapElements(j*8+i, (j+1)*8 +i);
				if (getNode((j+1)*8 + i).type != NodeType::None) {
					nodesFell.insert((j+1)*8 +i);
				}
			}
			if (getNode(j*8 + i).type == NodeType::None) {
				found = true;
			}
		}
		if (found) {
			newNodes.insert(i);
			getNode(i).type = static_cast<NodeType>(distributions[3](m));
		}
	}
}
	
bool Table::hasEmpty()
{
	for (int i = 63; i>=0; --i) {
		if (getNode(i).type == NodeType::None) {
			return true;
		}
	}
	
	return false;
}
	
} //namespace