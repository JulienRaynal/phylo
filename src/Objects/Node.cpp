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

    if (this->getLeftChild()) {
    	this->getLeftChild()->freeNode();
    }
    
    if (this->getRightChild()) {
    this->getRightChild()->freeNode();
    }
}

string& Node::getName() {
	return this->_name;
}

void Node::addChild(Node* child) {
	if(!this->_left_child) {
		this->_left_child = child;
	} 
	else if (!this->_right_child) {
		this->_right_child = child;
	}
	else {
		cerr << "A third child was trying to be set";
		return;
	}
	child->setParentNode(this);

}

Node* Node::getLeftChild() {
	return this->_left_child;
}

Node* Node::getRightChild() {
	return this->_right_child;
}

void Node::setParentNode(Node* parent) {
	this->_parent = parent;
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

