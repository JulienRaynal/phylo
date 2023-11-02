#ifndef PHYLO_FITCH_H
#define PHYLO_FITCH_H

#include <algorithm>
#include "../Model/Tree.h"

namespace fitch {
	void fitchDescendTree(Tree& t);
	Tree& etiquetteTree(Tree& t);
}

#endif
