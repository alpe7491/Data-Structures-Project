#include <iostream>
#include "Restaurant.hpp"
#include "Time.hpp"
#include <string>


// validates user input to make sure that it is an integer between min and max
bool inputValidation(string input, int min, int max)
{
  if(input == "") return false;
  for(int i=0; i<input.length(); i++)
  {
    if(isdigit(input[i]) == false) return false;
  }
  if(stoi(input)<min || stoi(input)>max) return false;
  else return true;
}

// prints the menu at the beginning of every turn so the user can choose what to do
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
  string name;
  string size;
  cout << "You are now the proud owner of a restaurant!" << endl;
  cout << "What would you like to name your new restaurant? ";
  getline(cin, input);
  cout << endl;
  Restaurant restaurant(input);
  do {
    do {
      printTurnMenu(restaurant.checkClock());
      getline(cin,selection);
      cout << endl;
    } while(!inputValidation(selection,1,6));
    switch(stoi(selection))
    {
      case 1: // add new customers
        cout << "Please enter the name of your group: ";
        getline(cin, name);
        do {
          cout << "How big is your group (we accept groups of 1-12 people): ";
          getline(cin,size);
          cout << endl;
        } while(!inputValidation(size,1,12));
        restaurant.addToWaitList(name, stoi(size), restaurant.checkClock(), 0);
        break;
      case 2: // check inventory
        restaurant.checkInventory();
        break;
      case 3: // see who is currently seated
        restaurant.printCurrentlySeated();
        break;
      case 4: // continue, if it passes midnight, the day automatically ends
        if(!restaurant.addTime(15)) restaurant.endOfNight();
        else
        {
          restaurant.payBills();
          restaurant.seatGroups();
        }
        break;
      case 5: // end the day voluntarily
        restaurant.endOfNight();
        break;
      default: // exit the program
        break;
    }
  } while(selection!="6");
  // Restaurant destructor takes care of all of the exit procedures
}
