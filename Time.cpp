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

// adds a number of minutes. Returns true if new time is before midnight, false if after midnight
bool Time::addTime(int numMins)
{
  for(int i=0; i<numMins; i++)
  {
    addOneMinute();
  }
  if(getTime()>="24:00") return false;
  else return true;
}
bool Time::subtractTime(int numMins)
{
  while(numMins>minute)
  {
    hour--;
    numMins-=60;
  }
  minute-=numMins;
  if(getTime()<="00:00") return false;
  else return true;
}

// increments to the next day of the week, starts again at the time the restaurant is set to open
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

// returns a string containg hours:minutes in 24hr time. May be compared to other times to see which is earlier
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

// returns a string with the current day of the week
string Time::getDay()
{
  return day;
}

// adds one minute. Used repeatedly in public addTime() function. Adds an hour if minutes pass 59
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

// adds an hour
void Time::addOneHour()
{
  hour++;
}

// sets time
void Time::setTime(string _day, int _hour, int _minute)
{
  day = _day;
  hour = _hour;
  minute = _minute;
}

// prints day of the week and current time in 24hr hours:minutes format
void Time::printTime()
{
  cout << getDay() << " " << getTime() << endl;
}
