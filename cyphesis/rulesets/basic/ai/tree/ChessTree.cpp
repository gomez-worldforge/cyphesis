//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "ChessTree.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

//We build a tree here with ChessTreeNodes
bool ChessTree::breadthFirstSearch(ChessTreeNode& node)
{
	//pass-by-reference for a move
	int row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board inside this node to let the AI move
	node.get().searchMove(node.get().getPlayerName(), node, 
		row,col,oldrow,oldcol);

	//cache the position FIXME check for legal move here
	positions.push_back(row);	
	positions.push_back(col);	
	positions.push_back(oldrow);	
	positions.push_back(oldcol);	

	//set board again with other player move	
	if (!node.get().searchMove(node.get().getNPCPlayerName(), node,
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
	} else {
		return true;
	}		
}

bool ChessTree::buildTree(const Board& current)
{

	set(const_cast<Board&>(current));
	root = *this;

	//FIXME needs a timer
	breadthFirstSearch(root);

	return true;
}


}//namespace chess 
}//namespace tree 
}//namespace utilai	
