#include "includes/utils.h"
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>

std::string time_t_to_string(const time_t& t) {
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

time_t string_to_time_t(const std::string& str) {
    std::tm tm = {};
    std::istringstream iss(str);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    return std::mktime(&tm);
}

vector<string> queue_to_vector(queue<string> q) {
    vector<string> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}

queue<string> vector_to_queue(const vector<string>& v) {
    queue<string> q;
    for (string id : v) {
        q.push(id);
    }
    return q;
}
