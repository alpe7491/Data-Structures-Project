#include <iostream>
#include "Restaurant.hpp"
#include "Time.hpp"
#include <string>
//#include "PriorityQueue.hpp"

bool inputValidation(string input, int min, int max)
{
  for(int i=0; i<input.length(); i++)
  {
    if(isdigit(input[i]) == false) return false;
  }
  if(stoi(input)<min || stoi(input)>max) return false;
  else return true;
}

void printTurnMenu(Time clock)
{
  cout << "It is " << clock.getTime() << ". What would you like to do?" << endl;
  cout << "1. Add a new group of customers" << endl;
  cout << "2. Check my inventory" << endl;
  cout << "3. See who is currently seated" << endl;
  cout << "4. Continue" << endl;
  cout << "5. Close for the night" << endl;
  cout << "6. Quit" << endl;
}

int main()
{
  string input;
  string selection;
  cout << "You are now the proud owner of a restaurant!" << endl;
  cout << "What would you like to name your new restaurant?" << endl;
  getline(cin, input);
  Restaurant restaurant(input);
  do {
    do {
      printTurnMenu(restaurant.checkClock());
      cin >> selection;
      cout << endl;
    } while(!inputValidation(selection,1,6));
    switch(stoi(selection))
    {
      case 1:
        cout << "Adding a new customer" << endl;
        restaurant.addToWaitList("Charles", 8, restaurant.checkClock(), 0);
        restaurant.addToWaitList("Ray", 8, restaurant.checkClock(), 0);
        restaurant.addToWaitList("Amy", 8, restaurant.checkClock(), 0);
        restaurant.addToWaitList("Jake", 8, restaurant.checkClock(), 0);
        restaurant.addToWaitList("Rosa", 8, restaurant.checkClock(), 0);
        break;
      case 2:
        restaurant.checkInventory();
        break;
      case 3:
        restaurant.printCurrentlySeated();
        break;
      case 4:
        if(!restaurant.addTime(15)) restaurant.endOfNight();
        else
        {
          //people pay and leave
          restaurant.seatGroups();
          //take orders
          restaurant.takeOrders();
          //serve food
        }
        break;
      case 5:
        restaurant.endOfNight();
        break;
      default:
        break;
    }
  } while(selection!="6");

}
