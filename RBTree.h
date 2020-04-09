//Hunter Lupro
//lab9
//April 9th, 2020
#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

//enum that creates the type color_t which can be RED or BLACK
enum color_t {
  RED,
  BLACK
};


class RBTree{
 private:
   struct TreeNode{
     int key;
     color_t color;
     TreeNode* left;
     TreeNode* right;
     TreeNode* parent;
   };

   //Static TreeNode* so all the elaves point to the same NIL ptr
   static TreeNode* const NIL;

   TreeNode* root;
   //Private Methods that use recursion on the tree
   TreeNode* search(TreeNode* x, int k);
   TreeNode* minimum(TreeNode* x);
   TreeNode* maximum(TreeNode* x);
   TreeNode* sucessor(TreeNode* x);
   void deleteNode(TreeNode* z);
   //Fixup methods to fix the RedBlack tree after insertion or deletion
   void deleteFixup(TreeNode* x);
   void insertFixup(TreeNode* z);
   void transplant(TreeNode* u, TreeNode* v);
   void leftRotate(TreeNode* x);
   void rightRotate(TreeNode* x);
   int getHeight(TreeNode* x);
   void printLevel(TreeNode* x, int l);
   void inorder(TreeNode* x);

  public:
    //Defualt constructor initalizes an empty tree
    //public functions mainly handle print statements and call private functions
    RBTree();
    void insert(int n);
    void getSearch(int k);
    void timeSearch(int k);
    void getMin();
    void getMax();
    void getSucessor(int k);
    TreeNode* getRoot();
    void printInorder();
    void deleteTree();
    void deleteNIL();
    void getDelete(int k);
    void print();
    ~RBTree();
};


#endif
