#include <gtest/gtest.h>
#include <iostream>
#include "../src/LCA/LCA.h"
#include "../src/Model/Tree.h"


using namespace std;

TEST(FindCommonAncestor, LCA) {
	Tree t;
	t.buildTree("./Tests/test_file.txt");
	Node* n1 = t.findNode(t.getRoot(), "A1");
	Node* n2 = t.findNode(t.getRoot(), "A2");

	Node* ancestor = LCA::findLowestCommonAncestor(n1, n2);
	ASSERT_EQ(ancestor->getName(), "1");
	ASSERT_EQ(ancestor->getDepth(), 0);
}
