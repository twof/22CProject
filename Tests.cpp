#include <iostream>
#include "OMRA.hpp"
using namespace std;



int main() {
    OMRA omra;
    omra.addNewCountry("Alisa", 1000, 200, 500);
    omra.addNewCountry("Alex", 2000, 300, 10);
    omra.addNewCountry("Murica", 5000, 300, 30);
    omra.printByCountry();
    cout << "Print by rank: " << endl;
    omra.printByRank();
    //omra.testMethod();
}