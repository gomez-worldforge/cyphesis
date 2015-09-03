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
class ChessTreeNode;

template <class N>
class Tree : public N 
{
protected:
//AAARGH FIXME	virtual bool breadthFirstSearch(ChessTreeNode& node) = 0;

private:
	
};

}//namespace tree 
}//namespace utilai
#endif	
