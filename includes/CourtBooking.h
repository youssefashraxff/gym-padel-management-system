#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class CourtBooking {
public:
    string courtID;
    string memberID;
    string location;
    time_t date;
    string time;
};
