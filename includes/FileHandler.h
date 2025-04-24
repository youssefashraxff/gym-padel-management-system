

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
// #include "json_utils.h"

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

    void write(const std::vector<T>& data) {
        std::ofstream out(filePath);
        if (!out.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }
    
        nlohmann::json j_array = nlohmann::json::array();
        for (const auto& item : data) {
            try {
                nlohmann::json j_item;
                to_json(j_item, item); // call to_json explicitly
                j_array.push_back(j_item);
            } catch (...) {
                // Optional: skip on error
            }
        }
    
        try {
            out << j_array.dump(4); // write safely
        } catch (...) {
            // Optional: handle write error
        }
        
        std::cout << "[WRITE] Writing " << data.size() << " members to: " << filePath << std::endl;
        out.close();
    }
};

#endif