//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "ChessTree.hpp"

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
	//pass-by-reference for a move
	int row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board inside this node to let the AI move
	if (node.get().searchMove(node.get().getPlayerName(), node, 
		row,col,oldrow,oldcol)) {
		//cache the position FIXME check for legal move here
		positions.push_back(row);	
		positions.push_back(col);	
		positions.push_back(oldrow);	
		positions.push_back(oldcol);	
	}

	row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board again with other player move	
	if (node.get().searchMove(node.get().getNPCPlayerName(), node,
		col,row,oldrow,oldcol)) {

		//cache the position FIXME check for legal move here
		positions.push_back(row);	
		positions.push_back(col);	
		positions.push_back(oldrow);	
		positions.push_back(oldcol);	

		//we made 2 moves and/or strikes so the board has changed
		//thus we continue to change the board inside another node
		ChessTreeNode n(get());	
	
		breadthFirstSearch(n);
		return true;
	} else {
		return false;
	}		
}

//current should contain a board constructed with names
//these are needed to make moves, the default constructor
//of Board has "White" and "Black" as the names of the 
//two players.
bool ChessTree::buildTree(const Board& current)
{

	set(const_cast<Board&>(current));
	root = *this;

	//FIXME needs a timer and signal
	breadthFirstSearch(root);

	return true;
}

//The name of the player to make a move
void ChessTree::makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChessTreeNode& t) {
	static_cast<ChessTreeNode&>(*this).get().makeMove(name, 
							row, col, oldrow,
							oldcol, *this);
}

}//namespace chess 
}//namespace tree 
}//namespace utilai	
