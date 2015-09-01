//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "Tree.hpp"
#include "ChessTreeNode.hpp"

namespace utilai
{
namespace tree 
{


template class Tree<TreeNode>;
template class Tree<chess::ChessTreeNode>;
}//namespace tree 
}//namespace utilai	
