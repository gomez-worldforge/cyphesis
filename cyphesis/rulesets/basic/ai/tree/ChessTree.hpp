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
	class Adapter {};
	class ChessTreeAdapter : public Adapter {
	public:
		ChessTreeAdapter(ChessTree *t) { tree = t; }
		//set a position from the position vector
		void setMove(int index, int& row, int& col, int& oldrow, int& oldcol) {
			setRow(row,index,tree->getPositions());
			setCol(col,index,tree->getPositions());
			setOldRow(oldrow,index,tree->getPositions());
			setOldCol(oldcol,index,tree->getPositions());
		}
		
		//get a position from the position vector pass-by-reference
		void getMove(int index, int& row, int& col, int& oldrow, int& oldcol) {
			get(row, index, tree->getPositions());
			get(col, index+1, tree->getPositions());
			get(oldrow, index+2, tree->getPositions());
			get(oldcol, index+3, tree->getPositions());
		}
	
	protected:
		void setRow(int n, int index, std::vector<int>& p) {
			set(n,index,p);
		}
		void setCol(int n, int index, std::vector<int>& p) {
			set(n,index,p);
		}
		void setOldRow(int n, int index, std::vector<int>& p) {
			set(n,index,p);
		}
		void setOldCol(int n, int index, std::vector<int>& p) {
			set(n,index,p);
		}

		
		void set(int n, int index, std::vector<int>& p) {
			p[index] = n;
		}
		void get(int& n, int index, std::vector<int>& p) {
			n = p[index];
		}
	private:
		ChessTree *tree;
	}; 

	explicit ChessTree() : root(),last() { init(64); }
	~ChessTree() {}

	//The name of the player to make a move, then set the board
	void makeMove(std::string& name, const int& row, 
		const int& col, const int& oldrow, const int& oldcol,
		ChessTreeNode& t) {
			static_cast<ChessTreeNode&>(*this).get().makeMove(name, 
						row, col, oldrow,
						oldcol, *this);
	}

	//make a tree for a move
	bool buildTree();
	bool buildTreeWithBoard(const Board& b);
	//prepare chessboard with pieces 
        void startGame() { static_cast<ChessTreeNode&>(*this).startGame(); } 
	
	virtual ChessTree::Adapter* createAdapter();


protected:
	//main recursive algorithm
	bool breadthFirstSearch(ChessTreeNode& node);

private:
	ChessTreeNode root;
	ChessTreeNode last;
	//this vector has quadruples of positions of the form 
	//(row,col,oldrow,oldcol.) This is how moves that have been searched
	//for are cached. It is filled starting with a one color after the other
	std::vector<int> positions;	
	std::vector<int>& getPositions() { return positions; }
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
