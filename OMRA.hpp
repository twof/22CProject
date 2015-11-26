//
//  OMRA.hpp
//  22CProject
//
//  Created by fnord on 11/24/15.
//  Copyright © 2015 fnord. All rights reserved.
//

#ifndef OMRA_hpp
#define OMRA_hpp

#include <stdio.h>
#include "BST.h"

class OMRA {
private:
    struct Country{
        string countryName;
        int rank;
        int gold;
        int silver;
        int bronze;
        
        
        Country(): countryName(""), rank(NULL), gold(NULL), silver(NULL), bronze(NULL){}
        Country(string ncountry, int ngold, int nsilver, int nbronze): countryName(ncountry), rank(NULL), gold(ngold), silver(nsilver), bronze(nbronze) {}
        bool operator==(const Country &rightCountry){
            return this->rank == rightCountry.rank;
        }
        bool operator!=(const Country &rightCountry){
            return this->rank != rightCountry.rank;
        }
        bool operator>(const Country &rightCountry){
            return sortSwitch(*this, rightCountry);
        }
        bool operator<(const Country &rightCountry){
            return this->rank < rightCountry.rank;
        }
        bool operator>=(const Country &rightCountry){
            return this->rank >= rightCountry.rank;
        }
        bool operator<=(const Country &rightCountry){
            return this->rank <= rightCountry.rank;
        }
        friend ostream& operator<<(std::ostream& os, const Country &country){
            os << country.countryName << " is rank " << country.rank;
            return os;
        }
        
        bool (*sortSwitch) (const Country&, const Country&) = NULL;
        
        static bool rankComparison (const Country& leftCountry, const Country& rightCountry){
            return leftCountry.rank > rightCountry.rank;
        }
        static bool nameComparison (const Country& leftCountry, const Country& rightCountry){
            return leftCountry.countryName > rightCountry.countryName;
        }
        
    };
    
    
    BST<Country*> rankTree;
    BST<Country*> countryTree;
    vector<Country*> rankList;
    
    void rankingHelper(Country* country);
    
public:
    OMRA();
    ~OMRA();
    bool initializeFromFile(string filePath);
    bool exportToFile(string filePath);
    bool saveToFile();
    void addNewCountry(string name, int goldMedalCount, int silverMedalCount, int bonzeMedalCount);
    void editCountry(int rank);
    void editCountry(string name);
    void printByCountry();
    void printByRank();
    void menu();
    
};

#endif /* OMRA_hpp */
