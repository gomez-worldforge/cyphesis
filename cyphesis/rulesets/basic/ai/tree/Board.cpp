//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "Board.hpp"
#include "ChessTree.hpp"

namespace utilai
{
namespace tree 
{
namespace chess 
{

bool Board::beginMove(std::string& name, ChessTreeNode& t) {
	if (playername == name) {
		move(name, t);
	} else if (blackplayername == name) {
		move(name, t);
		
		if (goodnodes.empty()) {//we did not strike a chess piece	
			if (route.empty())
				return false;
			else {
				
			}
		} else {//we stroke a chess piece
			for (ChessNodesIter vi = route.begin();
					vi != route.end();
					vi++) {
				int row = 0, col = 0, oldrow = 0, oldcol = 0;
				if (!legalmove(goodnodes[goodnodes.size()-1],row,col,oldrow,oldcol))
					return false;
				else {
					moveBlackChessPiece(row,col,oldrow,oldcol);
					percentage = 1;
					return true;		
				}
			}
		//percentage = 1;
		}
	} 

	return false;
}

bool Board::legalmove(ChessTreeNode& ti, int& row, int& col, int& oldrow, int& oldcol) {
	int i = 0, j = 0;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((t.get())[i][j] >> (get())[i][j] == 0) 
				continue;
			else {
				if ((t.get())[i][j] == 7) { 
					oldrow = i;
					oldcol = j;
				} else {
					row = i;
					col = j;
				}
			}		
			
		}
	}

	j++;

