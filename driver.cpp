#include <iostream>
#include <sstream>
#include "mainClass.hpp"
using namespace std;

int main() {
  Main c("test.txt");
  vector<InputClass> user;
  set<string> classList;
  string input = "";
  int count = 0;

  while (1) {
    cout << "Enter the class (e.g. CSCI 2270) you want to enroll (enter \"end\" if you have entered all the classes):" << endl;
    getline(cin, input);
    cout << endl;
    if (input == "end") {
      break;
    }
    if (classList.find(input) == classList.end()) {
      classList.insert(input);
    } else {
      cout << "You have entered a class repeatedly. Please enter another class." << endl;
      continue;
    }
    stringstream ss;
    ss << input;
    string prefix, number;
    getline(ss, prefix, ' ');
    getline(ss, number);
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
    return 0;
  }
  c.inputEdges();
  c.computeSchedule(count);
  return 0;
}
