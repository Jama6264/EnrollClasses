#include "mainClass.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Main::Main() {}

Main::Main(string filename) {
  ifstream input;
  input.open(filename);
  string line;
  while (getline(input, line)) {
    string n, l, t, d;  // name, level, time, day of the week
    stringstream ss;
    ss << line;
    getline(ss, n, ' ');
    getline(ss, l, ' ');
    getline(ss, t, ' ');
    getline(ss, d);

    map<string, Level**>::iterator i = data.find(n);
    if (i == data.end()) {
      Level** fourLevels = new Level*[4];
      fourLevels[0] = new Level("1000");
      fourLevels[1] = new Level("2000");
      fourLevels[2] = new Level("3000");
      fourLevels[3] = new Level("4000");
      data.insert(pair<string, Level**>(n, fourLevels));
    }
    Time* newT = new Time(t, d);
    i = data.find(n);
    map<string, Classes*>::iterator m = i->second[stoi(l) / 1000 - 1]->classes.find(l);
    if (m == i->second[stoi(l) / 1000 - 1]->classes.end()) {
      Classes* newClass = new Classes(n, newT);
      i->second[stoi(l) / 1000 - 1]->classes.insert(pair<string, Classes*>(l, newClass));
    } else {
      m->second->times.push_back(newT);
    }
  }
  input.close();
}

Main::~Main() {
  data.clear();
}

void Main::printAll() {
  map<string, Level**>::iterator i;
  map<string, Classes*>::iterator j;
  for (i = data.begin(); i != data.end(); i++) {
    for (int k = 0; k < 4; k++) {
      if (!i->second[k]->classes.empty()) {
        cout << i->first << " => " << i->second[k]->level << ": " << endl;
        vector<Time*>::iterator t;
        for (j = i->second[k]->classes.begin(); j != i->second[k]->classes.end(); j++) {
          cout << (*j).second->name << (*j).first;
          for (t = (*j).second->times.begin(); t != (*j).second->times.end(); t++) {
            cout << " " << (*t)->d << " " << (*t)->t;
          }
          cout << endl;
        }
        cout << endl;
      }
    }
  }
}
