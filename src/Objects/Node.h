#ifndef PHYLO_NODE_H
#define PHYLO_NODE_H


#include <string>
#include <set>

class Node {
	protected:
		std::string _name;
		Node* _parent = nullptr;	
		Node* _left_child = nullptr;
		Node* _right_child = nullptr;
		int _depth = 0;
		std::set<std::string> _states = {};

	public:
		/**
		 * Constructor if the node doesn't have a known parent node
		 * @param _name Name of the current node
		 */
		Node(const std::string& name, int depth = 0);
		/**
		 * Constructor if the node has a known parent node
		 * @param _name Name of the current node
		 * @param parent Reference to the parent of the current node
		 */
		Node(const std::string& name, Node* parent);
		/**
		 * Destructor
		 */
		~Node();
		/**
		 * A manual destructor
		 * @param n A pointer to the root node
		 */
		void freeNode();
		
		/**
		 * Get the node name
		 * @return std::string
		 */
		std::string& getName();

		/**
		 * Dynamically assign a child if a child is not set (one left or right child is nullptr in that case)
		 * The child also gets the current node assigned as parent
		 *
		 * @param Node* Pointer to a child node
		 */
		void addChild(Node* child);

		/**
		 * Get the pointer of the left child
		 *
		 * @return Node*
		 */
		Node* getLeftChild();

		/**
		 * Get the pointer  of the right child
		 *
		 * @return Node*
		 */
		Node* getRightChild();

		/**
		 * Set the parent of the node
		 *
		 * @param parent Reference to the parent node
		 */
		void setParentNode(Node* parent);
		
		/**
		 * Get the pointer of the parent node
		 *
		 * @return Node*
		 */
		Node* getParentNode();

		/**
		 * Get the depth value of the current node
		 *
		 * @return int
		 */
		int getDepth() {
			return this->_depth;
		}

		/**
		 * Get the possible states of the Node
		 *
		 * @return std::list<std::string>&
		 */
		std::set<std::string>& getStates();

		/**
		 * Add a possible state to the Node
		 *
		 * @param s A string to add to the possible states
		 */
		void setStates(std::set<std::string> states);

};
#endif
