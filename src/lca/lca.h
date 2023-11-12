#ifndef PHYLO_LCA_H
#define PHYLO_LCA_H

#include "../Objects/Node.h"

namespace lca {
	/**
	 * Find the lowest common ancestor in a tree of two given nodes
	 * Returns the Node* corresponding to the Last Common Ancestor
	 *
	 * @param v Pointer to a node
	 * @param w Pointer to anoter node
	 *
	 * @return Node*
	 */
	Node* findLowestCommonAncestor(Node* v, Node* w);
}


#endif
