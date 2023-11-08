//struct Trunk {
//	Trunk* _prev;
//	std::string _str;
//
//	Trunk(Trunk* prev, std::string str) {
//		this->_prev = prev;
//		this->_str = str;
//	}
//};

#ifndef PHYLO_TRUNK_H
#define PHYLO_TRUNK_H

#include <string>
#include <vector>
#include <iostream>

namespace trunk {
	struct Trunk {
		Trunk* prev;
		std::string str;

		Trunk(Trunk* prev, std::string& str) {
			this->prev = prev;
			this->str = str;
		}
	};

	/**
	 * Memory management function for the Trunk structures
	 * @param v A vector containing pointers to Trunk structures
	 */
	void freeTrunk(std::vector<Trunk*> v);	

	/**
	 * Display the value of the trunk structure (used to build the tree)
	 * @param p A pointer to a trunk
	 */
	void showTrunks(trunk::Trunk* p);
};

#endif
