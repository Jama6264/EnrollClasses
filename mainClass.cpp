#include "mainClass.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Main::Main() {
}

Main::Main(string filename) {
  ifstream input;
  input.open(filename);
  string line;
  while (getline(input, line)) {
    string n, l, t, d;
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
    bool flag = false;
    if (!flag) {
      vector<Classes*>::iterator c;
      for (c = i->second[stoi(l) / 1000 - 1]->classes.begin(); c != i->second[stoi(l) / 1000 - 1]->classes.end(); c++) {
        if ((*c)->level == l) {
          (*c)->times.push_back(newT);
          flag = true;
          break;
        }
      }
    }
    if (flag == false) {
      Classes* newClass = new Classes(n, l, newT);
      i->second[stoi(l) / 1000 - 1]->classes.push_back(newClass);
    }
  }
  input.close();
}

Main::~Main() {
}

void Main::printAll() {
  map<string, Level**>::iterator i;
  vector<Classes*>::iterator j;
  for (i = data.begin(); i != data.end(); i++) {
    for (int k = 0; k < 4; k++) {
      if (!i->second[k]->classes.empty()) {
        cout << i->first << " => " << i->second[k]->level << ": " << endl;
        vector<Time*>::iterator t;
        for (j = i->second[k]->classes.begin(); j != i->second[k]->classes.end(); j++) {
          cout << (*j)->name << (*j)->level;
          for (t = (*j)->times.begin(); t != (*j)->times.end(); t++) {
            cout << " " << (*t)->d << " " << (*t)->t;
          }
          cout << endl;
        }
        cout << endl;
      }
    }
  }
}
