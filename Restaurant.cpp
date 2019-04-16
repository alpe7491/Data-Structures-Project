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

  cout << "Welcome to " << restaurantName << "! We open at 16:00 every day. It is currently " ;
  clock.printTime(); cout << endl;

}

//Destructor
Restaurant::~Restaurant()
{
  endOfNight();
  cout << restaurantName << " is now closed for business." << endl;
}

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
bool Restaurant::seatGroup()
{

}

// int main()
// {
//   cout << "Hello World" << endl;
//   Restaurant restaurant;
//   return 0;
// }
