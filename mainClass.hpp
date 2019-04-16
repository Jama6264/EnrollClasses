#ifndef MAINCLASS_HPP
#define MAINCLASS_HPP
#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

struct Time {
  string mon, tues, wed, thurs, fri;

  Time(string m, string t, string w, string th, string f) {
    mon = m;
    tues = t;
    wed = w;
    thurs = th;
    fri = f;
  }
};

struct Classes {
  string name;
  string level;
  vector<Time*> times;

  Classes(string n, string l, Time* t) {
    name = n;
    level = l;
    times.push_back(t);
  }
  Classes(Time* t) {
    times.push_back(t);
  }
};

struct Level {
  string level;
  vector<Classes*> classes;

  Level(){};
  Level(string l) {
    level = l;
  }
};

class Main {
 public:
  Main();
  Main(string);
  ~Main();

 private:
  map<string, Level*> data;
};

#endif