#ifndef PHYLO_TREE_H
#define PHYLO_TREE_H

#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include "Node.h"
#include "Trunk.h"

/**
 * Tree structure containing the root node
 */
class Tree{
	private: 
		Node* _root;
		std::vector<Trunk*> _trunks;
	public:
		/**
		 * Free the tree memory and the node it contains
		 */
		~Tree();

		/**
		 * Get the root node
		 * @return Node*
		 */
		Node* getRoot();
		
		/**
		 * Set the root node of the tree
		 * @param root A pointer to the root node
		 */
		void setRoot(Node* root);

		/**
		 * Build the tree of nodes using a newick notation like: (((A,B),C),(D,E))
		 * The tree is built in a down first manner and then left to right, going up the tree to go on the right branches
		 * @parameter path_to_file The path to the file holding the newick notation in one line
		 */
		Node* buildTree(std::string path_to_file);	

		/**
		 * Print the binary tree
		 * @parameter root The root node
		 * @parameter space
		 */
		void printTree(Node* root, int space = 0);

		/**
		 * Display the value of the trunk structure (used to build the tree)
		 * @param p A pointer to a trunk
		 */
		void showTrunks(Trunk* p);

		/**
		 * A cleaner tree display
		 * Largely inspired by https://www.techiedelight.com/fr/c-program-print-binary-tree/
		 * @param root A pointer to the root node of the tree
		 * @param prev A pointer to the previous trunk
		 * @param isLeft A boolean saying if the analysed part is left or not
		 */
		void cleanTreeDisplay(Node* root, Trunk* prev = nullptr, bool isLeft = false);

		/**
		 * Function to find a node (brute force because the tree is not ordered)
		 * @param root A pointer to the root node of the tree
		 * @param value The string value to lookup
		 */
		Node* findNode(Node* root, std::string value);

		/**
		 * Returns the list of trunk used to display the tree
		 * @note This is only needed to avoid memory leaks
		 * @return vector<Trunk*> 
		 */
		std::vector<Trunk*> getTrunks();

		/**
		 * Add a Trunk to the vector of Trunks
		 * @Note this is only needed to avoid memory leaks
		 * @param t A pointer to a Trunk to be added in the list
		 */
		void addTrunk(Trunk* t);

		/**
		 * Get a vector of pointer to all the leaf nodes
		 * @param v A vecotr of pointers to Node object
		 * @return std::vector<Node*>
		 */
		std::vector<Node*>& getLeafNodes(Node* root, std::vector<Node*>& v);
};

#endif
