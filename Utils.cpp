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

vector<int> queue_to_vector(queue<int> q) {
    vector<int> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}

queue<int> vector_to_queue(const vector<int>& v) {
    queue<int> q;
    for (int id : v) {
        q.push(id);
    }
    return q;
}
