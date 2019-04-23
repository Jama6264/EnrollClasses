#include <iostream>
#include <sstream>
#include "mainClass.hpp"
using namespace std;

int main() {
  Main c("test.txt");
  // c.printAll();
  vector<InputClass> user;
  set<string> classList;
  string input = "";
  int count = 0;

  while (1) {
    cout << "Enter the class (e.g. CSCI2270) you want to enroll (enter \"end\" if you have entered all the classes):" << endl;
    cin >> input;
    cout << endl;
    if (input == "end") {
      break;
    }
    if (input.size() != 8) {
      cout << "You may misspell the class name." << endl;
      continue;
    }
    if (classList.find(input) == classList.end()) {
      classList.insert(input);
    } else {
      cout << "You have entered a class repeatedly. Please enter another class." << endl;
      continue;
    }
    string prefix = "", number = "";
    for (int i = 0; i < 4; i++) {
      prefix += input[i];
    }
    for (int i = 4; i < 8; i++) {
      number += input[i];
    }
    InputClass newIC(prefix, number);
    user.push_back(newIC);
    count++;
  }

  if (count == 0) {
    return 0;
  }

  if (c.readInput(user)) {
    cout << "Successfully input your classes. Starting to compute the schedule..." << endl;
  } else {
    cout << "Fail to input your classes. Maybe some of your classes are misinput." << endl;
  }
  c.inputEdges();
  c.computeSchedule(count);

  return 0;
}
