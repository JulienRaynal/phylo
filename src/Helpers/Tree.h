#ifndef PHYLO_TREE_H
#define PHYLO_TREE_H

#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Objects/Node.h"
#include "Trunk.h"

/**
 * Tree structure containing the root node
 */
namespace tree {
		/**
		 * Build the tree of nodes using a newick notation like: (((A,B),C),(D,E))
		 * The tree is built in a depth first manner and then left to right, going up the tree to go on the right branches
		 * @parameter path_to_file The path to the file holding the newick notation in one line
		 */
		Node* buildTree(std::string path_to_file);	

		/**
		 * A cleaner tree display
		 * Largely inspired by https://www.techiedelight.com/fr/c-program-print-binary-tree/
		 * @param root A pointer to the root node of the tree
		 * @param prev A pointer to the previous trunk
		 * @param isLeft A boolean saying if the analysed part is left or not
		 */
		void cleanTreeDisplay(Node* root, std::vector<trunk::Trunk*>& v, trunk::Trunk* prev = nullptr, bool isLeft = false);

		/**
		 * Function to find a node (brute force because the tree is not ordered)
		 * @param root A pointer to the root node of the tree
		 * @param value The string value to lookup
		 */
		Node* findNode(Node* root, std::string value);

		/**
		 * Get a vector of pointer to all the leaf nodes
		 * Breadth-first-search (BFS) https://en.wikipedia.org/wiki/Breadth-first_search
		 * @param v A vector of pointers to Node object
		 * @return std::vector<Node*>
		 */
		std::set<Node*>& getLeafNodes(Node* node, std::set<Node*>& s);

		/**
		 * Transforms a Node tree into a newick string
		 * Works in a depth first manner using a stack object
		 *
		 * @parameter root A pointer to a node
		 * @parameter newick_string The string that will be built with newick annotation
		 */
		void treeToNewick(Node* root, std::string& newick_string);
};

#endif
