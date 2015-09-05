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

	void addNode(TreeNode& tn) { static_cast<TreeNode>(*this).addNode(tn); }
	TreeNode& getNode() { static_cast<TreeNode>(*this).getNode(); }
	void startGame() { board.startGame(); }

	void set(const Board& b) { board = const_cast<Board&>(b); }
	Board& get() { return board; }

protected:
	bool breadthFirstSearch(ChessTreeNode& node) {}
private:
	Board board;

public:
	ChessTreeNode operator=(ChessTreeNode n) {
		/* if (*this == n) return (*this); */
		this->board = n.board;
		
		return *this;
	}

	std::vector<int>& getPositions() { return positions; }
	void addPosition(int row, int col, int oldrow, int oldcol) { 
		positions.push_back(row); 
		positions.push_back(col); 
		positions.push_back(oldrow); 
		positions.push_back(oldcol); 
	}
	std::vector<int> positions;
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
