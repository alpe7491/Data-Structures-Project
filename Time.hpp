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
    bool addTime(int numMins);
    bool subtractTime(int numMins);
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

const int OPEN_TIME = 16;
const string START_DAY = "Sun";

#endif
