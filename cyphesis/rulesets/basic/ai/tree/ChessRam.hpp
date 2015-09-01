//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSRAM_UTILAI_H_
#define _CHESSRAM_UTILAI_H_

/*
 * ChessRam is a byte vector system for storing chess pieces.
 * 
 * There's a fast shift for checking striking of chesspieces. 
 */

#include <map>
 
namespace utilai
{
namespace tree 
{
namespace chess 
{
typedef char ChessPieceNum;

class ChessRam 
{

public:
	class ChessPiece
	{
	public:
		ChessPiece() : _num(-1) {}
		~ChessPiece() {}

		void init(int num) { _num = num; }
		ChessPieceNum get() { return _num; }
	private:
		ChessPieceNum _num;
	};

	class Pawn : public ChessPiece
	{
	public:
		explicit Pawn() { init(5); }
	}; 

	class Knight : public ChessPiece
	{
	public:
		explicit Knight() { init(4); }
	}; 

	class Tower : public ChessPiece
	{
	public:
		explicit Tower() { init(3); }
	}; 

	class Bishop : public ChessPiece
	{
	public:
		explicit Bishop() { init(2); }
	}; 

	class Queen : public ChessPiece
	{
	public:
		explicit Queen() { init(1); }
	}; 

	class King : public ChessPiece
	{
	public:
		explicit King() { init(0); }
	}; 

	class Nothing
	{
	public:
		explicit Nothing() { _num = 7; }
		ChessPieceNum get() { return _num; }
	private:
		int _num;
	}; 

public:
	ChessRam() {  
		//_chessram = new char[8][8];
				
		//init chess piece numbers
		//NOTE _chesspiecenumbers[7] = Nothing();
		_chesspiecenumbers[0] = King();
		_chesspiecenumbers[5] = Pawn();	
		_chesspiecenumbers[4] = Knight();	
		_chesspiecenumbers[3] = Bishop();	
		_chesspiecenumbers[2] = Tower();	
		_chesspiecenumbers[1] = Queen();	
	}
	~ChessRam() {
	}

	bool strikeWith(ChessPieceNum striker, ChessPieceNum n) {
		//NOTE : the higher striker is and the lower n,
		//you make a move which is extremely good (more entropy.)
		return n >> striker;
	}		

private:
	std::map<ChessPieceNum, ChessPiece> _chesspiecenumbers; 
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
