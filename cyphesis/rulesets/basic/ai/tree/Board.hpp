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
//FIXME typedef std::list<ChessTreeNode&>::iterator ChessTreeNodesIter;

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

	bool beginMove(std::string& name, ChessTreeNode& t);

	bool move(std::string& name, ChessTreeNode& t);
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

	void setmode(int n) { mode = n; }	

private:
	int height, width;
	int percentage; //strike lower value	
	int mode;

	std::string playername, blackplayername;
	ChessTreeNodes goodnodes;
	ChessTreeNodes route;

	
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
