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
bool ChessTree::depthFirstSearchChess(ChessTreeNode& node)
{
	for (ChessTreeNode *n = static_cast<ChessTreeNode*>(&getNode()); !node.atEnd(); ) {
		if (chess(*n)) {
			last = *n;
			positions = last.getPositions();
			return true;
		} else {
			depthFirstSearchChess(*n);
		}
	}
	return false;
}

bool ChessTree::depthFirstSearchChessMat(ChessTreeNode& node)
{
	for (ChessTreeNode *n = static_cast<ChessTreeNode*>(&getNode()); !node.atEnd(); ) {
		if (chessmat(*n)) {
			last = *n;
			positions = last.getPositions();
			return true;
		} else {
			depthFirstSearchChessMat(*n);
		}
	}
	return false;
}

//The tree is built, the board is adapted each 
//search for a move, then the position of that move 
//is saved
//This way the tree uses best-first search for chess piece striking in the 
//Board class and is somewhat chaotic (see Board.hpp comments.)
//the variable breadthnodes are good strikes or all moves which can be done
bool ChessTree::buildBreadthFirstSearch(ChessTreeNode& node)
{

	//pass-by-reference for a move
	ChessTreeNodes breadthnodes;
	int row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board inside this node to let the AI move
	if (node.get().searchMove(breadthnodes, node.get().getPlayerName(), node, 
		row,col,oldrow,oldcol)) {

		//we add the position to an array
		//that gets set when we encounter a chess position	
		node.addPosition(row,col,oldrow,oldcol);

	}
	//add good nodes or a route, after first AI move
	for (ChessTreeNodesIter vi = breadthnodes.begin(); vi != breadthnodes.end(); vi++) {

		node.addNode(*vi);
	}

	//reinit position for other player AI
	row = -1, col = -1, oldrow = -1, oldcol = -1;
	//set board again with other player move	
	ChessTreeNode n;	
	if (node.get().searchMove(breadthnodes, node.get().getNPCPlayerName(), node,
		col,row,oldrow,oldcol)) {
		//we add the position to an array
		//that gets set when we encounter a chess position	
		node.addPosition(row,col,oldrow,oldcol);

	}
	//after both AIs have moved, again add a node
	//we do not care for this first and second node breadth
	//of the tree as we cache positions while searching which
	//is a path to chess position or something		
	for (ChessTreeNodesIter vi = breadthnodes.begin(); vi != breadthnodes.end(); vi++) {

		node.addNode(*vi);
		buildBreadthFirstSearch(*vi);
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
	buildBreadthFirstSearch(root);

	return true;
}

//build a tree with the current board
bool ChessTree::buildTree()
{

	root = *this;

	//FIXME needs a timer and signal
	buildBreadthFirstSearch(root);

	return true;
}

bool ChessTree::chess(ChessTreeNode& n)
{
	return get().chess(get().getCurrentPlayerName(), n);	
}

bool ChessTree::chessmat(ChessTreeNode& n)
{
	return get().chessmat(get().getCurrentPlayerName(), n);	
}

ChessTree::Adapter* ChessTree::createAdapter()
{
	return new ChessTree::ChessTreeAdapter(this);
}

}//namespace chess 
}//namespace tree 
}//namespace utilai	
