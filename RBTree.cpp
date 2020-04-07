#include "RBTree.h"

RBTree :: RBTree()
{
  root = NIL;
}

RBTree :: RBTree(int n)
{
  root = new TreeNode;
  root->key = n;
  root->left = NIL;
  root->right = NIL;
  root->parent = NIL;
}

RBTree :: TreeNode* RBTree :: search(TreeNode* x, int k)
{
  if (x == NIL || x->key == k)
  {
    return x;
  }
  if(k < x->key)
  {
    return search(x->left, k);
  }
  else
  {
    return search(x->right, k);
  }
}

RBTree :: TreeNode* RBTree :: minimum(TreeNode* x)
{
  while (x->left != NIL)
  {
    x = x->left;
  }
  return x;
}

RBTree :: TreeNode* RBTree :: maximum(TreeNode* x)
{
  while(x->right != NIL)
  {
    x = x->right;
  }
  return x;
}

RBTree :: TreeNode* RBTree :: sucessor(TreeNode* x)
{
  if (x->right != NIL)
  {
    return minimum(x->right);
  }
  TreeNode* y = x->parent;
  while(y != NIL && x == y->right)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

void RBTree :: deleteNode(TreeNode* z)
{
  if(z->left == NIL)
  {
    transplant(z,z->right);
  }
  else if(z->right == NIL)
  {
    transplant(z,z->left);
  }
  else
  {
    TreeNode* y = minimum(z->right);
    if(y->parent != z)
    {
      transplant(y,y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z,y);
    y->left = z->left;
    y->left->parent = y;
  }
  delete z;
}

void RBTree :: transplant(TreeNode* u, TreeNode* v)
{
  if(u->parent == NIL)
  {
    root = v;
  }
  else if(u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
    v->parent = u->parent;
}

void RBTree :: leftRotate(TreeNode* x)
{
  TreeNode* y = x->right;
  x->right = y->left;
  if(y->left != NIL)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == NIL)
  {
    root = y;
  }
  else if(x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
    y->left = x;
    x->parent = y;
  }
}

void RBTree :: rightRotate(TreeNode* x)
{
  TreeNode* y = x->left;
  x->left = y->right;
  if(y->right != NIL)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == NIL)
  {
    root = y;
  }
  else if(x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
    y->right = x;
    x->parent = y;
  }
}

int RBTree :: getHeight(TreeNode* x)
{
  if(x == NIL)
  {
    return 0;
  }
  else
  {
    int left = getHeight(x->left);
    int right = getHeight(x->right);
    if (left > right)
    {
      return (left + 1);
    }
    else
    {
      return(right + 1);
    }
  }
}

void RBTree :: printLevel(TreeNode* x, int l)
{
  if(x == NIL)
  {
    std::cout << "* ";
    return;
  }
  if(l == 1)
  {
    std::cout << x->key << " ";
  }
  else if(l > 1)
  {
    printLevel(x->left, l-1);
    printLevel(x->right, l-1);
  }
}

void RBTree :: inorder(TreeNode* x)
{
  if(x != NIL)
  {
    inorder(x->left);
    std::cout << x->key << " ";
    inorder(x->right);
  }
}

void RBTree :: insert(int n)
{
  TreeNode* z = new TreeNode;
  TreeNode* y = NIL;
  z->key = n;
  z->right = NIL;
  z->left = NIL;
  z->parent = NIL;
  TreeNode* x = root;
  while (x != NIL)
  {
    y = x;
    if(z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NIL)
  {
    root = z;
  }
  else if(z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
  z->left = NIL;
  z->right = NIL;
  z->color = RED;
  insertFixup(z);
}

void RBTree :: insertFixup(TreeNode* z)
{
  TreeNode* y;
  while (z->parent->color == RED)
  {
    if(z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right;
      if(y->color == RED)
      {
        z->parent->color == BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else if(z == z->parent->right)
      {
        z = z->parent;
        leftRotate(z);
      }
      z->parent->color = BLACK;
      z->parent->parent->color = RED;
      rightRotate(z->parent->parent);
    }
      else
      {
        //Then clause
      }
    }
    root->color = BLACK;
  }

void RBTree :: getSearch( int k)
{
  std::cout << "Searching for a node in the tree with the key " << k  << "..."<< std::endl;
  if(search(root, k) != NIL)
  {
    std::cout << "Sucess! There exists a node in the tree with the key " << k << "\n" << std::endl;
  }
  else
  {
    std::cout << "Failure. A node with the key " << k << " does not exist within the tree." << "\n" << std::endl;
  }
}

void RBTree :: getMin()
{
  std::cout << "The minimum is " << minimum(root)->key << ".\n" << std::endl;
}

void RBTree :: getMax()
{
  std::cout << "The maximum is " << maximum(root)->key << ".\n" << std::endl;
}

RBTree ::TreeNode* RBTree :: getRoot()
{
  return root;
}

void RBTree :: getSucessor(int k)
{
  std::cout << "\nLooking for the sucessor of " << k << std::endl;
  TreeNode* y = search(root,k);
  if(y)
  {
    TreeNode* z = sucessor(y);
    if(sucessor(search(root,k)))
    {
      std::cout << "The sucessor of " << k << " is " << z->key << ".\n" << std::endl;
    }
    else
    {
      std::cout << k << " is the largest node in the tree \nand has no sucessor." << "\n" << std::endl;
    }
  }
  else
  {
    std::cout << "Error.\n" << k << " does not exist in the tree and therefore a sucessor will not be found." << "\n" << std::endl;
  }
}

void RBTree :: printInorder()
{
  inorder(root);
  std::cout << "\n" << std::endl;
}

void RBTree :: deleteTree()
{
  if(root != NIL)
  {
    std::cout << "Now deleting the tree." << "\n" << std::endl;
    while(root != NIL)
    {
      deleteNode(root);
    }
  }
  else
  {
    std::cout << "Error. Tree already deleted or does not exist." << "\n" << std::endl;
  }
}

void RBTree :: getDelete(int k)
{
  std::cout << "\nDeleting the node with the key " << k << std::endl;
  TreeNode* y = search(root, k);
  if(y)
  {
    std::cout << "Deleting " << k << " from the tree." << "\n" << std::endl;
    deleteNode(y);
  }
  else
  {
    std::cout << "Error.\n" << k << " does not exist in the tree and therefore cannont be deleted." << "\n" <<std::endl;
  }
}

void RBTree :: print()
{
  if(root == NIL)
  {
    std::cout << "The tree is empty.\n" << std::endl;
  }
  else
  {
    int h = getHeight(root);
    for(int i = 1; i <= h; i++)
    {
      printLevel(root, i);
      std::cout << "\n";
    }
  }
}

RBTree :: ~RBTree()
{
  while(root != NIL)
  {
    deleteNode(root);
  }
}
