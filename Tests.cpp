#include <iostream>
#include "OMRA.hpp"

using namespace std;


int main() {
    OMRA omra;
    
    //omra.addNewCountry("Alisa", 10, 1000, 400);
    //omra.addNewCountry("Alex", 10, 300, 44);
    
	if (omra.initializeFromFile("/Users/fnord/Documents/CPP/22CProject/22CProject/inputOutput.txt")) {
		omra.printByRank();
	}
	else
		cout << "File failed to open." << endl;
    
    omra.menu();
    //omra.testMethod();
    return 0;
}