#ifndef PHYLO_FITCH_H
#define PHYLO_FITCH_H

#include <algorithm>
#include "../Helpers/Tree.h"

namespace fitch {
	/**
	 * Applies the fitch algorithm to get the most parcimonious tree
	 * @param root A pointer to a root Node of a tree
	 */
	void etiquetteTree(Node* root);
}

#endif
