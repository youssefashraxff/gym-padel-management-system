

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json; 

using namespace std;

template<typename T>
class FileHandler {
    string filePath;

public:
    FileHandler(const string& filePath)
        : filePath(filePath) {}

    vector<T> read() {
        ifstream in(filePath);
        vector<T> data;

        if (!in.is_open()) {
            cerr << "Failed to open file: " << filePath << endl;
            return data;
        }

        json j;
        in >> j;
        in.close();

        for (const auto& item : j) {
            data.push_back(item.get<T>());
        }

        return data;
    }

    void write(const vector<T>& data) {
        ofstream out(filePath);

        if (!out.is_open()) {
            cerr << "Failed to open file: " << filePath << endl;
            return;
        }

        json j = data;
        out << j.dump(4);
        out.close();
    }
};

#endif