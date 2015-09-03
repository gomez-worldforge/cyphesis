//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _BOARD_UTILAI_H_
#define _BOARD_UTILAI_H_

/*
 * NOTE
 * 
 * Board contains both a black and white playing board (in ChessRam.hpp)
 * It contains the breadth of the breadth search algorithm (in ChessTree.hpp)
 * The move function dispatches a player name and stores them in playername
 * for white and blackplayername for black.
 * Each time a breadth first search move gets calculated the move looks at
 * the white or black playing board and builds member nodes of the ChessTreeNode
 * parameter. Both players can be an AI (NPC) or a Person (PC). The code
 * is somewhat towards a black AI player and a white player as a person.
 * 
 * There's a threshold (called percentage) which gains more entropy when you
 * make a good strike e.g. a pawn striking a knight. This can be changed if
 * you like.
 *
 * Each time you strike you gain a good node (goodnodes list variable),
 *
 * There also is a mode flag which alters the route search for optimization. 
 *
 */

#include "Grid.hpp"
#include "BoardBase.hpp"

#include <string>
#include <vector>

namespace utilai
{
namespace tree 
{
namespace chess 
{
class BoardBase;
class ChessTree;
class ChessTreeNode;

typedef std::vector<ChessTreeNode> ChessTreeNodes;
typedef std::vector<ChessTreeNode>::iterator ChessTreeNodesIter;

class Board : protected Grid, BoardBase 
{
public:
	Board(const std::string player, const std::string blackplayer) 
		: Grid(),BoardBase(),width(8),height(8),percentage(1),
		  mode(10),
		  playername(const_cast<std::string&>(player)), 
		  blackplayername(const_cast<std::string&>(blackplayer)) 
		{}
	Board() 
		: Grid(),BoardBase(),width(8),height(8),percentage(1),
		  mode(10),
		  playername("White"), 
		  blackplayername("Black") 

		{}
	~Board() {}

	//make a move based on row and column
	//note that the treenode is optional
	void makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChessTreeNode& t);
	//let the AI move based on a treenode
	bool searchMove(std::string& name, ChessTreeNode& t,
			int& row, int& col, int& oldrow, int& oldcol);

	//test if the move has been done
	bool legalmove(std::string& name, ChessTreeNode& t, int& row, int& col, 
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
	char getWhiteBoardXY(int x, int y) { return (getWhiteBoard())[y][x]; }
	char getBlackBoardXY(int x, int y) { return (getBlackBoard())[y][x]; }
	std::string& getPlayerName() { return playername; }
	std::string& getNPCPlayerName() { return blackplayername; }

public:
	Board operator=(Board& b) { 
		/*if (b == *this)
			return *this;
		*/
		static_cast<BoardBase&>(*this) = static_cast<BoardBase&>(b);
	}
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
