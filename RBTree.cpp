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
  TreeNode* x;
  TreeNode* y = z;
  color_t original = y->color;
  if(z->left == NIL)
  {
    x = z->right;
    transplant(z,z->right);
  }
  else if(z->right == NIL)
  {
    x = z->left;
    transplant(z,z->left);
  }
  else
  {
    y = minimum(z->right);
    original = y->color;
    x = y->right;
    if(y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      transplant(y,y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z,y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
    print();
  }
  if(original == BLACK)
  {
    deleteFixup(x);
  }
  delete z;
}

void RBTree :: deleteFixup(TreeNode* x)
{
  if(x == NIL)
  {
    std::cout << "ITS NIL" << std::endl;
  }
  TreeNode* w;
  while (x != root && x->color == BLACK)
  {
    if(x == x->parent->left)
    {
      std::cout << "Left Child" << std::endl;
      w = x->parent->right;
      if(w->color == RED)
      {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if(w->left->color == BLACK && w->right->color == BLACK)
      {
        w->color = RED;
        x = x->parent;
      }
      else
      {
        if(w->right->color == BLACK)
        {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(x->parent);
        x = root;
      }
    }
    else
    {
      std::cout << "Right Child" << std::endl;
      w = x->parent->left;
      if(w->color == RED)
      {
        std::cout << "W is Red" << std::endl;
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if(w->left->color == BLACK && w->right->color == BLACK)
      {
        std::cout << "W's kids are black" << std::endl;
        w->color = RED;
        x = x->parent;
      }
      else
      {
        if(w->left->color == BLACK)
        {
          std::cout << "left black" << std::endl;
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(w);
          w = x->parent->left;
        }
        std::cout << "RIGHT ROTATE" << std::endl;
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
}

void RBTree :: transplant(TreeNode* u, TreeNode* v)
{
  std::cout << "U: " << u->key << " V: " << v->key << std::endl;
  if(u->parent == NIL)
  {
    std::cout << "V Root: " << v->key << std::endl;
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
  }
    y->left = x;
    x->parent = y;
}

void RBTree :: rightRotate(TreeNode* x)
{
  std::cout << "Right Roate " << x->key << std::endl;
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
  }
  y->right = x;
  x->parent = y;
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
    if(x->color == RED)
    {
      std::cout << "R[" << x->key << "] ";
    }
    else
    {
      std::cout << "B[" << x->key << "] ";
    }
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
  std::cout << z->key << std::endl;
  TreeNode* y;
  while (z->parent->color == RED)
  {
    if(z->parent == z->parent->parent->left)
    {
      std::cout << "TEST 1" << std::endl;
      y = z->parent->parent->right;
      if(y->color == RED)
      {
        std::cout << "TEST 2" << std::endl;
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->right)
        {
          std::cout << "TEST Left" << std::endl;
          z = z->parent;
          leftRotate(z);
        }
        std::cout << "TEST Right" << std::endl;
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(z->parent->parent);
      }
    }
    else
    {
      y = z->parent->parent->left;
      if(y->color == RED)
      {
        std::cout << "TEST 2" << std::endl;
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->left)
        {
          std::cout << "TEST Left2" << std::endl;
          z = z->parent;
          rightRotate(z);
        }
        else
        {
          std::cout << "TEST Right2" << std::endl;
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
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
      std::cout << "DELETING " << root->key << std::endl;
      print();
      deleteNode(root);
    }
  }
  else
  {
    delete NIL;
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

void RBTree :: getChildren(int n)
{
  TreeNode* z = search(root, n);
  std::cout << "Right " << z->right->key << std::endl;
  std::cout << "Left " << z->left->key << std::endl;
}

RBTree :: ~RBTree()
{
  while(root != NIL)
  {
    deleteNode(root);
  }
  delete NIL;
}
