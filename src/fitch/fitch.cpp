#include "fitch.h"

using namespace std;
namespace fitch {
	/** Gets the first element in a set of string
	 *
	 * @param states A set of strings
	 * @return set<string>
	 */
	set<string> _getFirstState(set<string>& states) {
		set<string>::iterator state_iterator = states.begin();
		set<string> first_state = {*state_iterator};
		return first_state;
	}

	/**
	 * A function that manages all the logic of the node gene state assignement.
	 * Ascending phase:
	 * 	Will assign to the receiver node the value of the giver node by either:
	 * 		- doing an intersect if they have any value in common
	 * 		- doing an union if there's no value in common between the giver and the receiver states
	 * 	If the giver has no receiver than it's the root node and it assigns to itself the first state in his state list
	 *
	 * Descending phase:
	 * 	Will assign to the receiver the node value of the giver node by either:
	 * 		- doing an intersect if they have on value in common
	 * 		- selecting the first state of the receiver if no intersection exists (mutation)
	 *
	 * @param giver A node pointer to the giver of the gene state
	 * @param receiver A node pointer to the receiver of the gene state
	 * @param descending A boolean to know if it's the descending (slightly alter the algorithm to avoid unions)
	 */
	void _fitchAssignState(Node* giver, Node* receiver, bool descending = false) {
		//TODO: This is the way it is described but it makes on more call to the parent node
		/*
		if (!receiver) {
			return;
		}
		if (!giver->getParentNode()) {
			giver->setStates(_getFirstState(giver->getStates()));
		*/


		// if the giver is null then the receiver is the parent root in the descending phase
		// see: _fitchDescendTree()
		if (!receiver) {
			giver->setStates(_getFirstState(giver->getStates()));
		// Else we check that the receiver node is not a leaf node (their state shouldn't be changed)
		// Leaf node do not possess a child left or right
		} else if (receiver->getLeftChild() || receiver->getRightChild()) {
			set<string> giver_states = giver->getStates();
			set<string> receiver_states = receiver->getStates();
			// Get the intersection of the two nodes
			set<string> intersect;
			set_intersection(giver_states.begin(), giver_states.end(),
					receiver_states.begin(), receiver_states.end(),
					inserter(intersect, intersect.begin()));
			// If there's an existing intersection
			if (intersect.size() > 0) {
				receiver->setStates(intersect);
				cout << "INTERSECTION: " << giver->getName() << " --> " << receiver->getName() << endl; 
				for (string s: intersect) {
					cout << "\t" << s << endl;
				}
			} else {
				// If the algorithm is descending the receiver gets assigned one of his states
				// Else if the algorithm is ascending the union between the giver and receiver is assigned to the receiver
				if (descending) {
					receiver->setStates(_getFirstState(receiver_states));
				} else {
					set<string> union_set;
					set_union(giver_states.begin(), giver_states.end(),
							receiver_states.begin(), receiver_states.end(),
							inserter(union_set, union_set.begin()));
					//set<string>::iterator giver_states_iterator = giver_states.begin();
					//set<string> first_giver_state = {*giver_states_iterator};
					//receiver->setStates(first_giver_state);
					receiver->setStates(union_set);
					cout << "UNION: " << giver->getName() << " --> " << receiver->getName() << endl; 
					for (string s: union_set) {
						cout << "\t" << s << endl;
					}
				}
			}

		}
	}

	/**
	 * A recursive algorithm to assign the states of gene to all child starting from a root node in a descending manner
	 *
	 * @param node A pointer to an initial node
	 */
	void _fitchDescendTree(Node* node) {
		cout << "DESCENDING" << endl;
		if(!node || (!node->getLeftChild() && !node->getRightChild())) {
			return;
		}

		if (node->getLeftChild()) {
			Node* child = node->getLeftChild();
			_fitchAssignState(node, child, true);		
			_fitchDescendTree(child);
		}

		if (node->getRightChild()) {
			Node* child = node->getRightChild();
			_fitchAssignState(node, child, true);
			_fitchDescendTree(child);
		}
	}

	/**
	 * A recursive algorihthm to assign states of gene to all parent from the leaf nodes in an ascending manner
	 *
	 * @param leafs A list of leaves from the tree
	 */
	void _fitchAscendTree(set<Node*>& leafs) {
		set<Node*> current_nodes = leafs; // create new list to put the parents of the nodes in it
		leafs.clear(); // free the list to add the parents in it
		while (*current_nodes.begin() != NULL) { // When the node is null then we reached the top
			for (Node* n: current_nodes) {
				Node* parent = n->getParentNode();
				_fitchAssignState(n, parent);
				// Check if the leaf is already in the set to not create doubles
				const bool is_in = leafs.find(parent) != leafs.end();
				if (!is_in) {
					leafs.emplace(parent);
				}
			}
			// Set the parents as next current_nodes
			current_nodes = leafs;
			leafs.clear();
		}
	}

	/**
	 * Implementation of the fitch algorithm for a parcimonic assignment of gene states in a tree
	 *
	 * @param t A tree object
	 */
	void etiquetteTree(Node* root) {
		// ===== Ascending phase =====
		// TODO: do a loop getting the parent at max_depth() - i for each leaf and assign with this
		set<Node*> v;
		tree::getLeafNodes(root, v); // Gets all the leaf nodes and put it in the v vector
		_fitchAscendTree(v);
		//for (Node* n : v) { // For each leaf node we go up to the root
		//	Node* current_node = n;
		//	Node* next_node = n->getParentNode();
		//	while(next_node != nullptr) { // While we haven't reached the root we assign to the parent node the current state
		//		if (next_node != nullptr) { // If we are not at the root
		//			set<string> current_node_states = current_node->getStates(); // Saves the current node state
		//			set<string> next_node_states = next_node->getStates();
		//			set<string> intersect;
		//			// Get the intersection of the child node and the parent node
		//			set_intersection(current_node_states.begin(), current_node_states.end(),
		//						next_node_states.begin(), next_node_states.end(),
		//						inserter(intersect, intersect.begin()));
		//			// If some value of the current node and the parent node states correspond
		//			if (intersect.size() > 0) {
		//				next_node->setStates(intersect);
		//				cout << "INTERSECT " << current_node->getName() << " --> " << next_node->getName();
		//				for (string s: intersect) {
		//					cout << "\t" << s << endl;
		//				}
		//			// Else the two sets are fused together
		//			} else {
		//				set<string> union_set;
		//				set_union(current_node_states.begin(), current_node_states.end(),
		//						next_node_states.begin(), next_node_states.end(),
		//						inserter(union_set, union_set.begin()));
		//				next_node->setStates(union_set);
		//				/*for (string s: union_set) {
		//					cout << "\t" << s << endl;
		//				}*/
		//			}
		//		}
		//		current_node = current_node->getParentNode();
		//		next_node = current_node->getParentNode();
		//	}
		//}
		//
		//// ===== Descending phase ======
		_fitchDescendTree(root);
	};
}
