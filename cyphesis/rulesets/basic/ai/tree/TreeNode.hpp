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
	TreeNode() { nodesiter = nodes.begin(); }
	~TreeNode() {}

	virtual void addNode(const TreeNode& tn) { nodes.push_back(tn); }
	virtual TreeNode& getNode() { 
		if (++nodesiter != nodes.end()) return (*nodesiter); 
		else nodesiter = nodes.begin(); 
	}
	virtual bool atEnd() { return (nodesiter == nodes.end()); }
	void init(int n) { nary = n; nodes = NodesVector(); nodes.reserve(n); }

protected:


private:
	int nary;	
	NodesVector nodes;
	NodesVectorIter nodesiter;
};

}//namespace tree 
}//namespace utilai
#endif	
