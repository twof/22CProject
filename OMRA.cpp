//
//  OMRA.cpp
//  22CProject
//
//  Created by fnord on 11/24/15.
//  Copyright © 2015 fnord. All rights reserved.
//

#include "OMRA.hpp"

//Private
void OMRA::rankingHelper(OMRA::Country *&country){
    bool hasInserted = false;
    if (rankList.size() == 0) {
        rankList.insert(rankList.begin(), country);
    }else{
        for (int x = 0; x < rankList.size(); x++) {
            
            if (country->gold < rankList[x]->gold){
                rankList.insert(rankList.begin() + x, country);
                hasInserted = true;
                break;
            }else if (country->gold == rankList[x]->gold){
            
                if (country->silver < rankList[x]->silver) {
                    rankList.insert(rankList.begin() + x, country);
                    hasInserted = true;
                    break;
                }else if (country->silver == rankList[x]->silver){
                
                    if (country->bronze <= rankList[x]->bronze) {
                        rankList.insert(rankList.begin() + x, country);
                        hasInserted = true;
                        break;
                    }else{
                        rankList.insert(rankList.begin() + (x + 1), country);
                        hasInserted = true;
                        break;
                    }
                }else{
                    rankList.insert(rankList.begin() + (x + 1), country);
                    hasInserted = true;
                    break;
                }
            }else{
                continue;
            }
        }
        if (!hasInserted) {
            rankList.push_back(country);
        }
    }
    
    for (int i = 0; i < rankList.size(); i++) {
        rankList[i]->rank = rankList.size() - i;
    }
}

//Public'

OMRA::OMRA(){
    
}

OMRA::~OMRA(){
    
}

void OMRA::addNewCountry(string name, int goldMedalCount, int silverMedalCount, int bronzeMedalCount){
    Country *newCountry = new Country(name, goldMedalCount, silverMedalCount, bronzeMedalCount);
    rankingHelper(newCountry);
    newCountry->sortSwitch = newCountry->rankComparison;
    rankTree.add(newCountry);
    newCountry->sortSwitch = newCountry->nameComparison;
    countryTree.add(newCountry);
}

void OMRA::printByRank(){
    rankTree.inOrderPrint();
}

void OMRA::printByCountry(){
    countryTree.inOrderPrint();
}

