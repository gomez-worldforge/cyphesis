//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _BOARDBASE_UTILAI_H_
#define _BOARBASE_UTILAI_H_

/*
 */
#include "ChessRam.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

class BoardBase
{
public:
	explicit BoardBase() {}
	~BoardBase() {}

	//initialize chess board
	void initialize() {
		//pawns
		for (int i = 0; i < 8; i++) { 
			whiteboard[1][i] = 5;
			blackboard[1][i] = 5;
		}

		//towers
		whiteboard[0][0] = 3;	
		whiteboard[0][7] = 3;	
		blackboard[0][0] = 3;	
		blackboard[0][7] = 3;	
		//knights
		whiteboard[0][1] = 4;	
		whiteboard[0][6] = 4;	
		blackboard[0][1] = 4;	
		blackboard[0][6] = 4;	
		//bishops
		whiteboard[0][2] = 2;	
		whiteboard[0][5] = 2;	
		blackboard[0][2] = 2;	
		blackboard[0][5] = 2;	
		//queen
		whiteboard[0][4] = 1;	
		blackboard[0][4] = 1;	
		//kings
		whiteboard[0][3] = 0;	
		blackboard[0][3] = 0;	
	} 

	int moveWhitePawn(const int &r, const int& c);
	int moveBlackPawn(const int &r, const int& c);

	int moveWhiteKnight(const int &r, const int& c, const int& oldr, const int& oldc);
	int moveBlackKnight(const int &r, const int& c, const int& old, const int& oldc);

	int moveWhiteTower(const int &r, const int& c, const int& oldr, const int& oldc);
	int moveBlackTower(const int &r, const int& c, const int& old, const int& oldc);

	int moveWhiteBishop(const int &r, const int& c, const int& oldr, const int& oldc);
	int moveBlackBishop(const int &r, const int& c, const int& old, const int& oldc);

	int moveWhiteQueen(const int &r, const int& c, const int& oldr, const int& oldc);
	int moveBlackQueen(const int &r, const int& c, const int& old, const int& oldc);

	inline char** getWhiteBoard() { return (char **)whiteboard; } 
	inline char** getBlackBoard() { return (char **)blackboard; } 

private:
	char whiteboard[8][8];
	char blackboard[8][8];
	
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
