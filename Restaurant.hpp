#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include <iostream>
#include "Time.hpp"
// #include "PriorityQueue.hpp"
using namespace std;

class Restaurant
{
  public:
    Restaurant();
    ~Restaurant();
    void addTime(int);

  private:
    Time clock();
    // PriorityQueue seatList;
    // PriorityQueue cookList;
    int profit;
    // Food food[5]

    void endOfNight();
};

#endif
