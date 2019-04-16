#include <iostream>
#include "Time.hpp"
// #include "PriorityQueue.hpp"
#include "Restaurant.hpp"
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
void printTurnMenu(Time clock)
{
  cout << "It is " << clock.getTime() << ". What would you like to do?" << endl;
  cout << "1. Add a new group of customers" << endl;
  cout << "2. Continue" << endl;
  cout << "3. Close for the night" << endl;
  cout << "4. Quit" << endl;
}


// PUBLIC CLASS FUNCTIONS
Restaurant::Restaurant()
{
  // initialize the menu
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
  clock.printTime();

}
Restaurant::~Restaurant()
{

}
void Restaurant::addTime(int)
{

}
void Restaurant::seatGroups()
{

}

// PRIVATE CLASS FUNCTIONS
void Restaurant::endOfNight()
{

}
bool Restaurant::seatGroup()
{

}

// int main()
// {
//   cout << "Hello World" << endl;
//   Restaurant restaurant;
//   return 0;
// }
