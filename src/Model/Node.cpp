#include "Node.h"

using namespace std;

Node::Node(const string& name, int depth) {
	this->_name = name;
	this->_depth = depth;
}

Node::Node(const string& name, Node* parent) {
	this->_name = name;
	this->_parent = parent;
}

Node::~Node(){
	delete this->_parent;
	delete this->_left;
	delete this->_right;
}

void Node::setName(std::string& name) {
	this->_name = name;
}

string& Node::getName() {
	return this->_name;
}

void Node::setLeftChild(Node* left_child) {
	this->_left = left_child;
}

bool Node::checkLeftChild() {
	if (this->_left) {
		return true;
	} else {
		return false;
	}
}

Node* Node::getLeftChild() {
	return this->_left;
}

void Node::setRightChild(Node* right_child) {
	this->_right = right_child;
}

bool Node::checkRightChild() {
	if (this->_right) {
		return true;
	} else {
		return false;
	}
}

Node* Node::getRightChild() {
	return this->_right;
}

void Node::setParentNode(Node* parent) {
	this->_parent = parent;
}


bool Node::checkParentNode() {
	if (this->_parent) {
		return true;
	} else {
		return false;
	}
}

Node* Node::getParentNode() {
	return this->_parent;
}
