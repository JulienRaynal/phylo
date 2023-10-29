#include "Trunk.h"

using namespace std;

Trunk::Trunk(Trunk* prev, string& str) {
	this->setPrev(prev);
	this->setStr(str);
}

Trunk::~Trunk() {
	free(this->getPrev());
}

Trunk* Trunk::getPrev() {
	return this->_prev;
}

void Trunk::setPrev(Trunk* prev) {
		this->_prev = prev;
}

std::string& Trunk::getStr() {
		return this->_str;
}

void Trunk::setStr(std::string& str) {
		this->_str = str;
}
