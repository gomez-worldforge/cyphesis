//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "Pair.hpp"
#include "Vector.hpp"

namespace utilai
{
namespace nn 
{

template<class First, class Second> 
Pair<First, Second>::Pair(First f, Second s)
 : _second(s), _first(f)
{}

template<class First, class Second> 
Pair<First, Second>::~Pair()
{}

template class Pair<math::Vector<float>,  math::Vector<float> >;
}//namespace nn 
}//namespace utilai	
