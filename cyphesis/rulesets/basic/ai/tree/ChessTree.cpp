//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "ChessTree.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

int ChessTree::depth_first_search(ChessTreeNode& node)
{
	node.get().makeMove(node.get().getPlayerName());	
	node.get().makeMove(node.get().getNPCPlayerName());	
	ChessTreeNode *n = new ChessTreeNode(board);	
	
	depth_first_search(n);
}

int ChessTree::makeTree(const Board& current)
{

	set(const_cast<Board&>(current));
	root = current;

	depth_first_search(root);		
}


}//namespace chess 
}//namespace tree 
}//namespace utilai	
