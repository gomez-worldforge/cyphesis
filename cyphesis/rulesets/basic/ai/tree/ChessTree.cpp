//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "ChessTree.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

bool ChessTree::breadthFirstSearch(ChessTreeNode& node)
{
	node.get().searchMove(node.get().getPlayerName(), node);	
	if (!node.get().searchMove(node.get().getNPCPlayerName(), node)) {	
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
