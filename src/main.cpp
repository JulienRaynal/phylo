#include <iostream>
#include <string>
#include <libgen.h>
#include "./Model/Node.h"
#include "./Model/Tree.h"
#include "./LCA/LCA.h"

using namespace std;

char* my_program = nullptr;

void usage() {
	cerr << "Usage: " << my_program << "<newick_file>" << endl
	<< my_program << "\t-h,\t --help\n\tdisplays this message" << endl;
}

bool tryParse(string& input, int& output) {
	try {
		output = stoi(input);
	} catch (invalid_argument) {
		return false;
	}
	return true;
}

void manage_lca(Tree& t) {
	string node_name1, node_name2;
	cout << "Please input the name of the first node you want to get the LCA from: " << endl;
	getline(cin, node_name1);
	cout << "Please input the name of the second node you want to get the LCA from: " << endl;
	getline(cin, node_name2);
	Node* n1 = t.findNode(t.getRoot(), node_name1);
	Node* n2 = t.findNode(t.getRoot(), node_name2);

	// If node 1 or node 2 is a nullptr then the node name doesn't exist
	if ((!n1) || (!n2)) {
		cerr << "One or both node name don't exist, please input existing names" << endl;
		return;
	}

	Node* ancestor = LCA::findLowestCommonAncestor(n1, n2);
	cout << "Common ancestor of " << n1->getName() << " and " << n2->getName()
		<< "\n\tName: " << ancestor->getName()
		<< "\n\tDepth: " << ancestor->getDepth() << endl;
}

int main(int argc, char **argv) {
	my_program = basename(argv[0]); // just used for a nicer output
	bool exit = false; // Allows to manage the exit of the program
	string input; // Takes the user input
	int output; // User input converted in int
	Tree t; // Tree that will be used in the whole code;
	
	cout << "You are currently running the program " << '\'' << my_program << '\'' << endl;
	if ((argc != 2) || ((string(argv[1]) == "-h") || string(argv[1]) == "--help")) {
		if (argc != 2) {
			cerr << "Bad usage !!!" << endl;
		}
		usage();
		return 1;
	}


	while(exit != true) {
		cout << "###############################################################################################\
			\nWelcome on the program " << my_program << ".\nPlease choose an option:\
			\n\tBuild tree: 1\
			\n\tLCA: 2\
			\n\tEXIT: 0\
			\n###############################################################################################" << endl;
		cout << "YOUR INPUT: ";
		getline(cin, input);
		while(!tryParse(input, output)) {
			cerr << "Error, please input a NUMBER" << endl;
			getline(cin, input);
		}
		switch (output) {
			case 1: 
				t.buildTree(argv[1]);
				t.cleanTreeDisplay(t.getRoot());
				break;
			case 2:
				manage_lca(t);
				break;
			case 0:
				return EXIT_SUCCESS;
		}
	}
}
