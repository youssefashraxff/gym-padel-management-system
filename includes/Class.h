#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <queue>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Class {
public:
    string type;
    string id;
    string coachName;
    int capacity;
    vector<int> members;
    string dayTime;
    queue<int> waitlist;
};