#include "RBTree.h"
#include "binaryTree.h"
#include <chrono>
#include <cstdlib>

RBTree::TreeNode* const RBTree::NIL = new TreeNode({0,BLACK, NULL, NULL, NULL});

void time(int n)
{
  RBTree x;
  BinaryTree y;
  std::cout << "\nTiming how long it takes to insert " << n << " elements." << std::endl;
  auto start = std::chrono::system_clock::now();
  for(int i = 0; i < n; i++)
  {
    int r = rand() % 1000 + 1;
    x.insert(r);
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elasped_seconds = end-start;
  std::cout << "RB Elasped Time: " << std::fixed << elasped_seconds.count() << " seconds\n";

  start = std::chrono::system_clock::now();
  for(int i = 0; i < n; i++)
  {
    int r = rand() % 1000 + 1;
    y.insert(r);
  }
  end = std::chrono::system_clock::now();
  elasped_seconds = end - start;
  std::cout << "BT Elasped Time: " << elasped_seconds.count() << " seconds\n";

  std::cout << "\nTiming how long it takes to search " << n << " elements." << std::endl;
  start = std::chrono::system_clock::now();
  for(int i = 0; i < n; i++)
  {
    int r = rand() % 1000 + 1;
    x.timeSearch(r);
  }
  end = std::chrono::system_clock::now();
  elasped_seconds = end - start;
  std::cout << "RB Elasped Time: " << elasped_seconds.count() << " seconds\n";

  start = std::chrono::system_clock::now();
  for(int i = 0; i < n; i++)
  {
    int r = rand() % 1000 + 1;
    y.timeSearch(r);
  }
  end = std::chrono::system_clock::now();
  elasped_seconds = end - start;
  std::cout << "BT Elasped Time: " << elasped_seconds.count() << " seconds\n";

  std::cout << "\nTiming how long it takes to delete " << n << " elements." << std::endl;
  start = std::chrono::system_clock::now();
  x.deleteTree();
  end = std::chrono::system_clock::now();
  elasped_seconds = end - start;
  std::cout << "RB Elasped Time: " << elasped_seconds.count() << " seconds\n";

  start = std::chrono::system_clock::now();
  y.deleteTree();
  end = std::chrono::system_clock::now();
  elasped_seconds = end - start;
  std::cout << "BT Elasped Time: " << elasped_seconds.count() << " seconds\n";

}

int main()
{
  std::cout << "==========================RED BLACK TREE FUNCTION TESTS============================\n\n";
  std::cout << "Initializing an empty Red Black tree\n";

  RBTree t;
  t.print();

  std::cout << "------Insert function Tests-------\n";
  std::cout << "Inserting 15,-2,1,54,76,-34 in that order into the tree.\n";
  t.insert(15);
  t.insert(-2);
  t.insert(1);
  t.insert(54);
  t.insert(76);
  t.insert(-34);

  t.print();
  std::cout << "Inserting a double of a node -2\n";
  t.insert(-2);
  t.print();
  std::cout << "Inserting a double of the root 15\n";
  t.insert(15);
  t.print();

  std::cout << "------Search function Tests-------\n\n";
  t.getSearch(76);
  t.getSearch(-2);
  t.getSearch(10000);
  t.getSearch(0);

  std::cout << "------Min and Max Tests------\n\n";
  t.print();
  t.getMin();
  t.getMax();

  std::cout << "-----------Sucessor Tests----------\n\n";
  t.print();
  t.getSucessor(15);
  t.getSucessor(1);
  t.getSucessor(53);
  t.getSucessor(76);

  std::cout << "------------Inorder Print Test ---------\n\n";
  t.printInorder();

  std::cout << "------------Delete Tests--------------\n";
  {
    t.print();
    t.getDelete(-2);
    t.print();
    t.getDelete(76);
    t.print();
    t.getDelete(15);
    t.print();
    t.getDelete(234);
    std::cout <<"\nNow Deleting Tree " << std::endl;
    t.deleteTree();
    t.print();
  }

  for(int i = 10000; i <= 100000; i+= 10000)
  {
    time(i);
  }
  t.deleteNIL();
}
