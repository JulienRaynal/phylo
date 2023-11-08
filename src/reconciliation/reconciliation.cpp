#include "reconciliation.h"

using namespace std;

namespace reco {
	Tree& reconcile(Tree& t1, Tree& t2) {
		// Initialisation
		Tree t;
		vector<Node*> v;
		t1.getLeafNodes(t1.getRoot(), v);
		for (Node* n : v) {
			cout << n->getName() << endl;
		}
		return t1;
	}
}
