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
#include <iomanip>
#include "BST.h"

/// The Olympic Medal Reccords Agency
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
        
        
        /**
         *  The default constructor for a country. Everything is set to null
         */
        Country(): countryName(""), rank(NULL), gold(NULL), silver(NULL), bronze(NULL){}
        
        /**
         *  Constructor that takes values for each of the fields except for sortSwitch and rank.
         *
         *  @param ncountry Name of the country.
         *  @param rank     Rank of the country.
         *  @param ngold    Number of gold medals
         *  @param nsilver  Number of silver medals
         *  @param nbronze  Number of bronze medals
         */
        Country(string ncountry, int rank, int ngold, int nsilver, int nbronze): countryName(ncountry), rank(rank), gold(ngold), silver(nsilver), bronze(nbronze), sortSwitch(NULL){}
        
        /**
         *  Overload of == operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator==(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, ET);
        }
        
        /**
         *  Overload of != operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator!=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, NET);
        }
        
        /**
         *  Overload of > operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator>(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, GT);
        }
        
        /**
         *  Overload of < operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator<(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, LT);
        }
        
        /**
         *  Overload of > operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator>=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, GTE);
        }
        
        /**
         *  Overload of <= operator.
         *
         *  @param rightCountry The country on the right of the operator.
         *
         *  @return The result of the comparison.
         */
        bool operator<=(const Country &rightCountry){
            return sortSwitch(*this, rightCountry, LTE);
        }
        
        /**
         *  Operator overloaded so that outputing country is in the format "rank" "name" "gold" "silver" "bronze"
         *
         *  @param os           The output stream.
         *  @param rightCountry The country on the right side of the operator
         *
         *  @return The output stream
         */
        friend ostream& operator<< (ostream& os, Country const *rightCountry){
            os << setw(4) << rightCountry->rank << setw(32) << rightCountry->countryName << setw(6) << rightCountry->gold << " Gold" << setw(6) << rightCountry->silver << " Silver" << setw(6) << rightCountry->bronze << " Bronze";
            return os;
        }
        
        /**
         *  A helper function used to overload the comparison operators so countries can be compared according to their ranks.
         *
         *  @param leftCountry  The country on the left side of the operator.
         *  @param rightCountry The country on the right side of the operator.
         *  @param compType     The type of comparison.
         *
         *  @return Whether the comparison is true or false.
         */
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
        
        /**
         *  A helper function used to overload the comparison operators so countries can be compared according to their names.
         *
         *  @param leftCountry  The country on the left side of the operator.
         *  @param rightCountry The country on the right side of the operator.
         *  @param compType     The type of comparison.
         *
         *  @return Whether the comparison is true or false.
         */
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
    
    /**
     *  A BST to hold the countries sorted by rank.
     */
    BST<Country*> rankTree;
    /**
     *  A BST to hold the countries sorted alphabetically by name.
     */
    BST<Country*> countryTree;
    /**
     *  A vector uset to stor countries in order to simplify ranking.
     */
    vector<Country*> rankList;
    
    void rankingHelper(Country *country);
    void recalculateRank();
    void cohesiveRemove(Country *country);
    
public:
    OMRA();
    ~OMRA();
    bool initializeFromFile(string filePath);
    bool exportToFile(string filePath);
    bool saveToFile();
    void addNewCountry(string name, int goldMedalCount, int silverMedalCount, int bonzeMedalCount);
    void printByCountry();
    void printByRank();
    void menu();
    void getCountry(string name);
    void getCountry(int rank);
    void printNodeRank(int value); // printNode helper for rank
    void printNodeCountry(string value); // printNode helper for country
    void printList();	// menu choice option #1
    void printNode();	// menu choice option #2 & 6
    void addCountry();	// menu choice option #4
    void removeCountry();	// menu choice option #5
    void edit();	// menu choice option #3
    
    
};

#endif /* OMRA_hpp */
