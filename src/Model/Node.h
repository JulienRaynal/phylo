#ifndef PHYLO_NODE_H
#define PHYLO_NODE_H


#include <string>

class Node {
	protected:
		std::string _name;
		Node* _parent = nullptr;	
		Node* _left = nullptr;
		Node* _right = nullptr;
		int _depth = 0;

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
		 * Set the name of the node
		 * @param name New name for the node
		 */
		void setName(std::string& name);
		
		/**
		 * Get the node name
		 * @return std::string
		 */
		std::string& getName();

		/**
		 * Set the left child of the current node
		 * @param left_child Reference to the left child
		 */
		void setLeftChild(Node* left_child);
		
		/**
		 * Check if left child exists
		 * @return bool
		 */
		bool checkLeftChild();
		
		/**
		 * Get the value of the left child
		 */
		Node* getLeftChild();
		
		/**
		 * Set the right child of the current node
		 * @param right_child Reference to the right child
		 * @return Node*
		 */
		void setRightChild(Node* right_child);
		
		/**
		 * Check if right child exists
		 */
		bool checkRightChild();
		
		/**
		 * Get the value of the right child
		 * @return bool
		 */
		Node* getRightChild();
		
		/**
		 * Set the parent of the node
		 * @param parent Reference to the parent node
		 * @return Node*
		 */
		void setParentNode(Node* parent);
		
		/**
		 * Check if parent Node exists
		 * @param parent A pointer to the parent node
		 * @return bool
		 */
		bool checkParentNode();
		
		/**
		 * Get the value of the parent node
		 * @return Node*
		 */
		Node* getParentNode();

		/**
		 * Get the depth value of the current node
		 * @return int&
		 */
		int getDepth() {
			return this->_depth;
		}
		/**
		 * Set the depth value of the current node
		 * @param int& Depth of the node
		 */
		void setDepth(int& depth) {
			this->_depth = depth;
		}
};

#endif
