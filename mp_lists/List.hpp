/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL; //Initializes the head and the tail since we will be using them a lot
    ListNode* tail_ = NULL;
    length_=0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); //Changed from original
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL); //Changed from original
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */

template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  int length = this->length_;
  ListNode* current;
  current = this->head_; //We need to go through every node and delete it, otherwise we will have memory leak
  
  ListNode* temp;
  temp = NULL;
  
  
  while(length > 1){
    temp = current->next;
    delete current;
    current = temp;
    length--;
  }
  
  if(length==1){
    current = this->tail_; //The last part of the list is the tail, which we will delete last
    delete current;
  }
  this->head_ = NULL;
  this->tail_ = NULL;
  this->length_ = 0;
  
  current = NULL; //set all of our variables to NULL to completely free up all used memory
  temp = NULL;
  
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * new_node = new ListNode(ndata);
  if(length_ == 0){
    head_ = new_node; //Initializes the head and tail to the new_node we created
    tail_ = new_node;
    length_ = 1; //Starts at the front
    return;
  }
  head_->prev = new_node;
  new_node->next = head_; //Creates a node at the front of the list
  new_node->prev = NULL;
  head_ = new_node;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * new_node = new ListNode(ndata);
  
  if(length_ == 0){
    head_ = new_node;
    tail_ = new_node;
    length_ = 1;
    return;
  }
  tail_->next = new_node; //Moves to the back of the list to insert a node
  //newNode2->next = NULL;
  new_node->prev = tail_;
  tail_ = new_node;
  
  length_++;
  
}

/*template <typename T>
 void List<T>::insertBack(const T & ndata) {
 /// @todo Graded in MP3.1

 */

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  if(splitPoint >= length_){
    return head_;
  }
  if(splitPoint == 0){
    return start;
  }
  if(start == NULL || start->next == NULL){
    return start;
  }
  ListNode* current_node = start; //Sets our current node to the start so we can split it
  int i = 0;
  while(i<splitPoint){
    if(current_node->next != NULL){
      current_node = current_node->next; //We move across the node list and increase the i so we find the middle (split point)
      i++;
    }
    else{
      return start;
    }
  }
  tail_ = current_node->prev;
  current_node->prev->next = NULL;
  current_node->prev = NULL;
  return current_node;
  
  /// @todo Graded in MP3.1

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  
  int triple = (length_/3);
  ListNode * current, *head1, *tail1, *head2, *tail2, *head3, *tail3, *T_head;
  current = head_;
  if(triple<1){
    return;
  }
  if(triple>0){
    head_ = head_->next;
    head_->prev = NULL;
  }
  
  for(int i=0; i<triple; i++){ //This is supposed to be the simple case (didn't come out how I wanted)
    for(int j=0; j<length_; j++){
      if(j==0){
        head1 = current;
      }
      if(j==length_){
        tail1 = current;
      }
      current = current->next;
    }
    for(int k=0; k<length_; k++){
      if(k==0){
        head2 = current;
      }
      if(k==length_){
        tail2 = current;
      }
      current = current->next;
    }
    if(i==0){
      T_head = head2;
      head2->prev = NULL;
    }
  }
  for(int i=0; i<triple; i++){ //This is the basic case
    if(current->prev != NULL){
      current->prev->next = current->next;
      current->next->prev = current->prev;
    }
    else{
      current->next->prev = NULL;
    }
    
    current = current->next;
  }
  
  if(current == NULL){
    tail_ = tail_->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if(startPoint == endPoint || startPoint == NULL || endPoint == NULL){
    return;
  }
  ListNode *current = startPoint;
  ListNode *x = startPoint->prev;
  ListNode *y = endPoint->next;
  ListNode *temp; //We use this temp variable sparingly, but it is so we can flip the order of the list
  
  
  if(x != NULL){
    x->next = endPoint;
  }
  if(y != NULL){
    y->prev = startPoint;
  }
  
  while(current != endPoint){
    current->prev = current->next;
    current->next = y;
    y = current;
    current = current->prev; //We use current to flip all of the elements in the lsit around
  }
  endPoint->prev = startPoint->prev;
  current->next = y;
  endPoint = startPoint;
  startPoint = current;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int length = this->length_;
  ListNode* start = head_;
  ListNode* end = start;
  if(n<=1 || head_ == NULL){
    return;
  }
  
  if(n>= length_){
    reverse(head_, tail_);
    return;
  }

  if(length == 0){
    return;
  }
  ListNode* spoint = this->head_; //I was thinking something like using the starting point and the ending point to reverse the list
  ListNode* epoint; //However, it didn't come out how I wanted and it doesn't work, but it's the best I have :)
  if(n>=length){
    ListNode* epoint = this->tail_;
    reverse(spoint, epoint);
    this->head_ = spoint;
    this->tail_ = epoint;
  }
  else{
    ListNode* epoint = this->head_;
    int index = 0;
    while (index<length/n){
      epoint = spoint;
      for(int i = 0; i<n-1; i++){
        epoint = epoint->next;
      }
      spoint = epoint->next;
      index = index + 1;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* head2;
  if(first->data < second->data){
    head2 = first; //If first is smaller than second, we use first as the head
    first = first->next; 
  }
  else{
    head2 = second; //If second is smaller than first, we use second as the head
    second = second->next;
  }
  if(first == NULL){
    return second;
  }
  if(second == NULL){
    return first;
  }
  if(first == NULL && second == NULL){
    return NULL;
  }
  ListNode* current_node = head2;
  while(first!= NULL && second!= NULL){
    
    if(second->data < first->data){
      current_node->next = second;
      second = second->next;
      second->prev = current_node;
    }
    
    else{
      current_node->next = first;
      first = first->next;
      first->prev = current_node;
    }
    
    current_node = current_node->next;
  }
  return head2;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start->next == NULL){
    return start;
  }
  int splitdist = chainLength/2; //Right in the middle of the chain is where we will split it, so splitdist is the distance to that middle point
  ListNode* second = split(start, splitdist);
  return merge(mergesort(start, splitdist), mergesort(second, (chainLength % 2) + (splitdist)));
}
