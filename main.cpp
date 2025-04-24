#include <iostream>

#include "includes/DataManager.h"

#include "utils/json_utils.h"
#include "User.h"
#include "Member.h"
using namespace std;

int main() {
    DataManager dataManager;
    dataManager.loadData(); 
    
    User u(dataManager);
    u.login();
    
    dataManager.saveData(); 

}