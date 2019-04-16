#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include <iostream>
#include "Time.hpp"
#include "PriorityQueue.hpp"
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
  GroupNode* group = 0;
  Table* next = 0;
};

class Restaurant
{
  public:

    Restaurant(string);
    ~Restaurant();
    bool addTime(int);
    void seatGroups();
    void takeOrders();
    float getProfit();
    float getTotalProfit();
    Time checkClock();
    void checkInventory();
    void endOfNight();

  private:
    string restaurantName;
    Time clock;
    PriorityQueue waitList = PriorityQueue(20);
    int nightlyProfit = 0;
    int totalProfit = 0;
    Food food[5];

    bool seatGroup();
    bool takeOrder();
};

#endif
