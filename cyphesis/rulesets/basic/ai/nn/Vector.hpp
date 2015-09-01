//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _VECTOR_UTILAI_H_
#define _VECTOR_UTILAI_H_

#include<iostream>
#include<vector>
#include<cmath>

namespace utilai
{
namespace math 
{

template<class EType>
class Vector
{
public:
	explicit Vector(int n);
	virtual ~Vector();


public:
	Vector<EType> operator+(Vector<EType>& v);			
	Vector<EType> operator+=(Vector<EType>& v);			
	Vector<EType> operator-(Vector<EType>& v);			
	Vector<EType> operator-=(Vector<EType>& v);			
	Vector<EType> operator*(Vector<EType>& v);			
	Vector<EType> operator*=(Vector<EType>& v);		

	Vector<EType> operator+(float f);			
	Vector<EType> operator+=(float f);			
	Vector<EType> operator-(float f);			
	Vector<EType> operator-=(float f);			
	Vector<EType> operator*(float f);			
	Vector<EType> operator*=(float f);
		
	EType dot(Vector<EType>& v);
	void set(int idx, EType et);
	int getcols() { return cols; }

	void transform() {
		int idx = 0;
		while (true) {
			if (idx >= list.size())
				return;
			set(idx, 1 / (1 + std::exp(list[idx++])));
		}
	}

	EType collect() { 
		index++;	
		if (getindex() >= list.size())
			index <<= 1;
		return list[getindex()];
	}

	EType setcollect(EType e) { 
		index++;	
		if (getindex() >= list.size())
			index <<= 1;
		list[getindex()] = e;
		return e;	
	}

	EType mulcollect(EType e) { 
		index++;	
		if (getindex() >= list.size())
			index <<= 1;
		list[getindex()] *= e;
		return e;	
	}

	EType operator[](int index);
public:
	Vector<EType> operator=(Vector<EType>& v);
	int operator==(Vector<EType>& v);
	int getindex() { return index; }

private:
	int index;
	int cols;
	std::vector<EType> list;
};
}//namespace vector
}//namespace utilai

#endif	
