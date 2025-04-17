#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Workout {
public:
    int memberID;
    string activity;
    string duration;
    time_t date;
};

