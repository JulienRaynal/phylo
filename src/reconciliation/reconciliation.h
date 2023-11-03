#ifndef PHYLO_RECONCILIATION_H
#define PHYLO_RECONCILIATION_H

#include <stdio.h>
#include <vector>
#include "../Model/Tree.h"
#include "../lca/lca.h"

namespace reco {
	/**
	 * Reconciles the gene tree and the species tree to follow their evolution
	 * @param t1 A gene tree
	 * @param t2 A species tree
	 * @return Tree&
	 */
	Tree& reconcile(Tree& t1, Tree& t2);
}

#endif
