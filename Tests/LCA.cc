#include <gtest/gtest.h>
#include <iostream>
#include "../src/lca/lca.h"
#include "../src/Helpers/Tree.h"


using namespace std;

TEST(FindCommonAncestor, LCA) {
	Node* root = tree::buildTree("./Tests/test_file.txt");
	Node* n1 = tree::findNode(root, "A1");
	Node* n2 = tree::findNode(root, "A2");

	Node* ancestor = lca::findLowestCommonAncestor(n1, n2);
	ASSERT_EQ(ancestor->getName(), "1");
	ASSERT_EQ(ancestor->getDepth(), 0);
}
