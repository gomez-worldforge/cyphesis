//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _TREENODE_UTILAI_H_
#define _TREENODE_UTILAI_H_

#include<vector>

/*
 */

namespace utilai
{
namespace tree 
{
class TreeNode;
typedef std::vector<TreeNode> NodesVector;
typedef std::vector<TreeNode>::iterator NodesVectorIter;

class TreeNode 
{
public:
	TreeNode() {}
	~TreeNode() {}

	void addNode(const TreeNode& tn) { nodes.push_back(tn); }
	void init(int n) { nary = n; nodes = NodesVector(); nodes.reserve(n); }
protected:


private:
	int nary;	
	NodesVector nodes;
};

}//namespace tree 
}//namespace utilai
#endif	
