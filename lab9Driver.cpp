#include "RBTree.h"

RBTree::TreeNode* const RBTree::NIL = new TreeNode({0,BLACK, nullptr, nullptr, nullptr});

int main()
{
  RBTree t;
  t.insert(11);
  t.insert(2);
  t.insert(14);
  t.insert(15);
  t.insert(1);
  t.print();
  t.printInorder();
}
