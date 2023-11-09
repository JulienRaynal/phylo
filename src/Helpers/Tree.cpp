#include "Tree.h"

using namespace std;
using namespace trunk;

namespace tree {
	// ======================================
	//	 GETTER AND SETTER FUNCTIONS
	// ======================================
	Node* findNode(Node* root, string value) {
		if (root != nullptr) {
			if (root->getName() == value) {
				return root; 
			}
			else {
				Node* foundNode = findNode(root->getLeftChild(), value);
				if (foundNode == nullptr) {
					foundNode = findNode(root->getRightChild(), value);
				}
				return foundNode;
			}
		}
		else {
			return nullptr;
		}
	}

	set<Node*>& getLeafNodes(Node* node, set<Node*>& s) {
		if ((!node->getLeftChild()) && (!node->getRightChild())) {
			s.emplace(node);
		} else {
			if (node->getLeftChild()) {
				getLeafNodes(node->getLeftChild(), s);
			}
			if (node->getRightChild()) {
				getLeafNodes(node->getRightChild(), s);
			}
		}
		return s;
	}

	// ======================================
	// 	Tree build function
	// ======================================
	Node* buildTree(string path_to_file) {
		ifstream ifs(path_to_file); // Read the file 

		signed int depth = -1; // taking into account the first parentheses, the first node is at depth 0
		Node* currentNode = nullptr; // initiating the head variable tracking the current node

		stack<Node*> s; // stack of nodes which allows to follow the tree down
		
		int i = 1; // Allows to give a unique name to each unnamed vertex

		while (ifs) {
			char c = ifs.get(); // get the character
			if ((c != -1) && (c != '\n')) { // If the character is not an EOF or a EOL
				if (c == '(') { // Meeting a parenthesis means that a vertex is here
					cout << "UNKNOWN NODE" << endl;
					depth += 1;
					Node* n = new Node(to_string(i)); // We create an unnamed node since only the leaf are named	
					n->setParentNode(currentNode);
					n->setDepth(depth);
					// If the current node is a not nullptr
					if (currentNode) {
						// Check if a child has not been set already and assign the left child first if possible
						if (!currentNode->checkLeftChild()) {
							cout << "SETTING LEFT CHILD " << i << endl;
							currentNode->setLeftChild(n);
						} else if (!currentNode->checkRightChild()) {
							cout << "SETTING RIGHT CHILD " << i << endl;
							currentNode->setRightChild(n);
						} else {
							cerr << "The notation or the algorithm detected a third child for a binary node" << endl;
						}
					}
					currentNode = n; // The created node becomes the current node
					s.push(currentNode); // The currentNode is pushed onto the stack to destack later
					i++;
				}
				else if (c == ')') { // Meeting a closing parenthesis means we go up to the parent of the node
					if (depth >= 1) {
						cout << "GO UP ONE" << endl;
						depth -= 1;
						s.pop(); // Remove the node from the stack
						currentNode = s.top(); // Get the most upper node from the stack (the parent of our previous node)
					}
				}
				else if (c == ',') {
					continue;
				}
				else { // Else it should be an alphabetical character
					string node_name;
					bool next_char_valid = true;
					// Get the full string, for each character that is not ['(', ')', ','] get the next character
					// and add it to the name string
					while (next_char_valid) {
						node_name.append(string(1, c)); 	

						char p = ifs.peek(); 
						if ((p == '(') || (p == ')') || (p == ','))
						{
							next_char_valid = false;
						} else {
							c = ifs.get();
						}
					}
					// Create and assign values to the child node
					Node* n = new Node(node_name);
					int leaf_depth = depth + 1;
					n->setDepth(leaf_depth);
					//Node* n = new Node(string(1, c));
					if (!currentNode->checkLeftChild()) {
						cout << "SETTING LEFT CHILD " << c << endl;
						currentNode->setLeftChild(n);
					} else if (!currentNode->checkRightChild()) {
						cout << "SETTING RIGHT CHILD " << c << endl;
						currentNode->setRightChild(n);
					} else {
						cerr << "The notation or the algorithm detected a third child for a binary node" << endl;
					}
					n->setParentNode(currentNode); // In case of a leaf we do not set it as our current  since it will not have children
				}
			}
		}
		// Closing the stream reading the file
		ifs.close();
		// Cleaning up the stack
		int stack_size = s.size();
		for (int i = stack_size; i<=0; i--) {
			s.pop();
			cout << i << endl;
		}
		// Setting up the root in the tree object
		return s.top();
	}
	// ======================================
	// 	Tree display related functions
	// ======================================

	void printTree(Node* root, int space) {
		if (root == NULL) {
			return;
		}

		space += 10;

		// processing the right child first
		printTree(root->getRightChild(), space);

		// Adding space and printing the tree
		cout << endl;
		for (int i = 10; i < space; i++) {
			cout << " ";
		}
		cout << root->getName() << '\n';

		// processing the left child second
		printTree(root->getLeftChild(), space);
	}

	void cleanTreeDisplay(Node* root, vector<Trunk*>& v, Trunk* prev,  bool isRight) {
		string up = ".----";
		string middle = "----";
		string down = "`----";
		string separator = "   |";
		if (root == nullptr) {
			return;
		}

		string prev_str = "    ";
		Trunk* trunk = new Trunk(prev, prev_str);
		v.push_back(trunk);

		cleanTreeDisplay(root->getRightChild(), v, trunk, true);

		if (!prev) {
			trunk->str = middle;
		} else if (isRight) {
			trunk->str = up;
			prev_str = (separator);
		} else {
			trunk->str = down;
			prev->str = prev_str;
		}

		showTrunks(trunk);
		cout << " " << root->getName() << "(";
		for (string s: root->getStates()) {
			cout << s << ",";
		}
		cout << ")" <<  endl;

		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = separator;

		cleanTreeDisplay(root->getLeftChild(), v, trunk, false);
	}
}