	for ( ; i < 8; i++) {
		for ( ; j < 8; j++) {
			if ((t.get())[i][j] >> (get())[i][j] == 0) 
				continue;
			else {
				if ((t.get())[i][j] == 7) { 
					oldrow = i;
					oldcol = j;
					return true;
				} else {
					row = i;
					col = j;
					return false;
				}
			}		
			
		}
	}
	return false;
}

bool Board::move(std::string& name, ChessTreeNode& t)
{
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
	
			switch(getWhiteBoard()[j][i]) {
				case 5:{//pawn
					ChessTreeNode *n = new ChessTreeNode(*this);
					if (!movePawn(name, j,i))
						if (!strikePawn(name, j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
					route.push_back(*n);
					t.addNode(*n);
					return true;
					break;
				}
				case 4:{//knight	
					ChessTreeNode *n = new ChessTreeNode(*this);
					if (!moveKnight(name, j,i))
						if (!strikeKnight(name, j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
					route.push_back(*n);
					t.addNode(*n);
					
					break;
				}	
				case 3:{//tower				
					ChessTreeNode *n = new ChessTreeNode(*this);
					for (int k = 1; k < 8-i; k++) {
						if (!moveTower(name, k,i,j,i))
							if (!strikeTower(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < 8-j; k++) {
						n = new ChessTreeNode(*this);
						if (!moveTower(name, j,k,j,i))
							if (!strikeTower(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < i; k++) {
						n = new ChessTreeNode(*this);
						if (!moveTower(name, k,i,j,i))
							if (!strikeTower(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < j; k++) {
						n = new ChessTreeNode(*this);
						if (!moveTower(name, j,k,j,i))
							if (!strikeTower(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					if (!mode)	
						route.push_back(*n);
					break;
				}	
				case 2:{//bishop									
					ChessTreeNode *n = new ChessTreeNode(*this);
					for (int k = 1; k < 8-i; k++) {
						if (i != j)
							continue;
						if (!moveBishop(name, k,i,j,i))
							if (!strikeBishop(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < 8-j; k++) {
						if (i != j)
							continue;
						if (!moveBishop(name, j,k,j,i))
							if (!strikeBishop(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < i; k++) {
						if (i != j)
							continue;
						if (!moveBishop(name, k,i,j,i))
							if (!strikeBishop(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < j; k++) {
						if (i != j)
							continue;
						if (!moveBishop(name, j,k,j,i))
							if (!strikeBishop(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					if (!mode)
						route.push_back(*n);
					t.addNode(*n);
					break;
				}	
				case 1:{//queen
					ChessTreeNode *n = new ChessTreeNode(*this);
					for (int k = 1; k < 8-i; k++) {
						if (i != j)
							continue;
						if (!moveQueen(name, k,i,j,i))
							if (!strikeBishop(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < 8-j; k++) {
						if (i != j)
							continue;
						if (!moveQueen(name, j,k,j,i))
							if (!strikeBishop(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < i; k++) {
						if (i != j)
							continue;
						if (!moveQueen(name, k,i,j,i))
							if (!strikeBishop(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < j; k++) {
						if (i != j)
							continue;
						if (!moveQueen(name, j,k,j,i))
							if (!strikeBishop(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					n = new ChessTreeNode(*this);
					for (int k = 1; k < 8-i; k++) {
						if (!moveQueen(name, k,i,j,i))
							if (!strikeTower(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < 8-j; k++) {
						n = new ChessTreeNode(*this);
						if (!moveQueen(name, j,k,j,i))
							if (!strikeTower(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < i; k++) {
						n = new ChessTreeNode(*this);
						if (!moveQueen(name, k,i,j,i))
							if (!strikeTower(name, k,i,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					for (int k = 1; k < j; k++) {
						n = new ChessTreeNode(*this);
						if (!moveQueen(name, j,k,j,i))
							if (!strikeTower(name, j,k,j,i))
								return false;
							else // true, cache good node
								goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					}
					if (!mode)	
						route.push_back(*n);
					t.addNode(*n);
					break;
				}
				case 0:{//king
					ChessTreeNode *n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i-1,j,i))
						if (!strikeKing(name, j-1,i-1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i,j,i))
						if (!strikeKing(name, j-1,i,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i+1,j,i))
						if (!strikeKing(name, j-1,i+1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j,i-1,j,i))
						if (!strikeKing(name, j,i-1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j,i+1,j,i))
						if (!strikeKing(name, j,i+1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i-1,j,i))
						if (!strikeKing(name, j-1,i-1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i,j,i))
						if (!strikeKing(name, j-1,i,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					n = new ChessTreeNode(*this);
					if (!moveKing(name, j-1,i+1,j,i))
						if (!strikeKing(name, j-1,i+1,j,i))
							return false;
						else // true, cache good node
							goodnodes.push_back(*n);
						t.addNode(*n);
						if (mode > 0)
							route.push_back(*n);
					if (!mode)	
						route.push_back(*n);
					t.addNode(*n);
					break;
				}		
				default:
					break;
			}
	
		}
	}
}

bool Board::movePawn(std::string& name, char r, char c)
{
	if (r == 7)
		return false;
	if (name == playername) {
		//go to free position
		if (getWhiteBoard()[r+1][c] == 7 && getBlackBoard()[r+1][c] == 7) {
			moveWhitePawn(r,c);	
			return true;
		}
		return false;
	} else if (name == blackplayername) { 
		//go to free position
		if (getBlackBoard()[r+1][c] == 7 && getWhiteBoard()[r+1][c]) { 
			moveBlackPawn(r,c);	
			return true;
		}
	}
}

bool Board::moveKnight(std::string& name, char r, char c)
{
	if (name == playername) {
		if (r+2 < 8 && c-1 < 8 && getWhiteBoard()[r+2][c-1] == 7 && getBlackBoard()[r+2][c-1] == 7) {//go to free position 
			moveWhiteKnight(r+2,c-1,r,c);	
			return true;
		} else if (r-2 < 8 && c-1 < 8 && getWhiteBoard()[r-2][c-1] == 7 && getBlackBoard()[r-2][c-1] == 7) {//go to free position 
			moveWhiteKnight(r-2,c-1,r,c);	
			return true;
		} else if (r+2 < 8 && c+1 < 8 && getWhiteBoard()[r+2][c+1] == 7 && getBlackBoard()[r+2][c+1] == 7) {//go to free position 
			moveWhiteKnight(r+2,c+1,r,c);	
			return true;
		} else if (r-2 < 8 && c+1 < 8 && getWhiteBoard()[r-2][c+1] == 7 && getBlackBoard()[r-2][c+1] == 7) {//go to free position 
			moveWhiteKnight(r-2,c+1,r,c);	
			return true;
		} else if (r+1 < 8 && c-2 < 8 && getWhiteBoard()[r+1][c-2] == 7 && getBlackBoard()[r+1][c-2] == 7) {//go to free position 
			moveWhiteKnight(r+1,c-2,r,c);	
			return true;
		} else if (r-1 < 8 && c-2 < 8 && getWhiteBoard()[r-1][c-2] == 7 && getBlackBoard()[r-1][c-2] == 7) {//go to free position 
			moveWhiteKnight(r-1,c-2,r,c);	
			return true;
		} else if (r+1 < 8 && c+2 < 8 && getWhiteBoard()[r+1][c+2] == 7 && getBlackBoard()[r+1][c+2] == 7) {//go to free position 
			moveWhiteKnight(r+1,c+2,r,c);	
			return true;
		} else if (r-1 < 8 && c+2 < 8 && getWhiteBoard()[r-1][c+2] == 7 && getBlackBoard()[r-1][c+2] == 7) {//go to free position 
			moveWhiteKnight(r-1,c+2,r,c);	
			return true;
		}
		return false;
	} else if (name == blackplayername) { 
		if (r+2 < 8 && c-1 < 8 && getWhiteBoard()[r+2][c-1] == 7 && getBlackBoard()[r+2][c-1] == 7) {//go to free position 
			moveBlackKnight(r+2,c-1,r,c);	
			return true;
		} else if (r-2 < 8 && c-1 < 8 && getWhiteBoard()[r-2][c-1] == 7 && getBlackBoard()[r-2][c-1] == 7) {//go to free position 
			moveBlackKnight(r-2,c-1,r,c);	
			return true;
		} else if (r+2 < 8 && c+1 < 8 && getWhiteBoard()[r+2][c+1] == 7 && getBlackBoard()[r+2][c+1] == 7) {//go to free position 
			moveBlackKnight(r+2,c+1,r,c);	
			return true;
		} else if (r-2 < 8 && c+1 < 8 && getWhiteBoard()[r-2][c+1] == 7 && getBlackBoard()[r-2][c+1] == 7) {//go to free position 
			moveBlackKnight(r-2,c+1,r,c);	
			return true;
		} else if (r+1 < 8 && c-2 < 8 && getWhiteBoard()[r+1][c-2] == 7 && getBlackBoard()[r+1][c-2] == 7) {//go to free position 
			moveBlackKnight(r+1,c-2,r,c);	
			return true;
		} else if (r-1 < 8 && c-2 < 8 && getWhiteBoard()[r-1][c-2] == 7 && getBlackBoard()[r-1][c-2] == 7) {//go to free position 
			moveBlackKnight(r-1,c-2,r,c);	
			return true;
		} else if (r+1 < 8 && c+2 < 8 && getWhiteBoard()[r+1][c+2] == 7 && getBlackBoard()[r+1][c+2] == 7) {//go to free position 
			moveBlackKnight(r+1,c+2,r,c);	
			return true;
		} else if (r-1 < 8 && c+2 < 8 && getWhiteBoard()[r-1][c+2] == 7 && getBlackBoard()[r-1][c+2] == 7) {//go to free position 
			moveBlackKnight(r-1,c+2,r,c);	
			return true;
		}
	}
	return false;
}

bool Board::moveTower(std::string& name, char r, char c, char oldr, char oldc)
{
	
	if (name == playername) {
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveWhiteTower(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveWhiteTower(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	} else if (name == blackplayername) {
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveBlackTower(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveBlackTower(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	}
	return false;
}

bool Board::moveBishop(std::string& name, char r, char c, char oldr, char oldc)
{
	
	if (name == playername) {
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveWhiteBishop(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveWhiteBishop(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	} else if (name == blackplayername) {
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveBlackBishop(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveBlackBishop(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	}
	return false;
}
				
bool Board::moveQueen(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) {
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveWhiteQueen(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveWhiteQueen(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	} else if (name == blackplayername) {
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveBlackQueen(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveBlackQueen(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	}
	return false;
}
				
bool Board::moveKing(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) {
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveWhiteKing(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveWhiteKing(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	} else if (name == blackplayername) {
		switch (getWhiteBoard()[r][c]) {
			case 7:
				moveBlackKing(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
		switch (getBlackBoard()[r][c]) {
			case 7:
				moveBlackKing(r,c,oldr,oldc);	
				return true;
				break;	
			default:
				return false;
				break;	
		}
	}
	return false;
}

bool Board::strikePawn(std::string& name, char r, char c)
{

	if (name == playername) { 
		//we cannot strike as we are a queen
		if (c == 7) {
			switch (getBlackBoard()[r+1][c-1]) {
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c-1])) > percentage) {
					percentage >>= 2;
					return true;			
				} else {
					return false;
				}
			}
		} else if (c == 0) {//we are a pawn on the side
			switch (getBlackBoard()[r+1][c+1]) {//go to nothing	
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c+1])) > percentage) {
					percentage >>= 2;
					return true;
				} else {
					return false;
				}
			}
		} else if (r != 7) {
			switch (getBlackBoard()[r+1][c-1]) {//we are not a queen	
			case 7:
				switch (getBlackBoard()[r+1][c+1]) {//go to nothing	
				case 7:
					return false;
				default:
					if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c+1])) > percentage) {
						percentage >>= 2;
						return true;
					} else {
						return false;
					}
				}
			default:
				if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c-1])) > percentage) {
					percentage >>= 2;
					return true;
				} else {
					return false;
				}
			}
		}
	} else if (blackplayername == name) {
		if (c == 7) {
			switch (getWhiteBoard()[r+1][c-1]) {
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c-1])) > percentage) {
					percentage >>= 2;
					return true;			
				} else {
					return false;
				}
			}
		} else if (c == 0) {//we are a pawn on the side
			switch (getWhiteBoard()[r+1][c+1]) {//go to nothing	
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c+1])) > percentage) {
					percentage >>= 2;
					return true;
				} else {
					return false;
				}
			}
		} else if (r != 7) {
			switch (getWhiteBoard()[r+1][c-1]) {//we are not a queen	
			case 7:
				switch (getWhiteBoard()[r+1][c+1]) {//go to nothing	
				case 7:
					return false;
				default:
					if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c+1])) > percentage) {
						percentage >>= 2;
						return true;
					} else {
						return false;
					}
				}
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c-1])) > percentage) {
					percentage >>= 2;
					return true;
				} else {
					return false;
				}
			}
		}
	}
	return false; 
}

bool Board::strikeKnight(std::string& name, char r, char c)
{
	if (name == playername) { 
		if (getBlackBoard()[r+2][c-1] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+2][c-1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r+2][c+1] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+2][c+1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r-2][c-1] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r-2][c-1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r-2][c+1] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r-2][c+1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r+1][c-2] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c-2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r+1][c+2] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r+1][c+2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r-1][c+2] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r-1][c+2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getBlackBoard()[r-1][c-2] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[r][c], getBlackBoard()[r-1][c-2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
	} else if (blackplayername == name) {
		if (getWhiteBoard()[r+2][c-1] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+2][c-1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r+2][c+1] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+2][c+1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r-2][c-1] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-2][c-1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r-2][c+1] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-2][c+1])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r+1][c-2] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c-2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r+1][c+2] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r+1][c+2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r-1][c+2] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c+2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
		else if (getWhiteBoard()[r-1][c-2] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c-2])) > percentage) {
				percentage >>= 2;
				return true;			
			} else {
				return false;
			}
		}
	}
	return false; 
}

bool Board::strikeTower(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) { 
		if (getBlackBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[oldr][oldc], getBlackBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	} else if (name == blackplayername) { 
		if (getWhiteBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[oldr][oldc], getWhiteBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	}
	return false;
}

bool Board::strikeBishop(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) { 
		if (getBlackBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[oldr][oldc], getBlackBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	} else if (name == blackplayername) { 
		if (getWhiteBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[oldr][oldc], getWhiteBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	}
	return false;
}

bool Board::strikeQueen(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) { 
		if (getBlackBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[oldr][oldc], getBlackBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	} else if (name == blackplayername) { 
		if (getWhiteBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[oldr][oldc], getWhiteBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	}
	return false;
}

bool Board::strikeKing(std::string& name, char r, char c, char oldr, char oldc)
{
	if (name == playername) { 
		if (getBlackBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getWhiteBoard()[oldr][oldc], getBlackBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	} else if (name == blackplayername) { 
		if (getWhiteBoard()[r][c] != 7) {
			if (static_cast<int>(strikeWith(getBlackBoard()[oldr][oldc], getWhiteBoard()[r][c])) > percentage) {
				percentage >>= 2;
				return true;		
			}
		}	
	}
	return false;
}

}//namespace chess 
}//namespace tree 
}//namespace utilai	
