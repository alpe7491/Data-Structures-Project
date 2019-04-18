#include <iostream>
#include "Time.hpp"
#include "PriorityQueue.hpp"
#include "Restaurant.hpp"
#include <iomanip>
using namespace std;


// HELPER FUNCTIONS (NOT IN CLASS)
void printFoodMenu()
{
  cout << "What would you like to order?" << endl;
  cout << "1. Soup" << endl;
  cout << "2. Salad" << endl;
  cout << "3. Chicken" << endl;
  cout << "4. Steak" << endl;
  cout << "5. Fish" << endl;
}

// sorts a full table into the linked list of full tables based on the time that the guests will leave
// returns first table in the new sorted list
Table* insertFullTable(Table* newTable, Table* linkedList)
{
  Table* current = linkedList;
  Table* previous = 0;
  while(current!=0 && current->leaveTime.getTime()<newTable->leaveTime.getTime())
  {
    previous = current;
    current = current->next;
  }
  newTable->next = current;
  if(previous==0) // if the new table will be the first in the list
  {
    return newTable;
  }
  else
  {
    previous->next = newTable;
    return linkedList;
  }
}

// sorts an empty table in to the linked list of empty tables based on the table size
// returns first table in the new sorted list
Table* insertEmptyTable(Table* newTable, Table* linkedList)
{
  Table* current = linkedList;
  Table* previous = 0;
  while(current!=0 && current->size<newTable->size)
  {
    previous = current;
    current = current->next;
  }
  newTable->next = current;
  if(previous==0) // if the new table will be the first in the list
  {
    return newTable;
  }
  else
  {
    previous->next = newTable;
    return linkedList;
  }
}



// PUBLIC CLASS FUNCTIONS

// Constructor
Restaurant::Restaurant(string name)
{
  restaurantName = name;
  // initialize all the food
  food[0].name = "Soup";
  food[1].name = "Salad";
  food[2].name = "Chicken";
  food[3].name = "Steak";
  food[4].name = "Fish";
  food[0].price = 4.50;
  food[1].price = 4.00;
  food[2].price = 6.00;
  food[3].price = 8.00;
  food[4].price = 8.50;
  food[0].inventory = 100;
  food[1].inventory = 100;
  food[2].inventory = 100;
  food[3].inventory = 100;
  food[4].inventory = 100;
  // initialize all the tables
  addNewTable(1,8);
  addNewTable(2,6);
  addNewTable(3,6);
  addNewTable(4,6);
  addNewTable(5,6);
  addNewTable(6,10);
  addNewTable(7,10);
  addNewTable(8,10);
  addNewTable(9,12);
  addNewTable(10,6);
  addNewTable(11,6);
  addNewTable(12,4);
  addNewTable(13,4);
  addNewTable(14,4);
  addNewTable(15,4);
  addNewTable(16,6);
  addNewTable(17,6);
  addNewTable(18,6);
  addNewTable(19,8);
  addNewTable(20,4);
  addNewTable(21,4);
  addNewTable(22,4);
  addNewTable(23,4);
  addNewTable(24,8);

  cout << "Welcome to " << restaurantName << "! We open at 16:00 every day. It is currently " ;
  clock.printTime(); cout << endl;

}

//Destructor
Restaurant::~Restaurant()
{
  endOfNight();
  cout << restaurantName << " is now closed for business." << endl;
  // delete all memory (empty waitlist, clear tables, delete table nodes)
}

// adds a new customer to the wait list
void Restaurant::addToWaitList(string groupName, int groupSize, Time arrivalTime, bool reservation)
{
  if(waitList.isFull())
  {
    cout << "Wait list is full, cannot add a new group" << endl;
  }
  else
  {
    waitList.enqueue(groupName, groupSize, arrivalTime, reservation);
    cout << groupName << ", you are #" << waitList.getSize() << " on the wait list. You will be seated shortly." << endl << endl;
  }
}

// prints a list of all the full tables
void Restaurant::printCurrentlySeated()
{
  Table* current = fullTables;
  while(current!=0)
  {
    cout << "Table #" << current->tableNumber << ": " << current->group->groupName << " leaving at " << current->leaveTime.getTime() << endl;
    current = current->next;
  }
  cout << "Number of groups waiting to be seated: " << waitList.getSize() << endl << endl;
}

// prints how much food is left and what the current profits are
void Restaurant::checkInventory()
{
  cout << "Inventory:" << endl;
  for(int i=0; i<5; i++)
  {
    cout << "    " << food[i].name << ": " << food[i].inventory;
  }
  cout << endl;
  cout << fixed << setprecision(2) << "Tonight's profit: $" << getProfit() << ", profit so far: $" << getTotalProfit() << endl << endl;
}

// returns clock
Time Restaurant::checkClock()
{
  return clock;
}

// increments time
bool Restaurant::addTime(int numMins)
{
  if(clock.addTime(numMins)) return true;
  else return false;
}

// seats as many groups as possible from the front of the waitlist
void Restaurant::seatGroups()
{
  GroupNode* group = waitList.peek();
  while(group!=0 && seatGroup(group))
  {
    waitList.dequeue();
    group = waitList.peek();
  }
  delete group;
  cout << "all groups seated" << endl << endl;
}

// seated parties will order food, this will use food count and add to their bill
void Restaurant::takeOrders(){
  string indivOrder;
  float tableBill;
  Table* temp = fullTables;
  while(temp != nullptr){
    printFoodMenu();
    for(int i=0; i<temp->size; i++){
      getline(cin, indivOrder);
      for(int j=0; j<5; j++){
        // Assuming user correctly inputs food choice
        if(indivOrder == food[j].name){
          food[j].inventory = food[j].inventory--;
          tableBill = tableBill + food[j].price;
        }
      }
    }
    temp->bill = tableBill;
    temp = temp->next;
  }
}

// returns the profit for the night
float Restaurant::getProfit()
{
  return nightlyProfit;
}

// returns the profit so far
float Restaurant::getTotalProfit()
{
  return totalProfit;
}

// tallies totals for the night and starts the next day
void Restaurant::endOfNight()
{
  cout << restaurantName << " has closed for the night -- ";
  clock.printTime();
  checkInventory();
  clock.startNewDay();
}

// PRIVATE CLASS FUNCTIONS


// seats a single group. If one is successfully seated, will return true so we can try to seat the next one too
bool Restaurant::seatGroup(GroupNode* group)
{
  Table* current = emptyTables;
  Table* previous = 0;
  while(current!=0 && current->size < group->groupSize)
  {
    previous = current;
    current = current->next;
  }
  if(current == 0) return false;
  cout << group->groupName << " will be seated at table #" << current->tableNumber << endl;
  current->group = group;
  current->leaveTime = checkClock();
  current->leaveTime.addTime(45);
  previous->next = current->next;
  fullTables = insertFullTable(current, fullTables);
  return true;
}

// adds a new table, used in restaurant constructor
void Restaurant::addNewTable(int tableNumber, int size)
{
  Table* newTable = new Table;
  newTable->tableNumber = tableNumber;
  newTable->size = size;
  emptyTables = insertEmptyTable(newTable, emptyTables);
}

// int main()
// {
//   cout << "Hello World" << endl;
//   Restaurant restaurant;
//   return 0;
// }
