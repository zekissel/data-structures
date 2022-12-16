#include <iostream>
#include "ptree.cpp"

int main () {

    PTree test;

    test.add("test");
    test.add("testing");
    test.add("testable");
    
    std::vector<std::string> collection = test.collect();
    for (auto w : collection) std::cout << w << std::endl;
    std::cout << '\n';

    test.remove("test");

    std::vector<std::string> collection2 = test.collect();
    for (auto w : collection2) std::cout << w << std::endl;
    std::cout << '\n';

    std::cout << test.size();

    return 0;
}