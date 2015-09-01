//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSTREE_UTILAI_H_
#define _CHESSTREE_UTILAI_H_

#include "Tree.hpp"
#include "ChessTreeNode.hpp"
/*
 */

namespace utilai
{
namespace tree 
{
namespace chess 
{
class ChessTree : protected Tree<ChessTreeNode>
{
public:
	explicit ChessTree() : root() { init(64); /*FIXME this is much higher sometimes */
	}
	~ChessTree() {}

	int makeTree(const Board& current);
	//prepare chessboard with pieces 
        void startGame() { static_cast<ChessTreeNode&>(*this).startGame(); } 

	int depth_first_search(ChessTreeNode& node);
	//int breath_first_search(ChessTreeNode& node);

private:
	ChessTreeNode root;
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
