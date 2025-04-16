#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

template<typename T>
class FileHandler {
    std::string readFile;
    std::string writeFile;

public:
    FileHandler(const string& readFile, const string& writeFile)
        : readFile(readFile), writeFile(writeFile) {}

    vector<T> read() {
        ifstream in(readFile);
        vector<T> data;

        if (!in.is_open()) {
            cerr << "Failed to open file: " << readFile << endl;
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
        ofstream out(writeFile);

        if (!out.is_open()) {
            cerr << "Failed to open file: " << writeFile << endl;
            return;
        }

        json j = data;
        out << j.dump(4);
        out.close();
    }
};