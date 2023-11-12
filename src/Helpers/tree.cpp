#include "tree.h"

using namespace std;
using namespace trunk;

namespace tree {
	// ======================================
	//	 GETTER AND SETTER FUNCTIONS
	// ======================================
	Node* findNode(Node* root, string value) {
		// Checks if the node pointer is not null else we return directly the null pointer
		// If the name is the same as the one looked for returns the node
		if (root != nullptr) {
			if (root->getName() == value) {
				return root; 
			}
			// If the name is not the one looked for we look recursively in the children nodes
			// 2 options:
			// 	- one of the children contains the node searched and returns it
			// 	- no children contains the looked up node and the nullptr children of the leaves are returned
			else {
				Node* foundNode = findNode(root->getLeftChild(), value);
				if (foundNode == nullptr) {
					foundNode = findNode(root->getRightChild(), value);
				}
				return foundNode;
			}
		}
		return root;
	}

	set<Node*>& getLeafNodes(Node* node, set<Node*>& stacked_nodes) {
		// If the current node contains neither a left nor a right child
		// Then it is a leaf node, and we add it to the set of leaves
		if ((!node->getLeftChild()) && (!node->getRightChild())) {
			stacked_nodes.emplace(node);
		// Else a Breadth-First-Search is done to look for the leaves of the current node
		} else {
			if (node->getLeftChild()) {
				getLeafNodes(node->getLeftChild(), stacked_nodes);
			}
			if (node->getRightChild()) {
				getLeafNodes(node->getRightChild(), stacked_nodes);
			}
		}
		return stacked_nodes;
	}

	// ======================================
	// 	Tree build function
	// ======================================
	Node* buildTree(string path_to_file) {
        // variables needed in the while loop
		ifstream ifs(path_to_file);
		stack<Node*> stacked_nodes;
		int unnamed_node_id = 1;
		Node* current_node = nullptr;
		string name;

        // for each caracter in the string in the file
		while(ifs){
			char c = ifs.get();
            // If '(' then we have a new node that is not a leaf
			if (c == '(') {
				Node* new_node = new Node(to_string(unnamed_node_id++), stacked_nodes.size());
				if (current_node) {
					current_node->addChild(new_node);
				}
				stacked_nodes.push(new_node);
				current_node = new_node;
			}
            /* If ')' or ',' then there's two options
             *  - If there was a string before then we reach the end of the name of a leaf and create a new leaf
             *  - If no string was before then we reached the end of a node and need to go up the stack
             */
			else if (c == ')' || c == ',') {
				if (!name.empty()) {
					Node* new_node = new Node(name, stacked_nodes.size() + 1);
					name.clear();
					current_node->addChild(new_node);
				} else {
					stacked_nodes.pop();
					current_node = stacked_nodes.top();
				}
			}
            // If there's a character we're currently building a child name and add it to the child name string
            // We expect to later meet either ')' or ',' as only the leaf nodes are named
			else {
				name.push_back(c);
			}
		}
		return current_node;
	}

	// ======================================
	// 	Tree display related functions
	// ======================================
	void cleanTreeDisplay(Node* root, vector<Trunk*>& v, Trunk* prev,  bool isRight) {
		// The string composing the body of the tree
		string up = ".----";
		string middle = "----";
		string down = "`----";
		string separator = "   |";

		// The function is recursive and will reach empty pointers which indicates it has reached leaves previously
		if (root == nullptr) {
			return;
		}

        // For each loop adds space to build the string for the next depth
		string prev_str = "    ";
		Trunk* trunk = new Trunk(prev, prev_str);
		v.push_back(trunk);

		cleanTreeDisplay(root->getRightChild(), v, trunk, true);

        // Uses the recursive logic to detect if a node is right, middle or left in the tree and adds the corresponding tree
		if (!prev) {
			trunk->str = middle;
		} else if (isRight) {
			trunk->str = up;
			prev_str = (separator);
		} else {
			trunk->str = down;
			prev->str = prev_str;
		}

        // Displays the built trunk
		showTrunks(trunk);
		cout << " " << root->getName() << "(";
        // prints all the gene states of the node between '(' and ')'
		for (string stacked_nodes: root->getStates()) {
			cout << stacked_nodes << ",";
		}
		cout << ")" <<  endl;

		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = separator;
        // Builds the left part recursively of the tree
		cleanTreeDisplay(root->getLeftChild(), v, trunk, false);
	}
}
