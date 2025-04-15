#include <iostream>
#include "includes/FileHandler.h"
#include "includes/Member.h"

using namespace std;

int main() {

    FileHandler<Member> handler("files/Members.json", "files/Members.json");

    std::vector<Member> members = handler.read();

    for (const auto& m : members) {
        std::cout << m.name << " - " << m.id << std::endl;
    }

    members.push_back({"New Student", 123});
    handler.write(members);

    cout << "Hello World" << endl;
    return 0;
}