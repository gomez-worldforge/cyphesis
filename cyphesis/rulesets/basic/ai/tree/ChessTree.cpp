//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "ChessTree.hpp"
#include "Board.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

//The tree is never built, the board is adapted each 
//search for a move, then the position of that move 
//is saved, building a tree is optional
//This way the tree uses best-first search in the Board class
//and is somewhat chaotic (see Board.hpp comments.)
bool ChessTree::breadthFirstSearch(ChessTreeNode& node)
{

	ChessTreeNodes breadthnodes;
	
	//pass-by-reference for a move
	int row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board inside this node to let the AI move
	if (node.get().searchMove(breadthnodes, node.get().getPlayerName(), node, 
		row,col,oldrow,oldcol)) {
		//FIXME do something here for if there's no nodes
	}

	for (ChessTreeNodesIter vi = breadthnodes.begin(); vi != breadthnodes.end(); vi++) {

		node.addNode(*vi);
	}

	//FIXME do the move here NOT on the board but in the node 

	/****
	//cache the position FIXME check for legal move here
	positions.push_back(row);	
	positions.push_back(col);	
	positions.push_back(oldrow);	
	positions.push_back(oldcol);	
	***/
	row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board again with other player move	
	ChessTreeNode n;	
	if (node.get().searchMove(breadthnodes, node.get().getNPCPlayerName(), node,
		col,row,oldrow,oldcol)) {
		//FIXME do something here for if there's no nodes
		/**** FIXME
		//cache the position FIXME check for legal move here
		positions.push_back(row);	
		positions.push_back(col);	
		positions.push_back(oldrow);	
		positions.push_back(oldcol);	
	
		//we made 2 moves and/or strikes so the board has changed
		//thus we continue to change the board inside another node
		ChessTreeNode n = get();	

		//contruct tree further
		node.addNode(n);
	return true;
	} else {
		last = n; 
		return false;
	}		
		*****/
	}		
	for (ChessTreeNodesIter vi = breadthnodes.begin(); vi != breadthnodes.end(); vi++) {

		node.addNode(*vi);
		breadthFirstSearch(*vi);
	}
	return true;
}

//current should contain a board constructed with names
//these are needed to make moves, the default constructor
//of Board has "White" and "Black" as the names of the 
//two players.
bool ChessTree::buildTreeWithBoard(const Board& b)
{

	set(const_cast<Board&>(b));
	root = *this;
	//clear the positions array as we start a new board
	positions.clear();

	//FIXME needs a timer and signal
	breadthFirstSearch(root);

	return true;
}

//build a tree with the current board
bool ChessTree::buildTree()
{

	root = *this;

	//FIXME needs a timer and signal
	breadthFirstSearch(root);

	return true;
}
/******
//The name of the player to make a move
void ChessTree::makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChessTreeNode& t) {
	static_cast<ChessTreeNode&>(*this).get().makeMove(name, 
							row, col, oldrow,
							oldcol, *this);
}

//get a position from the position vector, pass-by-reference 
void ChessTree::getMove(int n, int& row, int& col, int& oldrow, int& oldcol) {
		row = positions[n];
		col = positions[n+1];
		oldrow = positions[n+2];
		oldcol = positions[n+3];
}
*******/
ChessTree::Adapter* ChessTree::createAdapter()
{
	return new ChessTree::ChessTreeAdapter(this);
}

}//namespace chess 
}//namespace tree 
}//namespace utilai	
