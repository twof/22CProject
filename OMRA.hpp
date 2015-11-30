;//
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
        enum Comparison{
            GT, //Greater than (>)
            LT, //Less than (<)
            ET, //Equal to (==)
            NET, //Not equal to (!=)
            LTE, //Less than or equal to (<=)
            GTE //Greater than or equal to (>=)
        };

        string countryName;
        int rank;
        int gold;
        int silver;
        int bronze;
        bool (*sortSwitch) (Country, const Country, Comparison);
        
        
        
        Country(): countryName(""), rank(NULL), gold(NULL), silver(NULL), bronze(NULL){}
        Country(string ncountry, int rank, int ngold, int nsilver, int nbronze): countryName(ncountry), rank(rank), gold(ngold), silver(nsilver), bronze(nbronze), sortSwitch(NULL){}
        
        bool operator==(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, ET);
        }
        bool operator!=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, NET);
        }
        bool operator>(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, GT);
        }
        bool operator<(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, LT);
        }
        bool operator>=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, GTE);
        }
        bool operator<=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, LTE);
        }
        
        friend ostream& operator<< (ostream& os, Country const *rightCountry){
            os << rightCountry->countryName << " is rank " << rightCountry->rank << " with " << rightCountry->gold << " gold medals, " << rightCountry->silver << " silver medals, and " << rightCountry->bronze << " bronze medals.";
            return os;
        }
        
        static bool rankComparison (Country leftCountry, const Country rightCountry, Comparison compType){
            switch(compType){
                case LT:
                    return leftCountry.rank < rightCountry.rank;
                    break;
                case GT:
                    return leftCountry.rank > rightCountry.rank;
                    break;
                case ET:
                    return leftCountry.rank == rightCountry.rank;
                    break;
                case NET:
                    return leftCountry.rank != rightCountry.rank;
                    break;
                case LTE:
                    return leftCountry.rank >= rightCountry.rank;
                    break;
                case GTE:
                    return leftCountry.rank <= rightCountry.rank;
                    break;
                default:
                    cout << "Hit default case somehow" << endl;
                    return false;
                    break;
            }
        }
        static bool nameComparison (Country leftCountry, const Country rightCountry, Comparison compType){
            switch(compType){
                case LT:
                    return leftCountry.countryName < rightCountry.countryName;
                    break;
                case GT:
                    return leftCountry.countryName > rightCountry.countryName;
                    break;
                case ET:
                    return leftCountry.countryName == rightCountry.countryName;
                    break;
                case NET:
                    return leftCountry.countryName != rightCountry.countryName;
                    break;
                case LTE:
                    return leftCountry.countryName >= rightCountry.countryName;
                    break;
                case GTE:
                    return leftCountry.countryName <= rightCountry.countryName;
                    break;
                default:
                    cout << "Hit default case somehow" << endl;
                    return false;
                    break;
            }
        }
    };
    
    
    BST<Country*> rankTree;
    BST<Country*> countryTree;
    vector<Country*> rankList;
    
    void rankingHelper(Country *country);
    vector<string> tokenizeCSVLine(istream &is);
    
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
    void getCountry(string name);
    void getCountry(int rank);
    void testMethod();
    void printNodeRank(int value); // printNode helper for rank
    void printNodeCountry(string value); // printNode helper for country
    //	void makeMenuChoice(OMRA &omra);
    void printList();	// menu choice option #1
    void printNode();	// menu choice option #2 & 6
    void addCountry();	// menu choice option #4
    void removeCountry();	// menu choice option #5
    void edit();	// menu choice option #3
    int findRank(string country);
    
};

#endif /* OMRA_hpp */
