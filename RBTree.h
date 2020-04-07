#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

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

   static TreeNode* const NIL;

   TreeNode* root;
   TreeNode* search(TreeNode* x, int k);
   TreeNode* minimum(TreeNode* x);
   TreeNode* maximum(TreeNode* x);
   TreeNode* sucessor(TreeNode* x);
   void deleteNode(TreeNode* z);
   void insertFixup(TreeNode* z);
   void transplant(TreeNode* u, TreeNode* v);
   void leftRotate(TreeNode* x);
   void rightRotate(TreeNode* x);
   int getHeight(TreeNode* x);
   void printLevel(TreeNode* x, int l);
   void inorder(TreeNode* x);

  public:
    RBTree();
    RBTree(int n);
    void insert(int n);
    void getSearch(int k);
    void getMin();
    void getMax();
    void getSucessor(int k);
    TreeNode* getRoot();
    void printInorder();
    void deleteTree();
    void getDelete(int k);
    void print();
    ~RBTree();


};

RBTree::TreeNode* const RBTree::NIL = new TreeNode({0,BLACK, nullptr, nullptr, nullptr});

#endif
