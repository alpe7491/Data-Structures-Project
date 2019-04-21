#include <iostream>
#include "Time.hpp"
#include "PriorityQueue.hpp"
#include "Restaurant.hpp"
#include <iomanip>
using namespace std;


// HELPER FUNCTIONS (NOT IN CLASS)
bool inputValidate(string input, int min, int max)
{
  if(input == "") return false;
  for(int i=0; i<input.length(); i++)
  {
    if(isdigit(input[i]) == false) return false;
  }
  if(stoi(input)<min || stoi(input)>max) return false;
  else return true;
}

void printFoodMenu(string name)
{
  cout << name << ", what would you like to order?" << endl;
  cout << "1. Soup - $4.50" << endl;
  cout << "2. Salad - $4.00" << endl;
  cout << "3. Chicken - $6.00" << endl;
  cout << "4. Steak - $8.00" << endl;
  cout << "5. Fish - $8.50" << endl;
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
  food[0].cost = 2.00;
  food[1].cost = 2.50;
  food[2].cost = 4.00;
  food[3].cost = 5.00;
  food[4].cost = 5.50;
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
  if(fullTables==0) cout << "There are currently no customers seated." << endl;
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
  // cout << "all groups seated" << endl << endl;
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
// all customers currently seated are allowed to finish, pay their bills, and leave
// all customers who have not yet been seated must leave
// the user is asked if they would like to buy more food for the next day, and if yes, buyFood() is called
void Restaurant::endOfNight()
{
  string input;
  cout << restaurantName << " is closing for the night -- ";
  clock.printTime();
  clock.addTime(60);
  payBills();
  waitList.clearQue();
  checkInventory();
  nightlyProfit = 0;
  cout << "Would you like to buy more food for tomorrow? (Y/N)";
  getline(cin, input);
  cout << endl;
  if(input=="Y" || input=="y" || input=="yes" || input=="Yes" || input=="YES") buyFood();
  clock.startNewDay();
  cout << "It is now ";
  clock.printTime();
  cout << endl;
}

// checks to see if it is time for any patrons to leave. If so, they pay their bill and vacaate their table
void Restaurant::payBills()
{
  while(fullTables!=0 && fullTables->leaveTime.getTime()<=clock.getTime())
  {
    payBill(fullTables);
  }
  cout << endl;
}

// PRIVATE CLASS FUNCTIONS

// takes a table pointer. Adds bill from that table to total profit, frees memory for group seated there
// moves table from full list to empty list
void Restaurant::payBill(Table* table)
{
  cout << table->group->groupName << ", thank you for eating with us today! Your bill is $" << table->bill << endl;
  nightlyProfit+=table->bill;
  totalProfit+=table->bill;
  table->bill = 0;
  delete table->group;
  table->group = 0;
  fullTables = table->next;
  emptyTables = insertEmptyTable(table, emptyTables);
}


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
  cout << "Currently seating " << group->groupName << " at table #" << current->tableNumber << endl;
  current->group = group;
  current->leaveTime = checkClock();
  current->leaveTime.addTime(45);
  if(previous==0) emptyTables = current->next;
  else previous->next = current->next;
  fullTables = insertFullTable(current, fullTables);
  takeOrder(current);
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

// seated parties will order food, this will use food count and add to their bill
void Restaurant::takeOrder(Table* table){
  string input;
  float tableBill;
  printFoodMenu(table->group->groupName);
  for(int i=0; i<table->group->groupSize; i++)
  {
    do {
      cout << "Person " << i+1 << ": ";
      getline(cin, input);
    } while(!inputValidate(input,1,5));
    cout << food[stoi(input)-1].name << endl;
    food[stoi(input)-1].inventory--;
    tableBill = tableBill + food[stoi(input)-1].price;
  }
  table->bill = tableBill;
  cout << endl;
}

// called at the end of each day, allows management to order more food if/when the restaurant runs out
// takes user input, changes food inventory and total profit
void Restaurant::buyFood()
{
  string input;
  string amount;
  do {
    cout << "You have $" << fixed << setprecision(2) << totalProfit << ". What would you like to buy more of?" << endl;
    cout << "1. Soup - $2.00 (You currently have " << food[0].inventory << ")"<< endl;
    cout << "2. Salad - $2.50 (You currently have " << food[1].inventory << ")"<< endl;
    cout << "3. Chicken - $4.00 (You currently have " << food[2].inventory << ")"<< endl;
    cout << "4. Steak - $5.00 (You currently have " << food[3].inventory << ")"<< endl;
    cout << "5. Fish - $5.50 (You currently have " << food[4].inventory << ")"<< endl;
    cout << "6. I am done buying food." << endl;
    getline(cin,input);
    if(inputValidate(input,1,5))
    {
      cout << "How much " << food[stoi(input)-1].name << " would you like to buy? ";
      getline(cin, amount);
      if(inputValidate(amount,0,10000) && stoi(amount)*food[stoi(input)-1].cost < totalProfit)
      {
        // cout <<  food[stoi(input)-1].name << ": " << food[stoi(input)-1].inventory << ", $" << totalProfit << endl;
        food[stoi(input)-1].inventory += stoi(amount);
        totalProfit -= stoi(amount)*food[stoi(input)-1].cost;
        // cout <<  food[stoi(input)-1].name << ": " << food[stoi(input)-1].inventory << ", $" << totalProfit << endl;
      }
      else cout << "Cannot purchase. Either you did not enter a valid number, or you do not have enough money." << endl;
    }
  } while(input!="6");
  cout << endl;
}
