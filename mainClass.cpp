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
    string n, l, t, d, day = "";
    stringstream ss;
    ss << line;
    getline(ss, n, ' ');
    getline(ss, l, ' ');
    getline(ss, t, ' ');
    getline(ss, d);

    for (int k = 0; k < d.length(); k++) {
      switch (d[k]) {
        case '1': {
          day += "M";
          break;
        }
        case '2': {
          day += "T";
          break;
        }
        case '3': {
          day += "W";
          break;
        }
        case '4': {
          day += "Th";
          break;
        }
        case '5': {
          day += "F";
          break;
        }
        default: {
          break;
        }
      }
    }

    Time* newT = new Time(t, day);
    Level* newL = new Level(l);
    Classes* newClass = new Classes(n, l, newT);
    map<string, Level**>::iterator i = data.find(n);
    if (i == data.end()) {
      Level** fourLevels = new Level*[4];
      fourLevels[0] = new Level("1000");
      fourLevels[1] = new Level("2000");
      fourLevels[2] = new Level("3000");
      fourLevels[3] = new Level("4000");
      data.insert(pair<string, Level**>(n, fourLevels));
    }
    i = data.find(n);
    i->second[stoi(l) / 1000 - 1]->classes.push_back(newClass);
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
        cout << (*i->second[k]->classes.begin())->name << (*i->second[k]->classes.begin())->level;
        vector<Time*>::iterator t;
        for (t = (*i->second[k]->classes.begin())->times.begin(); t != (*i->second[k]->classes.begin())->times.end(); t++) {
          cout << " " << (*t)->d << " " << (*t)->t;
        }
        for (j = i->second[k]->classes.begin(); j != i->second[k]->classes.end(); j++) {
          if (j == i->second[k]->classes.begin()) {
            continue;
          }
          cout << endl
               << " *** " << endl
               << (*j)->name << (*j)->level;
          for (t = (*j)->times.begin(); t != (*j)->times.end(); t++) {
            cout << " " << (*t)->d << " " << (*t)->t;
          }
        }
        cout << endl
             << endl;
      }
    }
  }
}
