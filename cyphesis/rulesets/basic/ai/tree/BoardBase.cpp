//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "BoardBase.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

//NOTE pawns move 1 forward whereas the rest moves acoording to
//r and c
int BoardBase::moveWhitePawn(const int &r, const int& c) {
	whiteboard[r+1][c] = whiteboard[r][c];
	whiteboard[r][c] = 7;
}	

int BoardBase::moveBlackPawn(const int &r, const int& c) {
	blackboard[r+1][c] = blackboard[r][c];
	blackboard[r][c] = 7; 
}	

int BoardBase::moveWhiteKnight(const int &r, const int& c, const int& oldr, const int& oldc) {
	whiteboard[r][c] = whiteboard[oldr][oldc];
	whiteboard[oldr][oldc] = 7;
}	

int BoardBase::moveBlackKnight(const int &r, const int& c, const int& oldr, const int& oldc) {
	blackboard[r][c] = blackboard[oldr][oldc];
	blackboard[oldr][oldc] = 7; 
}	

int BoardBase::moveWhiteTower(const int &r, const int& c, const int& oldr, const int& oldc) {
	whiteboard[r][c] = whiteboard[oldr][oldc];
	whiteboard[oldr][oldc] = 7;
}	

int BoardBase::moveBlackTower(const int &r, const int& c, const int& oldr, const int& oldc) {
	blackboard[r][c] = blackboard[oldr][oldc];
	blackboard[oldr][oldc] = 7; 
}	

int BoardBase::moveWhiteBishop(const int &r, const int& c, const int& oldr, const int& oldc) {
	whiteboard[r][c] = whiteboard[oldr][oldc];
	whiteboard[oldr][oldc] = 7;
}	

int BoardBase::moveBlackBishop(const int &r, const int& c, const int& oldr, const int& oldc) {
	blackboard[r][c] = blackboard[oldr][oldc];
	blackboard[oldr][oldc] = 7; 
}	

int BoardBase::moveWhiteQueen(const int &r, const int& c, const int& oldr, const int& oldc) {
	whiteboard[r][c] = whiteboard[oldr][oldc];
	whiteboard[oldr][oldc] = 7;
}	

int BoardBase::moveBlackQueen(const int &r, const int& c, const int& oldr, const int& oldc) {
	blackboard[r][c] = blackboard[oldr][oldc];
	blackboard[oldr][oldc] = 7; 
}	

}//namespace chess 
}//namespace tree 
}//namespace utilai	
