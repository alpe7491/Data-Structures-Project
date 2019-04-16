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
  cout << "3. Continue" << endl;
  cout << "4. Close for the night" << endl;
  cout << "5. Quit" << endl;
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
    } while(!inputValidation(selection,1,5));
    switch(stoi(selection))
    {
      case 1:
        cout << "Adding a new customer" << endl;
        break;
      case 2:
        restaurant.checkInventory();
        break;
      case 3:
        if(!restaurant.addTime(15)) restaurant.endOfNight();
        else
        {
          //people pay and leave
          //seat people
          //take orders
          //serve food
        }
        restaurant.checkClock();
        break;
      case 4:
        restaurant.endOfNight();
        break;
      default:
        break;
    }
  } while(selection!="5");

}
