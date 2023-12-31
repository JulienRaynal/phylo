#ifndef PHYLO_FITCH_H
#define PHYLO_FITCH_H

#include <algorithm>
#include "../Helpers/tree.h"
#include "../Helpers/Trunk.h"

namespace fitch {
	/**
	 * Applies the fitch algorithm to get the most parcimonious tree
	 *
	 * Complexity O(n) + O(n) = O(n)
	 *
	 * @param root A pointer to a root Node of a tree
	 */
	void etiquetteTree(Node* root);
}

#endif
