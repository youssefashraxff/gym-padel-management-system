#include <iostream>
#include "includes/FileHandler.h"
#include "includes/Member.h"

using namespace std;

int main() {

    FileHandler<Member> handler("files/Members.json", "files/Members.json");

    vector<Member> members = handler.read();

    for (const auto& m : members) {
        cout << m.name << " - " << m.id << endl;
    }

    handler.write(members);
    
    return 0;
}