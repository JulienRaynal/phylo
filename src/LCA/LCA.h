#ifndef PHYLO_LCA_H
#define PHYLO_LCA_H

#include "../Model/Node.h"

namespace LCA {
	/** Find the lowest common ancestor in a tree of two given nodes
	 * @param v Pointer to a node
	 * @param w Pointer to anoter node
	 * @return Node*
	 */
	Node* findLowestCommonAncestor(Node* v, Node* w);
}


#endif
