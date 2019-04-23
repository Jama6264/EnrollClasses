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

    auto i = data.find(n);
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
    auto m = i->second[stoi(l) / 1000 - 1]->classes.find(l);
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

bool Main::readInput(vector<InputClass> user) {
  if (user.empty()) {
    return false;
  }
  vector<InputClass>::iterator v;
  for (v = user.begin(); v != user.end(); v++) {
    auto m = data.find(v->prefix);
    if (m == data.end()) {
      return false;
    } else {
      auto c = m->second[stoi(v->number) / 1000 - 1]->classes.find(v->number);
      if (c == m->second[stoi(v->number) / 1000 - 1]->classes.end()) {
        return false;
      } else {
        Schedule* newS = new Schedule(v->prefix, v->number, c->second->times);
        // cout << v->prefix << " " << v->number << endl;
        // for (auto i = c->second->times.begin(); i != c->second->times.end(); i++) {
        //   cout << (*i)->d << " " << (*i)->t;
        // }
        // cout << endl;
        schedules.push_back(newS);
      }
    }
  }
  return true;
}

void Main::inputEdges() {
  for (auto i = schedules.begin(); i != schedules.end() - 1; i++) {
    (*i)->next = *(i + 1);
  }
  // for (auto i = schedules.begin(); i != schedules.end(); i++) {
  //   if ((*i)->next != NULL) {
  //     cout << (*i)->name << " => " << (*i)->next->name << endl;
  //   } else {
  //     cout << (*i)->name << " => NULL" << endl;
  //   }
  // }
}

vector<int> startTime(Time* t) {
  stringstream ss;
  ss << t->t;
  string stringStart, stringEnd;
  getline(ss, stringStart, '-');
  getline(ss, stringEnd);
  int intStart = stoi(stringStart) / 100;
  int intEnd = stoi(stringEnd) / 100;
  vector<int> timeSlot;
  for (int i = intStart; i <= intEnd; i++) {
    timeSlot.push_back(i);
  }
  return timeSlot;
}

void printSchedule(vector<string> option) {
  for (auto i = option.begin(); i != option.end(); i++) {
    cout << *i << endl;
  }
}

void Main::helper(Schedule* current, vector<string> option, int count, int optionNum) {
  if (current != NULL) {
    for (auto i = current->times.begin(); i != current->times.end(); i++) {
      vector<int> st = startTime(*i);
      for (int j = 0; j < (*i)->d.length(); j++) {
        string index = "";
        if ((*i)->d[j] == 'T' && (*i)->d[j + 1] == 'h') {
          index = "Th";
        } else {
          index += (*i)->d[j];
        }
        for (auto k = st.begin(); k != st.end(); k++) {
          if (slot[index].find(*k) == slot[index].end()) {
            continue;
          } else {
            return;
          }
        }
        for (auto k = st.begin(); k != st.end(); k++) {
          slot[index].insert(*k);
        }
      }
      string classInfo = current->name + current->level + " " + (*i)->d + " " + (*i)->t;
      option.push_back(classInfo);
      helper(current->next, option, count, optionNum);
      if (option.size() == count) {
        cout << "Option " << optionNum << ":" << endl;
        printSchedule(option);
        cout << endl;
        optionNum++;
      }
    }
    option.pop_back();
  }
}

void Main::computeSchedule(int count) {
  vector<string> option;
  int optionNum = 1;

  helper(*schedules.begin(), option, count, optionNum);
  cout << endl
       << "(If there is no option printed out, that means it is impossible to have all the classes at once)" << endl;
}
