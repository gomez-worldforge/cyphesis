//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "Vector.hpp"

namespace utilai
{
namespace math 
{

template<class EType>
Vector<EType>::Vector(int n)
	: cols(n), list() { list.reserve(n); }

template<class EType>
Vector<EType>::~Vector()
{}
	
template<class EType>
void Vector<EType>::set(int idx, EType et)
{
	list[idx] = et;
}	

template<class EType>
Vector<EType> Vector<EType>::operator+(Vector<EType>& v)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		rv.set(idx, v[idx] + list[idx++]);
	}
	return rv;
}
 
template<class EType>
Vector<EType> Vector<EType>::operator+=(Vector<EType>& v)			
{
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		list[idx] = v[idx] + list[idx++];
	}
	return *this;
}

template<class EType>
Vector<EType> Vector<EType>::operator-(Vector<EType>& v)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		rv.set(idx, v[idx] - list[idx++]);
	}
	return rv;
}
 
template<class EType>
Vector<EType> Vector<EType>::operator-=(Vector<EType>& v)			
{
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		list[idx] = v[idx] - list[idx++];
	}
	return *this;
}

template<class EType>
Vector<EType> Vector<EType>::operator*(Vector<EType>& v)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		rv.set(idx, v[idx] * list[idx++]);
	}
	return rv;
}	

template<class EType>
Vector<EType> Vector<EType>::operator*=(Vector<EType>& v)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return v;
		list[idx] = v[idx] * list[idx++];
	}
	return *this;
}

template<class EType>
EType Vector<EType>::dot(Vector<EType>& v)
{
	int idx = 0, sum = 0;
	while (true) {
		if (idx >= list.size())
			return sum;
		sum += v[idx] * list[idx++];
	}
	return sum;

}

template<class EType>
EType Vector<EType>::operator[](int idx)
{
	return list[idx];
}

template<class EType>
Vector<EType> Vector<EType>::operator=(Vector<EType>& v)
{

	if (*this == v)
		return *this;	

	this->cols = v.cols;
	this->list = v.list;

	return *this;
}

template<class EType>
int Vector<EType>::operator==(Vector<EType>& v)
{

	if (*this == v)
		return 1;	

	//FIXME
	if (this->cols == v.cols 
		&& 
		this->list == v.list)
		return 1;

	return 0;
}

template<class EType>
Vector<EType> Vector<EType>::operator*=(float f)
{
	int idx = 0;
	while (true) {
		if (idx >= list.size()) 
			return *this;
		list[idx] = (*this)[idx++] * f;
	}
}

template<class EType>
Vector<EType> Vector<EType>::operator*(float f)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return rv;
		set(idx, (*this)[idx++] * f);
	}
}

template<class EType>
Vector<EType> Vector<EType>::operator+(float f)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return rv;
		set(idx, (*this)[idx] + f);
	}
}

template<class EType>
Vector<EType> Vector<EType>::operator+=(float f)
{
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return *this;
		list[idx] = (*this)[idx++] + f;
	}
	return *this;
}

template<class EType>
Vector<EType> Vector<EType>::operator-(float f)
{
	Vector<EType> rv(cols);
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return rv;
		set(idx, (*this)[idx++] - f);
	}
	return rv;
}

template<class EType>
Vector<EType> Vector<EType>::operator-=(float f)
{
	int idx = 0;
	while (true) {
		if (idx >= list.size())
			return *this;
		list[idx] = (*this)[idx++] - f;
	}
}

template class Vector<float>;
template class Vector<double>;
}//namespace vector
}//namespace utilai	
