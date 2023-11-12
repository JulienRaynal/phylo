#ifndef PHYLO_TRUNK_H
#define PHYLO_TRUNK_H

#include <string>
#include <vector>
#include <iostream>

namespace trunk {
    /**
     * A trunk structure that manages the string to display the tree
     * ONLY USED FOR DISPLAY PURPOSE
     */
	struct Trunk {
		Trunk* prev;
		std::string str;

        /**
         * Constructor of the trunk structure
         *
         * @param prev
         * @param str
         */
		Trunk(Trunk* prev, std::string& str) {
			this->prev = prev;
			this->str = str;
		}
	};

	/**
	 * Memory management function for the Trunk structures
	 * Frees all the trunks.
	 * Needs to be called after displaying the tree
	 *
	 * @param v A vector containing pointers to Trunk structures
	 */
	void freeTrunk(std::vector<Trunk*> v);	

	/**
	 * Display the string contained in the trunk structure (used to build the tree)
	 *
	 * @param p A pointer to a trunk
	 */
	void showTrunks(trunk::Trunk* p);
};

#endif
