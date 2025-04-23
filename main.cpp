#include <iostream>

#include "includes/DataManager.h"

#include "utils/json_utils.h"

using namespace std;

int main() {
    DataManager dataManager;
    dataManager.loadData();
    //Logic
    dataManager.saveData();
}