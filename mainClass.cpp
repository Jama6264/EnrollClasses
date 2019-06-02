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
    string n, l, start, startT, end, endT, t, d, useless;  // name, level, time, day of the week
    stringstream ss;
    ss << line;
    getline(ss, n, ' ');
    getline(ss, l, ' ');
    getline(ss, start, ' ');
    start.erase(2, 1);
    getline(ss, startT, ' ');
    if (startT == "PM" && stoi(start) / 100 != 12) {
      start = to_string(stoi(start) + 1200);
    }
    getline(ss, useless, ' ');
    getline(ss, end, ' ');
    end.erase(2, 1);
    getline(ss, endT, ' ');
    if (endT == "PM" && stoi(end) / 100 != 12) {
      end = to_string(stoi(end) + 1200);
    }
    t = start + "-" + end;
    getline(ss, d);
    if (d == "M-F") {
      d = "MTWTHF";
    }

    auto i = data.find(n);
    if (i == data.end()) {
      Level** allLevels = new Level*[7];
      allLevels[0] = new Level("1000");
      allLevels[1] = new Level("2000");
      allLevels[2] = new Level("3000");
      allLevels[3] = new Level("4000");
      allLevels[4] = new Level("5000");
      allLevels[5] = new Level("6000");
      allLevels[6] = new Level("7000");
      allLevels[7] = new Level("8000");
      data.insert(pair<string, Level**>(n, allLevels));
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
  schedules.clear();
  slot.clear();
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
}

vector<int> startTime(Time* t) {
  stringstream ss;
  ss << t->t;
  string stringStart, stringEnd;
  getline(ss, stringStart, '-');
  getline(ss, stringEnd);
  int intStart = stoi(stringStart) / 100;
  int intEnd = stoi(stringEnd) / 100;
  if (stoi(stringEnd) % 100 == 0) {
    intEnd--;
  }
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

void Main::helper(Schedule* current, int count, int& optionNum) {
  if (!current->visited) {
    for (auto i = current->times.begin(); i != current->times.end(); i++) {
      bool flag = true;
      vector<int> st = startTime(*i);
      for (int j = 0; j < (*i)->d.length(); j++) {
        string index = "";
        if ((*i)->d[j] == 'T' && (*i)->d[j + 1] == 'H') {
          index = "TH";
        } else {
          index += (*i)->d[j];
        }
        for (auto k = st.begin(); k != st.end(); k++) {
          if (slot[index].find(*k) == slot[index].end()) {
            continue;
          } else {
            flag = false;
            break;
          }
        }
      }
      if (flag == true) {
        for (int j = 0; j < (*i)->d.length(); j++) {
          string index = "";
          if ((*i)->d[j] == 'T' && (*i)->d[j + 1] == 'H') {
            index = "TH";
          } else {
            index += (*i)->d[j];
          }
          for (auto k = st.begin(); k != st.end(); k++) {
            slot[index].insert(*k);
          }
        }
        string classInfo = current->name + current->level + " " + (*i)->d + " " + (*i)->t;
        option.push_back(classInfo);
        current->visited = true;
      }
      if (current->next != NULL) {
        helper(current->next, count, optionNum);
      }
      if (option.size() == count) {
        cout << "Option " << optionNum << ":" << endl;
        printSchedule(option);
        cout << endl;
        optionNum++;
        option.pop_back();
        vector<int> st = startTime(*i);
        for (int j = 0; j < (*i)->d.length(); j++) {
          string index = "";
          if ((*i)->d[j] == 'T' && (*i)->d[j + 1] == 'H') {
            index = "TH";
          } else {
            index += (*i)->d[j];
          }
          for (auto k = st.begin(); k != st.end(); k++) {
            slot[index].erase(*k);
          }
        }
      }
      if (flag == true) {
        vector<int> st = startTime(*i);
        for (int j = 0; j < (*i)->d.length(); j++) {
          string index = "";
          if ((*i)->d[j] == 'T' && (*i)->d[j + 1] == 'H') {
            index = "TH";
          } else {
            index += (*i)->d[j];
          }
          for (auto k = st.begin(); k != st.end(); k++) {
            slot[index].erase(*k);
          }
        }
      }
    }
    if (!option.empty()) {
      option.pop_back();
    }
    current->visited = false;
  }
}

void Main::computeSchedule(int count) {
  int optionNum = 1;

  if (count == 1) {
    cout << endl
         << "Since you only have one class, here is the information of the class:" << endl;
    cout << (*schedules.begin())->name << " " << (*schedules.begin())->level;
    for (auto i = (*schedules.begin())->times.begin(); i != (*schedules.begin())->times.end(); i++) {
      cout << " " << (*i)->d << " " << (*i)->t;
    }
    cout << endl
         << endl;
  } else {
    helper(*schedules.begin(), count, optionNum);
    cout << endl
         << "(If there is no option printed out, that means it is impossible to have all the classes at once)" << endl;
  }
}
