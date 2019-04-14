#include "PriorityQueue.hpp"
#include <iostream>
#include <string>

using namespace std;

// Public

//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue::PriorityQueue(int queueSize){
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new GroupNode [maxQueueSize];
}
// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue(){
  delete[] priorityQueue;
}
// Purpose: enqueue new group into priority queue; call other
void PriorityQueue::enqueue(std::string _groupName, int _groupSize, int _cookingTime){
  if(isFull())
  {
    cout << "Heap full, cannot enqueue" << endl;
    return;
  }
  else
  {
    currentQueueSize++;
    int index = currentQueueSize-1;
    priorityQueue[index].groupName = _groupName;
    priorityQueue[index].groupSize = _groupSize;
    priorityQueue[index].cookingTime = _cookingTime;
  }
  repairUpward(currentQueueSize-1);
}
//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue::dequeue(){
  if(isEmpty())
  {
    cout << "Heap empty, cannot dequeue" << endl;
    return;
  }
  else
  {
    currentQueueSize--;
    int index = currentQueueSize;
    priorityQueue[0] = priorityQueue[index];
    priorityQueue[index].groupName = "";
    priorityQueue[index].groupSize = 0;
    priorityQueue[index].cookingTime = 0;
  }
  repairDownward(0);
}
// return: groupID of the group at the front of the priority queue
GroupNode PriorityQueue::peek(){
  if(isEmpty())
  {
    GroupNode empty;
    empty.groupName = "";
    empty.groupSize = 0;
    empty.cookingTime = 0;
    cout << "Heap empty, nothing to peek" << endl;
    return empty;
  }
  else
  {
    return priorityQueue[0];
  }
}
//return: true if queue is full, false otherwise
bool PriorityQueue::isFull(){
  if(currentQueueSize == maxQueueSize)
  {
    return true;
  }
  else
  {
    return false;
  }
}
// return: true if queue is empty, false otherwise
bool PriorityQueue::isEmpty(){
  if(currentQueueSize == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Private

// Helper: check priority
bool checkPriority(GroupNode parent, GroupNode child){ //return true for parent, flase for child
  if(parent.groupSize < child.groupSize){
    return true;
  }
  if(parent.groupSize == child.groupSize){
    if(parent.cookingTime < child.cookingTime){
      return true;
    }
    return false;
  }
  return false;
}
//Purpose: maintain heap properties by swapping node with parent if necessary
void PriorityQueue::repairUpward(int nodeIndex){
  int parent = (nodeIndex-1)/2;
  while(nodeIndex != 0 && !checkPriority(priorityQueue[parent], priorityQueue[nodeIndex])){
    swap(priorityQueue[nodeIndex], priorityQueue[parent]);
    nodeIndex = (nodeIndex-1)/2;
    parent = (nodeIndex-1)/2;
  }
}
// Helper: swap nodes in a que
void swap(GroupNode &x, GroupNode &y){
  GroupNode temp = x;
  x = y;
  y = temp;
}

// Purpose: maintain heap properties by swapping node with child if necessary
void PriorityQueue::repairDownward(int nodeIndex){
  int leftChild = (2*nodeIndex+1);
  int rightChild = (2*nodeIndex+2);
  int smallest = nodeIndex;

  if(leftChild < currentQueueSize && !checkPriority(priorityQueue[nodeIndex], priorityQueue[leftChild])){
    smallest = leftChild;
  }
  if(rightChild < currentQueueSize && !checkPriority(priorityQueue[smallest], priorityQueue[rightChild])){
    smallest = rightChild;
  }
  if(smallest != nodeIndex){
    swap(priorityQueue[nodeIndex], priorityQueue[smallest]);
    repairDownward(smallest);
  }
}

// Purpose: calculate how long a parties order will take to cook
int PriorityQueue::calcCookTime(string order[]){
  int cookTime = 0;
  for (int i=0; i<groupSize; i++){
    if(order[i] == "Steak"){
      cookTime = cookTime + 5;
    }
    else if(order[i] == "Chicken"){
      cookTime = cookTime + 2;
    }
    else if(order[i] == "Pork"){
      cookTime = cookTime + 4;
    }
    else if(order[i] == "Soup"){
      cookTime = cookTime + 1;
    }
    else if(order[i] == "Salad"){
      cookTime = cookTime + 1;
    }
  }
}
