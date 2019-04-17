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
  string level;
  vector<Time*> times;

  Classes(string n, string l, Time* t) {
    name = n;
    level = l;
    times.push_back(t);
  }
};

struct Level {
  string level;
  vector<Classes*> classes;

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
