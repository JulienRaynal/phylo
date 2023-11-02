#include "lca.h"

namespace lca {
	Node* findLowestCommonAncestor(Node* v, Node* w) {
		int depth_vv = v->getDepth();
		int depth_ww = w->getDepth();

		Node* vv = v;
		Node* ww = w;

		// First we try to get the nodes to the same depth
		while (depth_vv != depth_ww) {
			if (depth_vv > depth_ww) {
				vv = vv->getParentNode();
				depth_vv--;
			} else {
				ww = ww->getParentNode();
				depth_ww--;
			}
		}

		// Then we look for the common ancestor by going up the nodes of the tree until they match
		while (vv != ww) {
			vv = vv->getParentNode();
			ww = ww->getParentNode();
		}
		return vv;
	}
}
