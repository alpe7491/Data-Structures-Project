#include <iostream>
#include "Restaurant.hpp"
#include "Time.hpp"
//#include "PriorityQueue.hpp"

int main()
{
  string input;
  cout << "Welcome! You are now the proud owner of a restaurant!" << endl;
  cout << "What would you like to name your new restaurant?" << endl;
  getline(cin, input);
  Restaurant restaurant;
  restaurant.restaurantName = input;
  cout << "the name is: " << restaurant.restaurantName << endl;
}
