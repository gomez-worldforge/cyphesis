//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _MATRIX_UTILAI_H_
#define _MATRIX_UTILAI_H_

#include<iostream>
#include<vector>

#include "Vector.hpp"

namespace utilai
{
namespace math 
{

template<class EType>
class Matrix
{
public:
	explicit Matrix(int c, int r);
	virtual ~Matrix();


public:
	Matrix<EType> operator+(const Matrix<EType>& v);			
	Matrix<EType> operator+=(const Matrix<EType>& v);			
	Matrix<EType> operator*(const Matrix<EType>& v);			
	Matrix<EType> operator*=(const Matrix<EType>& v);		

	Matrix<EType> operator+(float f);			
	Matrix<EType> operator+=(float f);			
	Matrix<EType> operator-(float f);			
	Matrix<EType> operator-=(float f);			
	Matrix<EType> operator*(float f);			
	Matrix<EType> operator*=(float f);
		
	Vector<EType> operator*(const Vector<EType>& v);			
		
	void atput(int idx, EType et);
	int getcols() { return cols; }
	int getrows() { return rows; }
	EType operator[](int index);
private:
	int cols, rows;
	std::vector<EType> vector;
};
}//namespace math
}//namespace utilai
#endif	
