#include <iostream>
#include <string>
#include "Time.hpp"
using namespace std;


// I actually think we should have a non-parameterized constructor.
// I just didn't know what to set as the default values yet.
Time::Time()
{
  setTime(START_DAY, OPEN_TIME, 0);
}

Time::~Time()
{

}

void Time::addTime(int numMins)
{
  for(int i=0; i<numMins; i++)
  {
    addOneMinute();
  }
}

void Time::startNewDay()
{
  if(day=="Mon") day = "Tue";
  else if(day=="Tue") day="Wed";
  else if(day=="Wed") day="Thu";
  else if(day=="Thu") day="Fri";
  else if(day=="Fri") day="Sat";
  else if(day=="Sat") day="Sun";
  else day="Mon";
  hour = OPEN_TIME;
  minute = 0;
}

string Time::getTime()
{
  string zero = "0";
  string _hour = to_string(hour);
  if(hour<10) _hour = zero+_hour;
  string _minute = to_string(minute);
  if(minute<10) _minute = zero+_minute;
  string colon = ":";
  return _hour+colon+_minute;
}

string Time::getDay()
{
  return day;
}

void Time::addOneMinute()
{
  if(minute==59)
  {
    addOneHour();
    minute = 0;
  }
  else
  {
    minute++;
  }
}

void Time::addOneHour()
{
  if(hour==CLOSING_TIME)
  {
    startNewDay();
    hour = 0;
  }
  else
  {
    hour++;
  }
}

void Time::setTime(string _day, int _hour, int _minute)
{
  day = _day;
  hour = _hour;
  minute = _minute;
}

void Time::printTime()
{
  cout << getDay() << " " << getTime() << endl;
}

// main function with test cases below to prove that all functions work

// int main()
// {
//   Time time1;
//   Time time2;
//   time2.addTime(30);
//   if(time1.getTime()==time2.getTime())
//   {
//     cout << "Times are equal" << endl;
//   }
//   else cout <<"Times are not equal" << endl;
//   return 0;
// }

// int main()
// {
//   Time time;
//   time.printTime();
//   time.startNewDay();
//   time.addTime(45);
//   time.printTime();
//   time.addTime(30);
//   time.printTime();
//   return 0;
// }
