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

//make a move based on row and column
void Board::makeMove(std::string& name, const int& row, 
			const int& col, const int& oldrow, const int& oldcol,
			ChessTreeNode& t) {
	if (playername == name) {
		moveWhiteChessPiece(row,col,oldrow,oldcol);
	} else if (blackplayername == name) {
		moveBlackChessPiece(row,col,oldrow,oldcol);
	}
}

//let the AI move based on a treenode
//pass-by-reference on the position
bool Board::searchMove(ChessTreeNodes& l, std::string& name, ChessTreeNode& t, int& row, int& col,
			int& oldrow, int& oldcol) {
	if (playername == name) {
		move(name, t);
		
		if (goodnodes.empty()) {//we did not strike a chess piece	
			if (route.empty())
				//unless nothing can move anymore
				//return to tree
				return false;
			else {
				//route is not empty so we made a single move
				//we did not strike something
				//FIXME search for a better thing than striking
				//further on in the tree
				for (ChessTreeNodesIter vi = route.begin();
					vi != route.end();
					vi++) {
					if (!legalmove(playername, (*vi),row,col,oldrow,oldcol))
						continue;//FIXME return false; //continue
					else {
						//moves can happen here
						//moveWhiteChessPiece(row,col,oldrow,oldcol);
						//but the route (breadth search)
						//is  retrieved here
						l = route;
						percentage = 1;
						return true;		
					}	
				}
				percentage = 1;
				route.clear();
				
				return false;
			}
		} else {
			//we stroke a chess piece so we do that move
			//NOTE 03 sept 2015 :
			//the last goodnode is best as it beats higher
			//percentages
			if (!legalmove(playername, goodnodes[goodnodes.size()-1],row,col,oldrow,oldcol)) {
				//FIXME better algorithm
				goodnodes.clear();
				return false;
			} else {
				//we do not move here
				//moveWhiteChessPiece(row,col,oldrow,oldcol);
				//but return the goodnodes
				l = goodnodes;
				goodnodes.clear();
				percentage = 1;
				return true;		
			}
			percentage = 1;
		}
	} else if (blackplayername == name) {
		move(name, t);
		
		if (goodnodes.empty()) {//we did not strike a chess piece	
			if (route.empty())
				return false;//nothing can move anymore
						//return to tree
			else {
				for (ChessTreeNodesIter vi = route.begin();
					vi != route.end();
					vi++) {
					if (!legalmove(playername, (*vi),row,col,oldrow,oldcol))
						return false;//continue
					else {
						//moves can happen here
						//moveBlackChessPiece(row,col,oldrow,oldcol);
						//but the route (breadth search)
						//is  retrieved here
						l = route;
						percentage = 1;
						return true;		
					}	
				}
				route.clear();
				return true;		
			}
		} else {//we stroke a chess piece
				//int row = 0, col = 0, oldrow = 0, oldcol = 0;
				if (!legalmove(blackplayername, goodnodes[goodnodes.size()-1],row,col,oldrow,oldcol)) {
					return false;
				} else {
					//we do not move here	
					//moveBlackChessPiece(row,col,oldrow,oldcol);
					//but return the goodnodes
					l = goodnodes;
					percentage = 1;
					return true;		
				}
			}
		percentage = 1;
		//}
	} 

	return false;
}

