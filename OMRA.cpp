//
//  OMRA.cpp
//  22CProject
//
//  Created by fnord on 11/24/15.
//  Copyright © 2015 fnord. All rights reserved.
//

#include "OMRA.hpp"

//Private
void OMRA::rankingHelper(OMRA::Country country){
    for (int x = 0; x < rankList.size(); x++) {
        
        if (country.gold <= rankList[x].gold){
            
            if (country.silver <= rankList[x].silver) {
                
                if (country.bronze <= rankList[x].bronze) {
                    rankList.insert(rankList.begin() + x, country);
                    country.rank = x;
                }else{
                    rankList.insert(rankList.begin() + x + 1, country);
                    country.rank = x+1;
                }
            }else{
                rankList.insert(rankList.begin() + x + 1, country);
                country.rank = x+1;
            }
        }else{
            continue;
        }
    }
}

//Public'

OMRA::OMRA(){
    
}

OMRA::~OMRA(){
    
}

void OMRA::addNewCountry(string name, int goldMedalCount, int silverMedalCount, int bronzeMedalCount){
    Country newCountry(name, goldMedalCount, silverMedalCount, bronzeMedalCount);
    rankingHelper(newCountry);
    newCountry.sortSwitch = newCountry.rankComparison;
    rankTree.add(&newCountry);
    newCountry.sortSwitch = newCountry.countryComparison;
    countryTree.add(<#OMRA::Country *value#>)
}

void OMRA::printByRank(){
    rankTree.inOrderPrint();
}

