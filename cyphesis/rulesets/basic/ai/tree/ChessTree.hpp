//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSTREE_UTILAI_H_
#define _CHESSTREE_UTILAI_H_

#include "Tree.hpp"
#include "ChessTreeNode.hpp"
/*
 */

#include <vector>

namespace utilai
{
namespace tree 
{
namespace chess 
{

class ChessTree : protected Tree<ChessTreeNode>
{
public:
	explicit ChessTree() : root() { init(64); }
	~ChessTree() {}

	//make a tree for a move
	bool buildTree();
	bool buildTreeWithBoard(const Board& b);
	//prepare chessboard with pieces 
        void startGame() { static_cast<ChessTreeNode&>(*this).startGame(); } 

	//get a position from the position vector, pass-by-reference 
	void getMove(int n, int& row, int& col, int& oldrow, int& oldcol) {
		row = positions[n];
		col = positions[n+1];
		oldrow = positions[n+2];
		oldcol = positions[n+3];
	}
	
	//move deliberatly
	void makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChessTreeNode& t);
protected:
	//main recursive algorithm
	bool breadthFirstSearch(ChessTreeNode& node);

private:
	ChessTreeNode root;
	//this vector has quadruples of positions of the form 
	//(row,col,oldrow,oldcol.) This is how moves that have been searched
	//for are cached. It is filled starting with a one color after the other
	std::vector<int> positions;	

public:
	ChessTree& operator=(ChessTree t) {
		/*if (*this == t) return (*this);*/

		this->root = t.root;
		this->positions = t.positions;
		return (*this);
	}

};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
