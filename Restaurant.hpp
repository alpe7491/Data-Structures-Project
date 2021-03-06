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
  float cost;
};

struct Table
{
  int tableNumber;
  int size;
  Time leaveTime; //only relevant if the table has a group at it
  float bill = 0; //add to profit and reset to 0 every time a group leaves
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
    void printCurrentlySeated();
    void addToWaitList(string groupName, int groupSize, Time arrivalTime, bool reservation);
    void payBills();

  private:
    string restaurantName;
    Time clock;
    PriorityQueue waitList = PriorityQueue(20);
    int nightlyProfit = 0;
    int totalProfit = 0;
    Food food[5];
    Table* fullTables = 0;
    Table* emptyTables = 0;

    bool seatGroup(GroupNode* group);
    void takeOrder(Table* table);
    void addNewTable(int tableNumber, int size);
    void payBill(Table* table);
    void buyFood();
};

#endif
