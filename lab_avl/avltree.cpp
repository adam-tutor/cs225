/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}
//helper function to find the tree's height
template <class K, class V>
void AVLTree<K, V>::heightFinder(Node*& subroot){
  subroot->height = (1 + std::max(heightOrNeg1(subroot->left), heightOrNeg1(subroot->right)));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    heightFinder(t);
    t = temp;
    heightFinder(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    heightFinder(t);
    t = temp;
    heightFinder(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL){
      return;
    }
    
    int balance = balanceFinder(subtree);
    
    if (balance == 2){
      int bal_r = balanceFinder(subtree->right);
      if(bal_r <= 0){
        rotateRightLeft(subtree); //elbow case
      }
      else{
        rotateLeft(subtree);
        //stick case
      }
    }
    else if(balance == -2){
      int bal_l = balanceFinder(subtree->left);
      if(bal_l >= 0){
        rotateLeftRight(subtree); //elbow case
      }
      else{
        rotateRight(subtree); 
        //stick case
      }
    }
}
//helper function to find the subtree's balance
template <class K, class V>
int AVLTree<K, V>::balanceFinder(Node*& subtree){
  if(subtree == NULL){
    return 0;
  }
  return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key, value);
    }
    else if(key<subtree->key){
      insert(subtree->left, key, value);
    }
    else if(key>subtree->key){
      insert(subtree->right, key, value);
    }
    else if(key == subtree->key){
      subtree->value = value;
      return;
    }
    rebalance(subtree);
    heightFinder(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* pr = subtree->left;
            while(pr->right != NULL){
              pr = pr->right;
            }
            subtree->key = pr->key;
            subtree->value = pr->value;
            remove(subtree->left, pr->key);
        } else {
            /* one-child remove */
            // your code here
            if(!subtree->left && subtree->right){
              Node* temptree = subtree;
              subtree = subtree->right;
              delete temptree;
            }
            else if(subtree->left && !subtree->right){
              Node* temptree = subtree;
              subtree = subtree->left;
              delete temptree;
            }
        }
        // your code here
    }
    heightFinder(subtree);
    rebalance(subtree);
}
