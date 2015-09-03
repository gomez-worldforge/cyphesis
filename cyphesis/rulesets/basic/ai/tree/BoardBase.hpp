//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _BOARDBASE_UTILAI_H_
#define _BOARBASE_UTILAI_H_

/*
 */
#include "ChessRam.hpp"

#include <cstring>

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
	//white is at the top, black at the bottom
	//there is a board for each color
	void startGame() {

		//initialize first with free positions (number 7)
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				whiteboard[j][i] = 7;
				blackboard[j][i] = 7;
			}
		}
				
		//pawns
		for (int i = 0; i < 8; i++) { 
			whiteboard[1][i] = 5;
			blackboard[6][i] = 5;
		}

		//towers
		whiteboard[0][0] = 3;	
		whiteboard[0][7] = 3;	
		blackboard[7][0] = 3;	
		blackboard[7][7] = 3;	
		//knights
		whiteboard[0][1] = 4;	
		whiteboard[0][6] = 4;	
		blackboard[7][1] = 4;	
		blackboard[7][6] = 4;	
		//bishops
		whiteboard[0][2] = 2;	
		whiteboard[0][5] = 2;	
		blackboard[7][2] = 2;	
		blackboard[7][5] = 2;	
		//queen
		whiteboard[0][4] = 1;	
		blackboard[7][4] = 1;	
		//kings
		whiteboard[0][3] = 0;	
		blackboard[7][3] = 0;	
	} 

	int moveWhiteChessPiece(const int &r, const int& c, const int & oldr, const int& oldc);
	int moveBlackChessPiece(const int &r, const int& c, const int & oldr, const int& oldc);

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

	int moveWhiteKing(const int &r, const int& c, const int& oldr, const int& oldc);
	int moveBlackKing(const int &r, const int& c, const int& old, const int& oldc);

	inline char** getWhiteBoard() { return (char **)whiteboard; } 
	inline char** getBlackBoard() { return (char **)blackboard; } 

private:
	char whiteboard[8][8];
	char blackboard[8][8];

public:
	BoardBase operator=(BoardBase& b) { 
		//if (&b == this)
		//	return *this;
		
		std::memcpy((char **)(this->whiteboard), (char **)(b.whiteboard), 64);
		std::memcpy((char **)(this->blackboard), (char **)(b.blackboard), 64);
	}

};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
