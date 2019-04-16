#include "mainClass.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;

Main::Main() {
}

Main::Main(string filename) {
  // fstream input;
  // input.open(filename);
  // string line;
  // while (getline(cin, line)) {
  // input the information to the database.
  // assume there is a class CSCI 2270 from 15:00~15:50 Mon, Wed, Fri
  string name = "CSCI";
  Level* newL = new Level("2270");
  Time* newT = new Time("15001550", "", "15001550", "", "15001550");
  Classes* newClass = new Classes(name, newL->level, newT);
  map<string, Level*>::iterator i;
  // if (i == data.end()) {
  Level* fourLevels = new Level[4];
  data.insert(pair<string, Level*>(name, fourLevels));
  i = data.find(name);
  i->second[0].level = "1000";
  i->second[1].level = "2000";
  i->second[2].level = "3000";
  i->second[3].level = "4000";
  // }
  i->second[stoi(newL->level) / 1000 - 1].classes.push_back(newClass);
  // }
  // i = data.find(name);
  vector<Classes*>::iterator j;
  for (j = i->second[1].classes.begin(); j != i->second[1].classes.end(); j++) {
    cout << i->first << " => " << i->second[1].level << ": " << (*j)->name << (*j)->level << endl;
  }
}

Main::~Main() {
}