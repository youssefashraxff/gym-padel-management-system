#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Staff {
public:
    string name;
    string id;
    string role;
};