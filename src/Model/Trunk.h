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

class Trunk {
	private:
		Trunk* _prev;
		std::string _str;
	public:
		/**
		 * Constructor
		 * @param prev Pointer to the previous trunk
		 * @param str String for this trunk
		 */
		Trunk(Trunk* prev, std::string& str);

		/**
		 * Destructor
		 */
		~Trunk();

		/**
		 * Get the previous Trunk
		 * @return Trunk*
		 */
		Trunk* getPrev();	

		/**
		 * Set the previous Trunk
		 * @prev Pointer to the previous trunk
		 */
		void setPrev(Trunk* prev);

		/**
		 * Get this Trunk string
		 * @return string
		 */
		std::string& getStr();
		/**
		 * Set this Trunk string
		 * @param A string for this trunk
		 */
		void setStr(std::string& str);
};

#endif
