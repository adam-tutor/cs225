/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
  
  mirror(root);
  return;
}

    template <typename T>
void BinaryTree<T>::mirror(Node* subroot){
  if(subroot->left == NULL && subroot->right == NULL){
    return;
  }
  Node* temp;
  temp = subroot->left;
  subroot->left = subroot->right;
  subroot->right = temp;
  
  if(subroot->left!=NULL){
    mirror(subroot->left);
  }
  if(subroot->right!=NULL){
    mirror(subroot->right);
  }
  return;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> curr(root); //We use the curr variable to iterate over the tree
    typename TreeTraversal<T>::Iterator iterator = curr.begin();
    T prev = (*iterator)->elem; //The prev variable will update after the actual element so we can use them for comparison
    
    ++iterator;
    
    while(iterator != curr.end()){
      if((*iterator)->elem < prev){
        return false;
      }
      prev = (*iterator)->elem;
      ++iterator;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const{
    std::vector<T> treeVector;
    bool flag = true;
    T flag1, flag2; //The flags are to mark our place within the tree vector
    
    isOrderedRecursive(root, treeVector);
    
    flag1 = treeVector.back();
    treeVector.pop_back();
    
    for(unsigned long i = 0; i < treeVector.size(); i++){
      flag2 = treeVector.back();
      treeVector.pop_back(); //Using these two flags, we are checking whether or not the list is ordered since we start from the back and work our way forward
      if(flag1<flag2){
        flag = false;
      }
      flag1 = flag2;
    }
    return flag;
}

template <typename T>
void BinaryTree<T>::isOrderedRecursive(const Node* subRoot, std::vector<T> &treeVector) const{
  if(subRoot == NULL){
    return;
  }
  isOrderedRecursive(subRoot->left, treeVector);
  treeVector.push_back(subRoot->elem); //I tried to use the inOrder function here that was provided, but I couldn't implement it right
  isOrderedRecursive(subRoot->right, treeVector); //Instead I just rewrote it using a recursive call to isOrderedRecursive.
}
