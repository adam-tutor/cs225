/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
      return true;
    }
    if(second[curDim] < first[curDim]){
      return false;
    }
    if(first[curDim] == second[curDim]){
      return first < second;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int dist_potential = 0;
    int dist_currentBest = 0;
    for(int i = 0; i<Dim; i++){
      dist_potential += pow((target[i]-potential[i]), 2.0); //This is equal to the sum of all targets - potentials squared like in the equation given
      dist_currentBest += pow((target[i]-currentBest[i]), 2.0); //This is equal to the sum of all targets - currentBests squared like in the equation given
    }
    dist_potential = sqrt(dist_potential); //After all of the differences are summed together, we take the square root to determine distance
    dist_currentBest = sqrt(dist_currentBest); //After all of the differences are summed together, we take the square root to determine distance
    if(dist_potential < dist_currentBest){ //Just like the previous function, smallerDimVal, we compare the two
      return true;
    }
    if(dist_potential > dist_currentBest){
      return false;
    }
    if(dist_potential == dist_currentBest){
      return (potential < currentBest); //Tie breaker
    }

     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>> newPoints_ = newPoints;
    root = buildTree(newPoints_, 0, 0, newPoints_.size() - 1, root);
    size = newPoints.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != NULL){
    destroy(this->root);
  }
  root = copy(rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  /*if(root!=NULL){
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = NULL;
  }
  size = 0;*/
  destroy(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* current_node){
  if(current_node!=NULL){
    return NULL;
  }
  KDTreeNode* copy_root = new KDTreeNode(current_node->point);
  if(current_node->left == NULL && current_node->right == NULL){
    return copy_root;
  }
  copy_root->left = copy(current_node->left);
  copy_root->right = copy(current_node->right);
  return copy_root;
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* current_node){
  /*if(current_node == NULL){
    return;
  }

  if(current_node->left != NULL){
    destroy(current_node->left); //The recursive calls travel to the bottom of the tree and start deleting from the leaves
  }
  if(current_node->right != NULL){
    destroy(current_node->right);
  }
  
  
  delete current_node;
  current_node = NULL;*/

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    return findNearest(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(const Point<Dim>& query, int dim, KDTreeNode* curRoot) const{
  bool flag;
  Point<Dim> currentBest = curRoot->point;
  if(curRoot->left == NULL && curRoot->right == NULL){
    return curRoot->point;
  }
  /*if(curRoot == NULL){
    return Point<Dim>();
  }*/
  
  if(smallerDimVal(query, curRoot->point, dim)){
    if(curRoot->left!=NULL){
      flag = true;
      currentBest = findNearest(query, (dim+1)%Dim, curRoot->left);
    }
    if(curRoot->left==NULL){
      flag = true;
      currentBest = findNearest(query, (dim+1)%Dim, curRoot->right);
    }
  }
  else{
    if(curRoot->right!=NULL){
      flag = false;
      currentBest = findNearest(query, (dim+1)%Dim, curRoot->right);
    }
    if(curRoot->right==NULL){
      flag = false;
      currentBest = findNearest(query, (dim+1)%Dim, curRoot->left);
    }
  }
  if(shouldReplace(query, currentBest, curRoot->point)){
      currentBest = curRoot->point;
  }
  double radius = 0;
  for(int i = 0; i < Dim; i++){
    radius = radius + pow((currentBest[i] - query[i]), 2.0);
  }
      //radius = std::sqrt(radius);
  double radius_comparison = pow((query[dim] - curRoot->point[dim]), 2.0);
      //double radius_comparison = std::abs(query[dim] - curRoot->point[dim]);
  Point<Dim> tempNearest;
  if(radius_comparison <= radius){
      if(curRoot->right != NULL && flag == true){
        tempNearest = findNearest(query, (dim+1)%Dim, curRoot->right);
      }
      if(curRoot->left != NULL && flag == false){
        tempNearest = findNearest(query, (dim+1)%Dim, curRoot->left);
      }
      if(shouldReplace(query, currentBest, tempNearest)){
        currentBest = tempNearest;
      }
    }
  return currentBest;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints_, int dim, int left, int right, KDTreeNode* curRoot){
  /**
   * @todo Implement this function!
   */
  if(newPoints_.empty()){
    return NULL;
  }
  if(left > right || left < 0 || right < 0){
    return NULL;
  }

  if(left <= right){
    
    int middle = (left + right)/2;
    Point<Dim> selection = quickSelect(newPoints_, left, right, dim, middle);
    curRoot = new KDTreeNode(selection);
    size+=1;
    curRoot->left = buildTree(newPoints_, (dim+1)%Dim, left, middle-1, curRoot->left);
    curRoot->right = buildTree(newPoints_, (dim+1)%Dim, middle+1, right, curRoot->right);
  }
  return curRoot;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& newPoints_, int left, int right, int dim, unsigned int k){
    if(left == right){
      return newPoints_[left];
    }
    unsigned int pivotIndex = k;
    pivotIndex = partition(newPoints_, left, right, dim, pivotIndex);
    if(pivotIndex == k){
      return newPoints_[k];
    }
    else if(k < pivotIndex){
      right = pivotIndex - 1;
      return quickSelect(newPoints_, left, right, dim, k);
    }
    left = pivotIndex + 1;
    return quickSelect(newPoints_, left, right, dim, k);
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints_, int left, int right, int dim, unsigned int pivotIndex){
  Point<Dim> pivotValue = newPoints_[pivotIndex];
  std::swap(newPoints_[pivotIndex], newPoints_[right]);
  int storeIndex = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(newPoints_[i], pivotValue, dim)){
      std::swap(newPoints_[storeIndex], newPoints_[i]);
      storeIndex++;
    }
  }
  std::swap(newPoints_[right], newPoints_[storeIndex]);
  return storeIndex;
}