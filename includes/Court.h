#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Court {
public:
    string id;
    string location;
    map<string, bool> timeSlots;
};
