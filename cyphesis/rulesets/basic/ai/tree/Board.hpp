//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _BOARD_UTILAI_H_
#define _BOARD_UTILAI_H_

/*
 */

#include "Grid.hpp"
#include "BoardBase.hpp"

#include <string>
#include <list>

namespace utilai
{
namespace tree 
{
namespace chess 
{
class BoardBase;
class ChessTree;
class ChessTreeNode;

typedef std::list<ChessTreeNode> ChessTreeNodes;
typedef std::list<ChessTreeNode>::iterator ChessTreeNodesIter;

class Board : protected Grid, BoardBase 
{
public:
	Board(const std::string player, const std::string blackplayer) 
		: Grid(),BoardBase(),width(8),height(8),percentage(1),
		  mode(0),
		  playername(const_cast<std::string&>(player)), 
		  blackplayername(const_cast<std::string&>(blackplayer)) 
		{}
	Board() 
		: Grid(),BoardBase(),width(8),height(8),percentage(1),
		  mode(0),
		  playername("White"), 
		  blackplayername("Black") 

		{}
	~Board() {}

	//make a move based on row and column
	//note that the treenode is optional
	void makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChesstreeNode& t = ChessTreeNode());
	//let the AI move based on a treenode
	bool searchMove(std::string& name, ChessTreeNode& t);

	//test if the move has been done
	bool legalmove(ChessTreeNode& t, int& row, int& col, 
			int& oldrow, int& oldcol);
	//list based search on best single move
	bool move(std::string& name, ChessTreeNode& t);

	//AI moves of chess pieces
	//pawns
	bool movePawn(std::string& name, char r, char c);
	bool strikePawn(std::string& name, char r, char c);
	//knights
	bool moveKnight(std::string& name, char r, char c);
	bool strikeKnight(std::string& name, char r, char c);
	//towers
	bool moveTower(std::string& name, char r, char c, char oldr, char oldc);
	bool strikeTower(std::string& name, char r, char c, char oldr, char oldc);
	//bishops
	bool moveBishop(std::string& name, char r, char c, char oldr, char oldc);
	bool strikeBishop(std::string& name, char r, char c, char oldr, char oldc);
	//queens
	bool moveQueen(std::string& name, char r, char c, char oldr, char oldc);
	bool strikeQueen(std::string& name, char r, char c, char oldr, char oldc);

	//kings
	bool moveKing(std::string& name, char r, char c, char oldr, char oldc);
	bool strikeKing(std::string& name, char r, char c, char oldr, char oldc);

	//mode set for play
	//mode 0 is for best play, higher and lower change the list search
	//in the function searchMove (see above)
	void setmode(int n) { mode = n; }	

private:
	int height, width;
	int percentage; //strike lower value	
	int mode;

	std::string playername, blackplayername;
	ChessTreeNodes goodnodes;
	ChessTreeNodes route;

public:	
	Board& getBoard() { return (*this); }

};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
