#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>




class RBTree{
 private:
   struct TreeNode{
     int key;
     TreeNode* left;
     TreeNode* right;
     TreeNode* parent;
   };

   TreeNode* root;
   TreeNode* search(TreeNode* x, int k);
   TreeNode* minimum(TreeNode* x);
   TreeNode* maximum(TreeNode* x);
   TreeNode* sucessor(TreeNode* x);
   void deleteNode(TreeNode* z);
   void transplant(TreeNode* u, TreeNode* v);
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

#endif
