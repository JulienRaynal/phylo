#include "fitch.h"

using namespace std;
namespace fitch {
	/**
	 * A function that hold the final state of a gene assignement logic
	 *
	 * @param parent_node A pointer to the parent node
	 * @param child_node A pointer to the child node of the first pointer
	 */
	void fitchAssignState(Node* parent_node, Node* child_node) {
		set<string> parent_states = parent_node->getStates();
		// If the current node is the root node
		if (!parent_node->getParentNode()) {
			set<string>::iterator state_iterator = parent_states.begin();
			set<string> first_state = {*state_iterator};
			parent_node->setStates(first_state);
		// The current Node is not the root node
		} else if (child_node->getLeftChild() || child_node->getRightChild()){
			set<string> child_states = child_node->getStates();
			// Get the intersection of the two node states
			set<string> intersect;
			set_intersection(parent_states.begin(), parent_states.end(),
					child_states.begin(), child_states.end(),
					inserter(intersect, intersect.begin()));
			// If there's an existing intersection
			if (intersect.size() > 0) {
				//cout << "INTERSECTION " << parent_node->getName() << " : " << child_node->getName() << endl;
				child_node->setStates(intersect);

			} else {
				set<string>::iterator parent_state_iterator = parent_states.begin();
				set<string> first_parent_state = {*parent_state_iterator};
				child_node->setStates(first_parent_state);
			}

		}
	}

	/**
	 * A recursive algorithm to assign the etiquettes to all child starting from a root node
	 *
	 * @param a pointer to an initial node
	 */
	void fitchDescendTree(Node* node) {
		if(!node || (!node->getLeftChild() && !node->getRightChild())) {
			return;
		}

		if (node->getLeftChild()) {
			Node* child = node->getLeftChild();
			fitchAssignState(node, child);		
			fitchDescendTree(child);
		}

		if (node->getRightChild()) {
			Node* child = node->getRightChild();
			fitchAssignState(node, child);
			fitchDescendTree(child);
		}
	}

	/**
	 * Implementation of the fitch algorithm for a parcimonic assignment of gene states in a tree
	 *
	 * @param t A tree object
	 */
	Tree& etiquetteTree(Tree& t) {
		// ===== Ascending phase =====
		// TODO: do a loop getting the parent at max_depth() - i for each leaf and assign with this
		vector<Node*> v;
		t.getLeafNodes(t.getRoot(), v); // Gets all the leaf nodes and put it in the v vector
		for (Node* n : v) { // For each leaf node we go up to the root
			Node* current_node = n;
			Node* next_node = n->getParentNode();
			while(next_node != nullptr) { // While we haven't reached the root we assign to the parent node the current state
				if (next_node != nullptr) { // If we are not at the root
					set<string> current_node_states = current_node->getStates(); // Saves the current node state
					set<string> next_node_states = next_node->getStates();
					set<string> intersect;
					// Get the intersection of the child node and the parent node
					set_intersection(current_node_states.begin(), current_node_states.end(),
								next_node_states.begin(), next_node_states.end(),
								inserter(intersect, intersect.begin()));
					// If some value of the current node and the parent node states correspond
					if (intersect.size() > 0) {
						next_node->setStates(intersect);
						cout << "INTERSECT " << current_node->getName() << " --> " << next_node->getName();
						for (string s: intersect) {
							cout << "\t" << s << endl;
						}
					// Else the two sets are fused together
					} else {
						set<string> union_set;
						set_union(current_node_states.begin(), current_node_states.end(),
								next_node_states.begin(), next_node_states.end(),
								inserter(union_set, union_set.begin()));
						next_node->setStates(union_set);
						/*for (string s: union_set) {
							cout << "\t" << s << endl;
						}*/
					}
				}
				current_node = current_node->getParentNode();
				next_node = current_node->getParentNode();
			}
		}
		
		// ===== Descending phase ======
		fitchDescendTree(t.getRoot());
		return t;
	};
}
