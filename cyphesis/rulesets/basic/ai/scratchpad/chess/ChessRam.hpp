//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSRAM_UTILAI_H_
#define _CHESSRAM_UTILAI_H_

/*
 * ChessRam is a byte vector system for storing chess pieces.
 * 
 * There's a fast shift for checking striking of chesspieces. 
 */

namespace utilai
{
namespace chess 
{
namespace memory 
{

typedef int ChessPieceNum;

class ChessRam 
{

public:
	class ChessPiece
	{
	public:
		ChessPiece() : _num(-1) {}
		~ChessPiece() {}

		void init(int num) { _num = num }
	private:
		ChessPieceNum _num;
	};

	class Pawn : public ChessPiece
	{
		explicit Pawn() { init(5); }
	}; 

	class Horse : public ChessPiece
	{
		explicit Horse() { init(4); }
	}; 

	class Tower : public ChessPiece
	{
		explicit Tower() { init(3); }
	}; 

	class Bishop : public ChessPiece
	{
		explicit Bishop() { init(2); }
	}; 

	class Queen : public ChessPiece
	{
		explicit Queen() { init(1); }
	}; 

	class King : public ChessPiece
	{
		explicit King() { init(0); }
	}; 

public:
	ChessRam() {  
		_chessram = new char[8][8];
		for (int index = 0; index < 8; index++) {
			_chessramrow = new char[8];
			_chessram[8][index] = _chessramrow; //row and col	
		}
		_chesspiecenumbers = new ChessPieceNum[6];		
		
		//init chess piece numbers
		_chesspiecenumbers[0] = King().get();
		_chesspiecenumbers[5] = Pawn().get();	
		_chesspiecenumbers[4] = Horse().get();	
		_chesspiecenumbers[3] = Bishop().get();	
		_chesspiecenumbers[2] = Tower().get();	
		_chesspiecenumbers[1] = Queen().get();	
	}
	~ChessRam() {
		delete [][] _chessram;
		delete [] _chesspiecenumbers;
	}

	bool strikeWith(ChessPieceNum n1, ChessPieceNum n2) {
		if (n2 >> n1 > 0)
			return true;
		else
			return false;
	}		

private:
	char *_chessramrow;
	char **_chessram;
	ChessPieceNum *_chesspiecenumbers; 
};

}//namespace memory 
}//namespace chess 
}//namespace utilai
#endif	
