#ifndef MAINCLASS_HPP
#define MAINCLASS_HPP
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct InputClass {
  string prefix, number;

  InputClass(string p, string n) {
    prefix = p;
    number = n;
  }
};

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

struct Schedule {
  string name, level;
  Schedule* next;
  vector<Time*> times;
  bool visited;

  Schedule(string n, string l, vector<Time*> t) {
    name = n;
    level = l;
    times = t;
    next = NULL;
  }
};

class Main {
 public:
  Main();
  Main(string);
  ~Main();
  void printAll();
  bool readInput(vector<InputClass>);
  void inputEdges();
  void computeSchedule(int);

 private:
  map<string, Level**> data;
  vector<Schedule*> schedules;
  map<string, set<int>> slot;
  vector<string> option;
  void helper(Schedule*, int, int&);
};

#endif
