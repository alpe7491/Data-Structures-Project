#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include <iostream>
#include "Time.hpp"
// #include "PriorityQueue.hpp"
using namespace std;

struct Food
{
  string name;
  int inventory;
  float price;
};

struct Table
{
  int tableNumber;
  int size;
  // GroupNode* group;
};

class Restaurant
{
  public:

    Restaurant(string);
    ~Restaurant();
    void addTime(int);
    void seatGroups();
    void takeOrders();
    float getProfit();
    float getTotalProfit();
    Time checkClock();

  private:
    string restaurantName;
    Time clock;
    // PriorityQueue waitList;
    int nightlyProfit = 0;
    int totalProfit = 0;
    Food food[5];

    void endOfNight();
    bool seatGroup();
    bool takeOrder();
};

#endif
