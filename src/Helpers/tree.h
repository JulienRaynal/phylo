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
         * Function to find a node (brute force because the tree is not ordered)
         * Uses a depth-first-search
         *
         * Complexity O(n)
         *
         * @param root A pointer to the root node of the tree
         * @param value The string value to lookup
         */
        Node* findNode(Node* root, std::string value);

        /**
         * Get a vector of pointer to all the leaf nodes
         * Breadth-first-search (BFS) https://en.wikipedia.org/wiki/Breadth-first_search
         *
         * @param v A vector of pointers to Node object
         *
         * @return std::vector<Node*>
         */
        std::set<Node*>& getLeafNodes(Node* node, std::set<Node*>& s);

        /**
         * Build the tree of nodes using a newick notation like: (((A,B),C),(D,E)) and returns the root node
         * The tree is built in a depth first manner and then left to right, going up the tree to go on the right branches
         * To do this it uses a stack adding child node in it when going down and removing nodes to go up to parent nodes
         *
         * Complexity O(n): where n is the length of the newick string, loops once on each character of the string
         *
         * @parameter path_to_file The path to the file holding the newick notation in one line
         *
         * @return Node*
         */
        Node* buildTree(std::string path_to_file);

        /**
         * A cleaner tree display
         * Largely inspired by https://www.techiedelight.com/fr/c-program-print-binary-tree/
         *
         * @param root A pointer to the root node of the tree
         * @param prev A pointer to the previous trunk
         * @param isLeft A boolean saying if the analysed part is left or not
         */
        void cleanTreeDisplay(Node* root, std::vector<trunk::Trunk*>& v, trunk::Trunk* prev = nullptr, bool isLeft = false);
};

#endif
