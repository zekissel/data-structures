#include <iostream>
#include "ptree.cpp"

int main () {

    PTree test;

    test.add("test");
    test.add("testing");
    test.add("testable");
    
    std::vector<std::string> collection = test.collect();

    for (auto w : collection) std::cout << w << std::endl;

    return 0;
}