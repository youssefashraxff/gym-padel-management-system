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

template <typename T>
class FileHandler
{
    string filePath;

public:
    FileHandler(const string &filePath)
        : filePath(filePath) {}

    vector<T> read()
    {
        ifstream in(filePath);
        vector<T> data;

        if (!in.is_open())
        {
            cerr << "Failed to open file for reading: " << filePath << endl;
            return data;
        }

        try
        {
            json j;
            in >> j;
            in.close();

            for (const auto &item : j)
            {
                data.push_back(item.get<T>());
            }
        }
        catch (const exception &e)
        {
            cerr << "Error reading JSON from file: " << filePath << " " << e.what() << endl;
            if (in.is_open())
                in.close();
        }

        return data;
    }

    bool write(const vector<T> &data)
    {
        ofstream out(filePath);
        if (!out.is_open())
        {
            cerr << "Failed to open file for writing: " << filePath << endl;
            return false;
        }

        try
        {
            json j_array = json::array();
            for (const auto &item : data)
            {
                json j_item;
                to_json(j_item, item);
                j_array.push_back(j_item);
            }

            out << j_array.dump(4);
            out.close();
            return true;
        }
        catch (const exception &e)
        {
            cerr << "Error writing JSON to file: " << filePath << "\n"
                 << e.what() << endl;
            if (out.is_open())
                out.close();
            return false;
        }
    }
};

#endif