bool Board::legalmove(std::string& name, ChessTreeNode& t, int& row, int& col, int& oldrow, int& oldcol) {
	
	if (name == playername) {
		int i = 0, j = 0;

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if ((t.get().getWhiteBoardXY(i,j)) >> (getWhiteBoardXY(i,j)) == 0) 
					continue;
				else {
					if ((getWhiteBoardXY(i,j)) == 7) { 
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
				if ((t.get().getWhiteBoardXY(i,j)) >> (getWhiteBoardXY(i,j)) == 0) 
					continue;
				else {
					if ((getWhiteBoardXY(i,j)) == 7) { 
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
	//}
	} else if (blackplayername == name) {
		int i = 0, j = 0;

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if ((t.get().getBlackBoardXY(i,j)) >> (getBlackBoardXY(i,j)) == 0) 
					continue;
				else {
					if ((getBlackBoardXY(i,j)) == 7) { 
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
				if ((t.get().getBlackBoardXY(i,j)) >> (getBlackBoardXY(i,j)) == 0) 
					continue;
				else {
					if ((getBlackBoardXY(i,j)) == 7) { 
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
	 

	}
	return false;
}

bool Board::move(std::string& name, ChessTreeNode& t)
{
	if (name == playername) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			//choose white chess pieces
			switch(getWhiteBoard()[j][i]) {
				case 5:{//pawn
					if (strikePawn(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						route.push_back(*n);
						t.addNode(*n);
					} if (movePawn(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						route.push_back(*n);
						t.addNode(*n);
					}
					break;
				}
				case 4:{//knight	
					if (strikeKnight(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						route.push_back(*n);
						t.addNode(*n);
					} if (moveKnight(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						route.push_back(*n);
						t.addNode(*n);
					}
					
					break;
				}	
				case 3:{//tower			
					//move down 
					for (int k = i+1; k < 8; k++) {

						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}

					}
					//move right 
					for (int k = j+1; k < 8; k++) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move left	
					for (int k = i-1; k >= 0; k--) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move up	
					for (int k = j-1; k >= 0; k--) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//if (!mode)	
					//	route.push_back(*n);
					break;
				}	
				case 2:{//bishop
					//move bottom right	
					for (int k = j+1; k < 8; k++) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move up right
					for (int k = j-1; k >= 0; k--) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move left bottom
					for (int k = j+1; k < 8; k++) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;
	
							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
								
							}
						}
					}
					//move left up
					for (int k = j-1; k >= 0; k--) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//if (!mode)
					//	route.push_back(*n);
					//t.addNode(*n);
					break;
				}	
				case 1:{//queen
					//move right	
					for (int k = i+1; k < 8; k++) {

						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}

					}
					//move down 
					for (int k = j+1; k < 8; k++) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move left	
					for (int k = i-1; k >= 0; k--) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move up	
					for (int k = j-1; k >= 0; k--) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move bottom right	
					for (int k = j+1; k < 8; k++) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move up right
					for (int k = j-1; k >= 0; k--) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move left bottom
					for (int k = j+1; k < 8; k++) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;
	
							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
								
							}
						}
					}
					//move left up
					for (int k = j-1; k >= 0; k--) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//if (!mode)	
					//	route.push_back(*n);
					//if (!mode)
					//	route.push_back(*n);
					break;
				}
				case 0:{//king
					if (strikeKing(name, j-1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j-1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j-1,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j+1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j+1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j+1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j+1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					break;
				}	
				case 7:{
					//empty position
					break;
				}	
				default:
					break;
			}
	
		}
	}
	} else if (name == blackplayername) {

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			switch(getBlackBoard()[j][i]) {
				case 5:{//pawn
					if (strikePawn(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						route.push_back(*n);
						t.addNode(*n);
					} if (movePawn(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						route.push_back(*n);
						t.addNode(*n);
					}
					break;
				}
				case 4:{//knight	
					if (strikeKnight(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						route.push_back(*n);
						t.addNode(*n);
					} if (moveKnight(name, j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						route.push_back(*n);
						t.addNode(*n);
					}
					
					break;
				}	
				case 3:{//tower				
					//move down 
					for (int k = i+1; k < 8; k++) {

						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}

					}
					//move right 
					for (int k = j+1; k < 8; k++) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move left	
					for (int k = i-1; k >= 0; k--) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move up	
					for (int k = j-1; k >= 0; k--) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveTower(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//if (!mode)	
					//	route.push_back(*n);
					//if (!mode)	
					//	route.push_back(*n);
					break;
				}	
				case 2:{//bishop
					//move bottom right	
					for (int k = j+1; k < 8; k++) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move up right
					for (int k = j-1; k >= 0; k--) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move left bottom
					for (int k = j+1; k < 8; k++) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;
	
							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
								
							}
						}
					}
					//move left up
					for (int k = j-1; k >= 0; k--) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(l,k) != 7 || getBlackBoardXY(l,k) != 7)
								break;

							if (strikeBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveBishop(name, l,k,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//if (!mode)
					//	route.push_back(*n);
					//t.addNode(*n);
					break;
				}	
				case 1:{//queen
					//move right	
					for (int k = i+1; k < 8; k++) {

						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}

					}
					//move down 
					for (int k = j+1; k < 8; k++) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(j,k) != 7)
							break;

						if (strikeQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move left	
					for (int k = i-1; k >= 0; k--) {
						if (getWhiteBoardXY(j,k) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, j,k,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move up	
					for (int k = j-1; k >= 0; k--) {
						if (getWhiteBoardXY(k,i) != 7 || getBlackBoardXY(k,i) != 7)
							break;

						if (strikeQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							goodnodes.push_back(*n);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
						} if (moveQueen(name, k,i,j,i)) {
							ChessTreeNode *n = new ChessTreeNode(*this);
							if (mode > 0)
								route.push_back(*n);
							t.addNode(*n);
							
						}
					}
					//move bottom right	
					for (int k = j+1; k < 8; k++) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move up right
					for (int k = j-1; k >= 0; k--) {
						for (int l = i+1; l < 8; l++) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//move left bottom
					for (int k = j+1; k < 8; k++) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;
	
							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
								
							}
						}
					}
					//move left up
					for (int k = j-1; k >= 0; k--) {
						for (int l = i-1; l >= 0; l--) {
							if (k != l)
								continue;
							if (getWhiteBoardXY(k,l) != 7 || getBlackBoardXY(k,l) != 7)
								break;

							if (strikeQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								goodnodes.push_back(*n);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							} if (moveQueen(name, k,l,j,i)) {
								ChessTreeNode *n = new ChessTreeNode(*this);
								if (mode > 0)
									route.push_back(*n);
								t.addNode(*n);
							
							}
						}
					}
					//if (!mode)
					//	route.push_back(*n);
					break;
				}
				case 0:{//king
					if (strikeKing(name, j-1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j-1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j-1,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j-1,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j,i+1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j+1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j+1,i-1,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (strikeKing(name, j+1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					if (moveKing(name, j+1,i,j,i)) {
						ChessTreeNode *n = new ChessTreeNode(*this);
						goodnodes.push_back(*n);
						if (mode > 0)
							route.push_back(*n);
						t.addNode(*n);
					}
					break;
				}	
				case 7:{
					//empty position
					break;
				}	
				default:
					break;
			}
			//choose black chess pieces	
		}
	}
	}
}

bool Board::movePawn(std::string& name, char r, char c)
{
	if (name == playername) {
		//pawn will now becomes a queen if it is not blocked
		if (r == 6 && getWhiteBoard()[r+1][c] == 7) {
			moveWhitePawn(r,c);
			getWhiteBoard()[r+1][c] = 1;//set to queen	
			return true;
		}
			
		//go to free position
		if (getWhiteBoard()[r+1][c] == 7 && getBlackBoard()[r+1][c] == 7) {
			moveWhitePawn(r,c);	
			return true;
		}
		return false;
	} else if (name == blackplayername) {
		//will we move to the last row (upper row for black) 
		if (r == 1 && getWhiteBoard()[r-1][c] == 7) {
			moveBlackPawn(r,c);
			getBlackBoard()[r-1][c] = 1;//set to queen	
			return true;
		}
			
		//go to free position
		if (getBlackBoard()[r-1][c] == 7 && getWhiteBoard()[r-1][c] == 7) { 
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
			switch (getWhiteBoard()[r-1][c-1]) {
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c-1])) > percentage) {
					percentage >>= 2;
					return true;			
				} else {
					return false;
				}
			}
		} else if (c == 0) {//we are a pawn on the side
			switch (getWhiteBoard()[r-1][c+1]) {//go to nothing	
			case 7:
				return false;
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c+1])) > percentage) {
					percentage >>= 2;
					return true;
				} else {
					return false;
				}
			}
		} else if (r != 0) {
			switch (getWhiteBoard()[r-1][c-1]) {//we are not a queen	
			case 7:
				switch (getWhiteBoard()[r-1][c+1]) {//go to free position 
				case 7:
					return false;
				default:
					if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c+1])) > percentage) {
						percentage >>= 2;
						return true;
					} else {
						return false;
					}
				}
			default:
				if (static_cast<int>(strikeWith(getBlackBoard()[r][c], getWhiteBoard()[r-1][c-1])) > percentage) {
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
