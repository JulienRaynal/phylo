#include <iostream>
#include <string>
#include "./Objects/Node.h"
#include "./Helpers/tree.h"
#include "./lca/lca.h"
#include "./fitch/fitch.h"
//#include "./reconciliation/reconciliation.h"

using namespace std;

string my_program;

/**
 * A string to be called as a user manual
 */
void usage() {
	cerr << "Usage: " << my_program << "<newick_file>" << endl
	<< my_program << "\t-h,\t --help\n\tdisplays this message" << endl;
}

/**
 * A parser to automatically parse the user input and check that it is an integer
 * @param input A character or string that is supposed to be a int
 * @param output A int
 * @return bool
 */
bool tryParse(string& input, int& output) {
	try {
		output = stoi(input);
	} catch (invalid_argument) {
		return false;
	}
	return true;
}

/**
 * Management function for the main LCA application
 * @param t A root node of a tree
 */
void manage_lca(Node* root) {
	string node_name1, node_name2;
	cout << "Please input the name of the first node you want to get the LCA from: " << endl;
	getline(cin, node_name1);
	cout << "Please input the name of the second node you want to get the LCA from: " << endl;
	getline(cin, node_name2);
	Node* n1 = tree::findNode(root, node_name1);
	Node* n2 = tree::findNode(root, node_name2);

	// If node 1 or node 2 is a nullptr then the node name doesn't exist
	if ((!n1) || (!n2)) {
		cerr << "One or both node name don't exist, please input existing names" << endl;
		return;
	}

	Node* ancestor = lca::findLowestCommonAncestor(n1, n2);
	cout << "Common ancestor of " << n1->getName() << " and " << n2->getName()
		<< "\n\tName: " << ancestor->getName()
		<< "\n\tDepth: " << ancestor->getDepth() << endl;
}

int main(int argc, char **argv) {
	my_program = "Phylo"; // just used for a nicer output
	string input; // Takes the user input
	int output; // User input converted in int
	//Tree t; // Tree that will be used in the whole code;
	Node* root = nullptr;
	
	cout << "You are currently running the program " << '\'' << my_program << '\'' << endl;
	if ((argc != 2) || ((string(argv[1]) == "-h") || string(argv[1]) == "--help")) {
		if (argc != 2) {
			cerr << "Bad usage !!!" << endl;
		}
		usage();
		return 1;
	}


	while(true) {
		cout << "###############################################################################################\
			\nWelcome on the program " << my_program << ".\nPlease choose an option (if not done you need to build the tree first):\
			\n\tBuild tree: 1\
			\n\tLCA: 2\
			\n\tTree reconciliation: 3\
			\n\tFitch algorihm: 4\
			\n\tEXIT: 0\
			\n###############################################################################################" << endl;
		cout << "YOUR INPUT: ";
		getline(cin, input);
		while(!tryParse(input, output)) {
			cerr << "Error, please input a NUMBER" << endl;
			getline(cin, input);
		}
		switch (output) {
			case 1: {
                // If a tree exists we delete it to build a new one
				if (root) {
					root->freeNode();
				}
				vector<trunk::Trunk*> tv1;
				root = tree::buildTree(argv[1]);
				tree::cleanTreeDisplay(root, tv1);
				trunk::freeTrunk(tv1);
				break;
				}
			case 2:
				manage_lca(root);
				break;
			case 3:
				// TODO: Finish this one day
				cout << "This algorithm is not implemented YET" << endl;
				break;
			case 4:{
                cout << "The state of the gene for each node is displayed between parenthesis after the name" << endl;
                fitch::etiquetteTree(root);
				vector<trunk::Trunk*> tv;
				tree::cleanTreeDisplay(root, tv);
				trunk::freeTrunk(tv);
				break;
			      }
			case 0:
				root->freeNode();
				return EXIT_SUCCESS;
		}
	}
}
