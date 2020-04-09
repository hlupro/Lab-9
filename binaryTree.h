#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>




class BinaryTree{
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
    BinaryTree();
    BinaryTree(int n);
    void insert(int n);
    void timeSearch(int k);
    void getSearch(int k);
    void getMin();
    void getMax();
    void getSucessor(int k);
    TreeNode* getRoot();
    void printInorder();
    void deleteTree();
    void getDelete(int k);
    void print();
    ~BinaryTree();


};

#endif
