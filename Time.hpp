#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>
#include <string>
using namespace std;

class Time
{
  public:
    Time();
    ~Time();
    void addTime(int numMins);
    void startNewDay();
    string getTime();
    string getDay();
    void printTime();
  private:
    void addOneMinute();
    void addOneHour();
    void setTime(string day, int hour, int minute);
    string day;
    int hour;
    int minute;
};

const int CLOSING_TIME = 23;
const int OPEN_TIME = 16;
const string START_DAY = "Sun";

#endif
