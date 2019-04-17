#ifndef MAINCLASS_HPP
#define MAINCLASS_HPP
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Time {
  string t, d;

  Time(string T, string D) {
    t = T;
    d = D;
  }
};

struct Classes {
  string name;
  vector<Time*> times;

  Classes(string n, Time* t) {
    name = n;
    times.push_back(t);
  }
};

struct Level {
  string level;
  map<string, Classes*> classes;  // key(first) = level of the class; Classes*(second) represent the other information of the class.

  Level(string l) {
    level = l;
  }
};

class Main {
 public:
  Main();
  Main(string);
  ~Main();
  void printAll();

 private:
  map<string, Level**> data;
};

#endif
