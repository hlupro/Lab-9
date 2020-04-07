#include "RBTree.h"

RBTree :: RBTree()
{
  root = nullptr;
}

RBTree :: RBTree(int n)
{
  root = new TreeNode;
  root->key = n;
  root->left = nullptr;
  root->right = nullptr;
  root->parent = nullptr;
}

RBTree :: TreeNode* RBTree :: search(TreeNode* x, int k)
{
  if (x == nullptr || x->key == k)
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
  while (x->left != nullptr)
  {
    x = x->left;
  }
  return x;
}

RBTree :: TreeNode* RBTree :: maximum(TreeNode* x)
{
  while(x->right != nullptr)
  {
    x = x->right;
  }
  return x;
}

RBTree :: TreeNode* RBTree :: sucessor(TreeNode* x)
{
  if (x->right != nullptr)
  {
    return minimum(x->right);
  }
  TreeNode* y = x->parent;
  while(y != nullptr && x == y->right)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

void RBTree :: deleteNode(TreeNode* z)
{
  if(z->left == nullptr)
  {
    transplant(z,z->right);
  }
  else if(z->right == nullptr)
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
  if(u->parent == nullptr)
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
  if(v != nullptr)
  {
    v->parent = u->parent;
  }
}

int RBTree :: getHeight(TreeNode* x)
{
  if(x == nullptr)
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
  if(x == nullptr)
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
  if(x != nullptr)
  {
    inorder(x->left);
    std::cout << x->key << " ";
    inorder(x->right);
  }
}

void RBTree :: insert(int n)
{
  TreeNode* z = new TreeNode;
  TreeNode* y = nullptr;
  z->key = n;
  z->right = nullptr;
  z->left = nullptr;
  z->parent = nullptr;
  TreeNode* x = root;
  while (x != nullptr)
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
  if (y == nullptr)
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
}

void RBTree :: getSearch( int k)
{
  std::cout << "Searching for a node in the tree with the key " << k  << "..."<< std::endl;
  if(search(root, k) != nullptr)
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
  if(root != nullptr)
  {
    std::cout << "Now deleting the tree." << "\n" << std::endl;
    while(root != nullptr)
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
  if(root == nullptr)
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
  while(root != nullptr)
  {
    deleteNode(root);
  }
}
