#include "utils.h"


using namespace std;

string time_t_to_string(const time_t& t) {
    tm tm = *std::localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

time_t string_to_time_t(const string& str) {
    tm tm = {};
    istringstream iss(str);
    iss >> get_time(&tm, "%Y-%m-%d");
    return mktime(&tm);
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
    for (const string& id : v) {
        q.push(id);
    }
    return q;
}