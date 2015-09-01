//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSTREENODE_UTILAI_H_
#define _CHESSTREENODE_UTILAI_H_

#include "Board.hpp"
#include "TreeNode.hpp"

/*
 */
namespace utilai
{
namespace tree 
{
namespace chess 
{
class ChessTreeNode : protected TreeNode
{
public:
	ChessTreeNode() {}
	ChessTreeNode(Board b) : board(b) {}
	~ChessTreeNode() {}

	void addNode(ChessTreeNode tn) { static_cast<TreeNode>(*this).addNode(tn); }
	void initialize() { board.initialize(); }
protected:
	void set(const Board& b) { board = const_cast<Board&>(b); }
	Board& get() { return board; }

private:
	Board board;
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	