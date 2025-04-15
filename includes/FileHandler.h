#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

template<typename T>
class FileHandler {
    std::string readFile;
    std::string writeFile;

public:
    FileHandler(const std::string& readFile, const std::string& writeFile)
        : readFile(readFile), writeFile(writeFile) {}

    std::vector<T> read() {
        std::ifstream in(readFile);
        std::vector<T> data;

        if (!in.is_open()) {
            std::cerr << "Failed to open file: " << readFile << std::endl;
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
        std::ofstream out(writeFile);

        if (!out.is_open()) {
            std::cerr << "Failed to open file: " << writeFile << std::endl;
            return;
        }

        json j = data;
        out << j.dump(4);
        out.close();
    }
};
