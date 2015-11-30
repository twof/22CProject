#include <iostream>
#include "OMRA.hpp"

using namespace std;


int main() {
    OMRA omra;
    
    //omra.addNewCountry("Alisa", 10, 1000, 400);
    //omra.addNewCountry("Alex", 10, 300, 44);
    
    omra.initializeFromFile("/Users/fnord/Documents/CPP/22CProject/22CProject/inputOutput.txt");
    omra.printByRank();
    
    //omra.menu();
    //omra.testMethod();
    return 0;
}