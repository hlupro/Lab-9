//Hunter Lupro
//lab9
//April 9th, 2020

#include "RBTree.h"

RBTree :: RBTree()
{
  root = NIL;
}

//Takes in a TreeNode that acts as the root and searches for a
//node with the value k returns the node if found and NIL if not found
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

//Finds and returns the minimum of the tree
RBTree :: TreeNode* RBTree :: minimum(TreeNode* x)
{
  while (x->left != NIL)
  {
    x = x->left;
  }
  return x;
}

//Finds and returns the maximum of the tree
RBTree :: TreeNode* RBTree :: maximum(TreeNode* x)
{
  while(x->right != NIL)
  {
    x = x->right;
  }
  return x;
}

//Takes in a node and finds the node the smallest value node greater
//than itself in the tree
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

//Deletes the node  z from the tree
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
  }
  if(original == BLACK)
  {
    deleteFixup(x);
  }
  delete z;
}

//Called after deleting a node and fixes the red-black to follow
//all the rules that might have been broken by delete
void RBTree :: deleteFixup(TreeNode* x)
{
  if(x == NIL)
  {
  }
  TreeNode* w;
  while (x != root && x->color == BLACK)
  {
    if(x == x->parent->left)
    {
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
      w = x->parent->left;
      if(w->color == RED)
      {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if(w->left->color == BLACK && w->right->color == BLACK)
      {
        w->color = RED;
        x = x->parent;
      }
      else
      {
        if(w->left->color == BLACK)
        {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(w);
          w = x->parent->left;
        }
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

//Transplant replaces the subtree at node u with the subtree at node v
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

//leftRotate pivots around the the node x and its right child. altering the tree to where
//the node x becomes the left child of its right child and the right child is now the parent.
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

//rightRotate pivots around the the node x and its left child. altering the tree to where
//the node x becomes the left child of its left child and the left child is now the parent.
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
  }
  y->right = x;
  x->parent = y;
}

//Caclulates the height of the tree by recursively computing the height of the left and right Tree
// and taking the max of the two
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

//Prints all the nodes of the tree at level l
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

//Prints the nodes of the tree inorder
void RBTree :: inorder(TreeNode* x)
{
  if(x != NIL)
  {
    inorder(x->left);
    std::cout << x->key << " ";
    inorder(x->right);
  }
}

//Creates a new node based on the int n and inserts it into the tree
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

//Insert fixup fixes the RebBlack Tree so it fits all the RB tree properties that
//might have been broken after inserting
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
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->right)
        {
          z = z->parent;
          leftRotate(z);
        }
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
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->left)
        {
          z = z->parent;
          rightRotate(z);
        }
        else
        {
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
  }
  root->color = BLACK;
}

//getSearch handles all the print functions to test the search function
void RBTree :: getSearch(int k)
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

//Used for timing where no print statements are needed
void RBTree :: timeSearch(int k)
{
  search(root, k);
}

//Returns the min after calling the private function minimum
void RBTree :: getMin()
{
  std::cout << "The minimum is " << minimum(root)->key << ".\n" << std::endl;
}

//Returns the max after calling the private function maximum
void RBTree :: getMax()
{
  std::cout << "The maximum is " << maximum(root)->key << ".\n" << std::endl;
}

//Returns the root of the tree
RBTree ::TreeNode* RBTree :: getRoot()
{
  return root;
}

//Print messages for the sucessor private function
void RBTree :: getSucessor(int k)
{
  std::cout << "\nLooking for the sucessor of " << k << std::endl;
  TreeNode* y = search(root,k);
  if(y != NIL)
  {
    TreeNode* z = sucessor(y);
    if(sucessor(search(root,k)) != NIL)
    {
      std::cout << "The sucessor of " << k << " is " << z->key << ".\n" << std::endl;
    }
    else
    {
      std::cout << k << " is the largest node in the tree and has no sucessor." << "\n" << std::endl;
    }
  }
  else
  {
    std::cout << "Error.\n" << k << " does not exist in the tree and therefore a sucessor will not be found." << "\n" << std::endl;
  }
}

//Used to call the private function from the main
void RBTree :: printInorder()
{
  inorder(root);
  std::cout << "\n" << std::endl;
}

//Delete function used to delete the entire tree
void RBTree :: deleteTree()
{
  if(root != NIL)
  {
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

//This function deletes the static TreeNode* NIL
void RBTree :: deleteNIL()
{
  delete NIL;
}

//Handles the print statements for testing, first searchs to see if node is in tree
//if it is it calles delete Node so it is delete.
void RBTree :: getDelete(int k)
{
  std::cout << "\nDeleting the node with the key " << k << std::endl;
  TreeNode* y = search(root, k);
  if(y != NIL)
  {
    std::cout << "Deleting " << k << " from the tree." << "\n" << std::endl;
    deleteNode(y);
  }
  else
  {
    std::cout << "Error.\n" << k << " does not exist in the tree and therefore cannot be deleted." << "\n" <<std::endl;
  }
}

//Prints the Tree
void RBTree :: print()
{
  if(root == NIL)
  {
    std::cout << "\nThe tree is now empty.\n" << std::endl;
  }
  else
  {
    int h = getHeight(root);
    for(int i = 1; i <= h; i++)
    {
      std::cout <<"\n";
      printLevel(root, i);
      std::cout << "\n";
    }
    std::cout<<"\n";
  }
}

//Deconstructor for RBTree that uses the deletenode function.
RBTree :: ~RBTree()
{
  while(root != NIL)
  {
    deleteNode(root);
  }
}
