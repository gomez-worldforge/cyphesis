//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _TREE_UTILAI_H_
#define _TREE_UTILAI_H_

#include "TreeNode.hpp"
/*
 */

namespace utilai
{
namespace tree 
{

template <class N>
class Tree : public N 
{
public:
	virtual int depth_first_search() = 0;
	virtual int breath_first_search() = 0;

private:
	
};

}//namespace tree 
}//namespace utilai
#endif	
