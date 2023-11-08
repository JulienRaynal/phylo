#include "Node.h"
#include <iostream>

using namespace std;

set<string> stringSplitting(string s) {
	size_t find_number = s.find_first_of("0123456789");
	string state;
	state = s.substr(0, find_number);
	set<string> states;
	if (state.length() > 0) {
		states.emplace(state);
	}
	return states;
}

Node::Node(const string& name, int depth) {
	this->_name = name;
	this->_depth = depth;
	this->_states = stringSplitting(name);
}

Node::Node(const string& name, Node* parent) {
	this->_name = name;
	this->_parent = parent;
	this->_states = stringSplitting(name);
}

void Node::freeNode() {
    delete this;
}

Node::~Node(){
    if (!this) {
        return;
    }

    this->getLeftChild()->freeNode();
    this->getRightChild()->freeNode();
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

set<string>& Node::getStates() {
	return this->_states;
}

void Node::setStates(std::set<string> states) {
	this->_states = states;
}

