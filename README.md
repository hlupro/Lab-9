# Lab-9
Red-Black Tree

(a) Summarize your approach to the problem, and how your code addresses the abstractions needed.

    My approach to Red-Black Trees is very similar to the way I approached Binary Tree's in the last lab.
    I have a constructor that initializes an empty Tree by initializing the root node to equal NIL.
    From there elements are added into the tree via the insert function which calls private Methods
    to act on the tree. Like last lab, I created public and private functions of each algorithm, the public
    functions were used to handle print statements for testing while the private method did all
    the heavy lifting by acting on the tree and inserting and deleting, or using recursion to travel
    down the tree. While a Red-Black Tree is similar to a Binary Tree, a RB tree uses a static treenode called NIL that acts
    as a NULL pointer.
      The RB tree follows four rules that
    make them more balanced than a typical binary tree. In order to uphold these properties, four new functions
    were added to the binary tree structure. LeftRotate, RightRotate, Insert-Fixup and Delete-Fixup. When Inserting
    or deleting a node, there is a change that the RB tree will break one of this four rules so after inserting a
    node insert fixup is called and when deleting a node delete-fixup is called. Inside these functions, the rotate functions
    are called which rotate around the node and its left or right child. For leftRotate the parent node becomes the left child and its right child becomes the parent. RightRotate is symmetric. These functions were fairly straight forward.
    In order to time the algorithms, I created a function outside the main, that would use the chrono library to time the insertion of n random elements (n is between 1,1000), searching for n elements and then deleting the nodes of n elements which was the whole tree. In order for this to work, I had to compile and link with std=c++11 inside my makefile.
    At the end, I had to use the deleteNIL function to delete the static member NIL.

(b) What is the theoretical time complexity of your algorithms (best and worst case), in terms of the
size of the tree? Be sure to vary the parameters enough to use the observations to answer the
next questions!

  Inserting into a RB Tree takes O(log n) since inserting depends on the height of the tree which is log n and
  insert-fixup also takes O(log n).
  Deleting a node takes O(log n) and deleteFixup takes O(log n) time as well.
  LeftRotate and RightRotate take O(1) time.
  The search, minimum, maximum and sucessor functions all take O(log n) which is better than
  the time it took with a binary tree which was O(height h).

(c) Use timing tools to study the cost of each of the data structure algorithms. Does the data align
with the theoretical guarantees?

  See graphs and tables.

(d) How could the code be improved in terms of usability, efficiency, and robustness?

    When timing the functions of the RB tree and BinaryTree, I relied on random numbers when inserting and Searching
    for nodes, so the nodes i was inserting into one tree was most likely not the same as the other tree and that may have
    skewed some results of the times, since a binary tree works better when its balanced and not when its unbalanced.
    I also could have created another file to hold my time function in the main in order to free up some space.
    Memory management was also an issue due to the static member NIL. I had to include a member function to delete it since, it couldn't be done inside the main and if I deleted it, I couldn't reinitialize it for a new tree. Making it easier to
    delete and re-initiate NIL would make this code more user friendly.
