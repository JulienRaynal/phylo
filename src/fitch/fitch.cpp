#include "fitch.h"

using namespace std;
namespace fitch {
	/** 
	 * Gets the first element in a set of string
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
	 * 		- doing an intersect (ensemblist logic) if they have any value in common
	 * 		- doing an union (ensemblist logic) if there's no value in common between the giver and the receiver states
	 * 	If the giver has no receiver than it's the root node and it assigns to itself the first state in his state list
	 *
	 * Descending phase:
	 * 	Will assign to the receiver the node value of the giver node by either:
	 * 		- doing an intersect (ensemblist logic) if they have on value in common
	 * 		- selecting the first state of the receiver if no intersection exists (mutation)
	 *
	 *
	 *
	 * @param giver A node pointer to the giver of the gene state
	 * @param receiver A node pointer to the receiver of the gene state
	 * @param descending A boolean to know if it's the descending (slightly alter the algorithm to avoid unions)
	 */
	void _fitchAssignState(Node* giver, Node* receiver, bool descending = false) {
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
			if (!intersect.empty()) {
				receiver->setStates(intersect);
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
					receiver->setStates(union_set);
					}
				}
			}

		}

	/**
	 * A recursive algorithm to assign the states of gene to all child starting from a root node in a descending manner
	 * Uses a depth-first-search
	 *
	 * Complexity O(n)
	 *
	 * @param node A pointer to an initial node
	 */
	void _fitchDescendTree(Node* node) {
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
	 * A recursive algorithm to assign states of gene to all parent from the leaf nodes in an ascending manner
	 * Uses a breadth-first search
	 *
	 * Complexity O(n) [O(n) + O(log(n))]
	 *
	 * @param nodes_set A list of leaves from the tree
	 */
	void _fitchAscendTree(set<Node*>& nodes_set) {
		set<Node*> current_nodes = nodes_set; // create a new set to put the leaves in it
		nodes_set.clear(); // free the set to add the leaves parents in
		while (*current_nodes.begin() != nullptr) { // When the node is null then we reached the root
			for (Node* node: current_nodes) {
				Node* parent = node->getParentNode();
				_fitchAssignState(node, parent);
				// Check if the leaf is already in the set to not create doubles
				const bool is_in = nodes_set.find(parent) != nodes_set.end();
				if (!is_in) {
					nodes_set.emplace(parent);
				}
			}
			// Set the parents as next current_nodes to go in the loop
			current_nodes = nodes_set;
			nodes_set.clear();
		}
	}

	/**
	 * Implementation of the fitch algorithm for a parsimonious assignment of gene states in a tree
	 *
	 * @param t A tree object
	 */
    void etiquetteTree(Node* root) {
		set<Node*> leaves;
		tree::getLeafNodes(root, leaves); // Gets all the leaf nodes and put it in the v vector
					     
		// ===== Ascending phase =====
		_fitchAscendTree(leaves); // o(n)
		// ===== Descending phase =====
		_fitchDescendTree(root); // O(n)
	};
}
