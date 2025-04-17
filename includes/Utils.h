#pragma once
#include <string>
#include <ctime>
#include <vector>
#include <queue>

using namespace std;

std::string time_t_to_string(const time_t& t);
time_t string_to_time_t(const std::string& str);

vector<int> queue_to_vector(queue<int> q);
queue<int> vector_to_queue(const vector<int>& v);