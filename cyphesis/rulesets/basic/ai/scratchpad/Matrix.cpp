//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "Matrix.hpp"

namespace utilai
{
namespace math 
{

template<class EType>
Matrix<EType>::Matrix(int c, int r)
	: cols(c), rows(r) 
{
	vector.reserve(c*r);
}

template<class EType>
Matrix<EType>::~Matrix()
{}
	
template<class EType>
void Matrix<EType>::atput(int idx, EType et)
{
	vector[idx] = et;
}	

template<class EType>
Matrix<EType> Matrix<EType>::operator+(const Matrix<EType>& v)
{
	Matrix<EType> rm(cols,rows);
	int idx;
	while (true) {
		if (idx >= vector.size())
			return rm;
		rm.atput(idx,const_cast<Matrix<EType> &>(v)[idx] + vector[idx++]);
	}
	return rm;
}
 
template<class EType>
Matrix<EType> Matrix<EType>::operator+=(const Matrix<EType>& v)			
{
	int idx;
	while (true) {
		if (idx >= vector.size())
			return *this;
		atput(idx,const_cast<Matrix<EType> &>(v)[idx] + vector[idx++]);
	}
	return *this;
}

template<class EType>
Matrix<EType> Matrix<EType>::operator*(const Matrix<EType>& v)
{
	Matrix<EType> rm(cols,rows);
	int idx;
	while (true) {
		if (idx >= vector.size())
			return rm;
		rm.atput(idx,const_cast<Matrix<EType> &>(v)[idx] * vector[idx++]);
	}
	return rm;
}	

template<class EType>
Matrix<EType> Matrix<EType>::operator*=(const Matrix<EType>& v)
{
	int idx;
	while (true) {
		if (idx >= vector.size())
			return *this;
		atput(idx, const_cast<Matrix<EType> &>(v)[idx] * vector[idx++]);
	}
	return *this;
}

template<class EType>
EType Matrix<EType>::operator[](int index)
{
	return vector[index];
}

template<class EType>
Matrix<EType> Matrix<EType>::operator*=(float f)
{
	int idx;
	while (true) {
		if (idx >= vector.size())
			return *this;
		atput(idx, vector[idx++] * f);
	}
}

template<class EType>
Matrix<EType> Matrix<EType>::operator*(float f)
{
	Matrix<EType> rm(cols,rows);
	int idx;
	while (true) {
		if (idx >= vector.size())
			return rm;
		rm.atput(idx, vector[idx] * f);
	}
}

template<class EType>
Matrix<EType> Matrix<EType>::operator+(float f)
{
	Matrix<EType> rm(cols,rows);
	int idx;
	while (true) {
		if (idx >= vector.size())
			return rm;
		const_cast<Matrix<EType> &>(rm).atput(idx, vector[idx] + f);
	}
}

template<class EType>
Matrix<EType> Matrix<EType>::operator+=(float f)
{
	int idx;
	while (true) {
		if (idx >= vector.size())
			return *this;
		atput(idx, vector[idx] + f);
	}
}

template<class EType>
Matrix<EType> Matrix<EType>::operator-(float f)
{
	Matrix<EType> rm(cols,rows);
	int idx;
	while (true) {
		if (idx >= vector.size())
			return rm;
		rm.atput(idx, vector[idx] - f);
	}
}

template<class EType>
Matrix<EType> Matrix<EType>::operator-=(float f)
{
	int idx;
	while (true) {
		if (idx >= vector.size())
			return *this;
		atput(idx, vector[idx] - f);
	}
}

template<class EType>
Vector<EType> Matrix<EType>::operator*(const Vector<EType> & v)
{
	Vector<EType> rv(cols);
	int i,j, sum;
	while (true) {
		if (i >= rows) 
			return rv;
		while (true) {
			sum = vector[j+i*cols] * const_cast<Vector<EType> &>(v)[j];
			j++;
		}
		rv.atput(i, sum);
		j = 0;	
		i++;
	}
}

template class Matrix<float>;
template class Matrix<double>;
}//namespace math
}//namespace utilai	
