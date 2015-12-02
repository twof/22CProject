//
//  OMRA.cpp
//  22CProject
//
//  Created by fnord on 11/24/15.
//  Copyright © 2015 fnord. All rights reserved.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "OMRA.hpp"

//Private

/**
 *  Inserts a country into the rankList in order, then determines its rank
 *
 *  @param country The country to be inserted into rankList and ranked
 */
void OMRA::rankingHelper(OMRA::Country *country){
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

/**
 *  Recalculates rank. Useful after deletions and edits.
 */
void OMRA::recalculateRank(){
    for (int i = 0; i < rankList.size(); i++) {
        rankList[i]->rank = rankList.size() - i;
    }
}

/**
 *  Removes a country from both BSTs and from the rankList. Then it recalculates rankings.
 *
 *  @param country The country to be removed.
 */
void OMRA::cohesiveRemove(Country *country){
    country->sortSwitch = country->nameComparison;
    countryTree.remove(country);
    country->sortSwitch = country->rankComparison;
    rankTree.remove(country);
    rankList.erase(std::remove(rankList.begin(), rankList.end(), country), rankList.end());
    recalculateRank();
}

//Public'

/**
 *  Default constructor. Doesn't do anything.
 */
OMRA::OMRA(){
    
}

/**
 *  Default destructor. Doesn't do anything.
 */
OMRA::~OMRA(){
    
}

/**
 *  Clears the screen by carriage returning a bunch of times.
 */
void clearScreen() {
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

/**
 *  Adds a new country to the BSTs and ranks it.
 *
 *  @param name             The name of the country to be added.
 *  @param goldMedalCount   The gold medal count of the country to be added.
 *  @param silverMedalCount The silver medal count of the country to be added.
 *  @param bronzeMedalCount The bronze medal count of the country to be added.
 */
void OMRA::addNewCountry(string name, int goldMedalCount, int silverMedalCount, int bronzeMedalCount){
    Country *newCountry = new Country(name, NULL, goldMedalCount, silverMedalCount, bronzeMedalCount);
    rankingHelper(newCountry);
    newCountry->sortSwitch = newCountry->rankComparison;
    rankTree.add(newCountry);
    newCountry->sortSwitch = newCountry->nameComparison;
    countryTree.add(newCountry);
}

/**
 *  Prints all of the countries by rank.
 */
void OMRA::printByRank(){
	cout << endl;
    rankTree.inOrderPrint();
	cout << endl;
}

/**
 *  Prints all of the countries in alphabetical order
 */
void OMRA::printByCountry(){
	cout << endl;
    countryTree.inOrderPrint();
	cout << endl;
}

/**
 *  Loads countries from a CSV file.
 *  
 *  @param filePath The file to read from.
 *  
 *  @return Returns true if the file was opened succefully.
 */
bool OMRA::initializeFromFile(string filePath){
    ifstream file;
    file.open(filePath);
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vector<string> result;
            
            stringstream lineStream(line);
            string cell;
            
            while(getline(lineStream,cell,',')){
                result.push_back(cell);
            }

            addNewCountry(result[0], stoi(result[2]), stoi(result[3]), stoi(result[4]));
        }
        return true;
    }else{
        return false;
    }
}

/**
 *  Saves all of the countries into a file in CSV format.
 *
 *  @param filePath The file to save to.
 *
 *  @return Returns true if the file was opened succesfully.
 */
bool OMRA::exportToFile(string filePath){
    ofstream saveFile;
    saveFile.open(filePath);
    if(saveFile.is_open()){
        for (int i = 0; i < rankList.size(); i++) {
            saveFile << rankList[i]->countryName << ", " << rankList[i]->rank << ", " << rankList[i]->gold << ", " << rankList[i]->silver << ", " << rankList[i]->bronze << endl;
        }
        return true;
    }else{
        return false;
    }
}



/**
 *  Prints out the menu and handles all of the options.
 */
void OMRA::menu() {
    int choice = 0;
    clearScreen();
    
    cout << "Welcome to Olympic Medals Records Agency.\n\nBegin by selecting an item from the list:" << endl;
    cout << "1.\t List" << endl;
    cout << "2.\t Search" << endl;
    cout << "3.\t Edit a Country" << endl;
    cout << "4.\t Add a Country" << endl;
    cout << "5.\t Remove a Country" << endl;
    //	cout << "6.\t Search" << endl;
    cout << "6.\t Quit" << endl << endl;
    
    cout << "Choice #  ";
    cin >> choice;
    cin.clear();
    cin.ignore();
    
    while (choice < 1 || choice > 6) {
        cout << "Please select a menu item between 1 and 6." << endl;
        cout << "Choice #  ";
        cin >> choice;
        cin.clear();
        cin.ignore();
        
    }
    
    clearScreen();
    if (choice == 1) // List by Rank or Country
        printList();
    else if (choice == 2) // Print Country or Search
        printNode();
    else if (choice == 3) // Edit a Country
        edit();
    else if (choice == 4) // Add
        addCountry();
    else if (choice == 5) // Remove
        removeCountry();
    else // quit (option 6)
        return;
}

/**
 *  Handles the print list option from the menu.
 */
void OMRA::printList() { // Option 1 "List"
    int choice = 0;
    
    cout << "Would you like to print by (1) Rank  or  (2) Country" << endl;
    cout << "Choice:  ";
    cin >> choice;
    cin.clear();
    cin.ignore();
    
    while (choice < 1 || choice > 2) {
        cout << "Please choose either (1) to print by Rank or (2) to print by Country." << endl;
        cout << "Choice:  ";
        cin >> choice;
        cin.clear();
        cin.ignore();
    }
    
    if (choice == 1)
        printByRank();
    else
        printByCountry();
    
    cout << "Press [ENTER] to return to the Main Menu...";
    cin.get(); // pause system
    menu(); // return to menu
}

/**
 *  Handles the search option from the menu.
 */
void OMRA::printNode() { // Option 2. SEARCH
    int choice = 0;
    
    cout << "Welcome to the Search Function of OMRA." << endl;
    cout << "Would you like to search by (1) Rank  or  (2) Country" << endl;
    cout << "Choice:  ";
    cin >> choice;
    cin.clear();
    cin.ignore();
    
    while (choice < 1 || choice > 2) {
        cout << "Please choose either (1) to search by Rank or (2) to search by Country." << endl;
        cout << "Choice:  ";
        cin >> choice;
        cin.clear();
        cin.ignore();
    }
    
    if (choice == 1) {
        int rank = 0;
        cout << "Please enter rank:  ";
        cin >> rank;
        printNodeRank(rank);
    }
    else {
        string name = "a";
        cout << "Please enter the name of the Country:  ";
        getline(cin, name);
        printNodeCountry(name);
    }
    
    cin.ignore();
    cout << "Press [ENTER] to return to the Main Menu...";
    cin.get(); // pause system
    menu(); // return to menu
}

/**
 *  Handles the edit option from the menu.
 */
void OMRA::edit() { // Option 3
    string name;
    char choice;

	cout << "Welcome to the Edit Function of OMRA." << endl;
    cout << "Enter the name of the Country to be edited:  ";
    getline(cin, name);
	cout << endl;
    
    Country *dummyCountry = new Country(name, 0, 0, 0, 0);
    Country *foundCountry;
	dummyCountry->sortSwitch = dummyCountry->nameComparison;

    if (countryTree.contains(dummyCountry)) {
        foundCountry = countryTree.getNode(dummyCountry);
		cout << foundCountry << endl;
        cout << "Is this the country you would like to edit? (Y/N)" << endl;
        cout << "Choice:  ";
        cin >> choice;
        
        while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
            cout << "Enter (Y) for yes or (N) for no." << endl;
            cout << "Choice:  ";
            cin >> choice;
        }
        
        if (toupper(choice) == 'Y') { // edit country by removing old and adding new
            cohesiveRemove(foundCountry);
            
            string country;
            int gold, silver, bronze;
            
            cout << "Insert the necessary information for '" << name << "'when prompted." << endl;
            cout << "Name of Country:  ";
            cin >> country;
            cout << "Gold Medals earned:  ";
            cin >> gold;
            cout << "Silver Medals earned:  ";
            cin >> silver;
            cout << "Bronze Medals earned:  ";
            cin >> bronze;
            
            addNewCountry(country, gold, silver, bronze);
        }
    }
    
    
    cout << "Would you like to edit another? (Y/N)" << endl;
    cout << "Choice:  ";
    cin >> choice;
    
    while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "Please enter (Y) for yes or (N) for no." << endl;
        cout << "Choice:  ";
        cin >> choice;
    }
    
    if (toupper(choice) == 'Y') {
        edit();
    }
    else {
        cout << "Press [ENTER] to return to the Main Menu...";
        cin.get(); // pause system
        menu();
    }
    
}


/**
 *  Handles the add option from the menu.
 */
void OMRA::addCountry() { // Option 4
    string country;
    int gold, silver, bronze;
    char choice = 'a';
    
    cout << "Welcome to the Add Country Function of OMRA." << endl;
    cout << "To add a country insert the necessary information when prompted." << endl << endl;
    cout << "Name of Country:  ";
    getline(cin, country);
    cout << "Gold Medals earned:  ";
    cin >> gold;
    cout << "Silver Medals earned:  ";
    cin >> silver;
    cout << "Bronze Medals earned:  ";
    cin >> bronze;
    
    addNewCountry(country, gold, silver, bronze); //
    
    while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "Would you like to add another?" << endl;
        cout << "Y/N:  ";
        cin >> choice;
    }
    
    if (toupper(choice) == 'Y')
        addCountry();
    else {
        cout << "Press [ENTER] to return to the Main Menu...";
        cin.get(); // pause system
        menu();  // return to menu
    }
}

/**
 *  Handles the remove option from the menu.
 */
void OMRA::removeCountry() { // Option 5
    int choice = 0;
    char charChoice = 'a';
    
    cout << "Welcome to the Remove Country Function of OMRA." << endl;
    cout << "Would you like to search by (1) Rank  or  (2) Country" << endl;
    cout << "Choice:  ";
    cin >> choice;
    
    while (choice < 1 || choice > 2) {
        cout << "Please choose either (1) to search by Rank or (2) to search by Country." << endl;
        cout << "Choice:  ";
        cin >> choice;
    }
    
    if (choice == 1) { // Remove by Rank
        int rank = 0;
        cout << "Please enter rank:  ";
        cin >> rank;
        Country *dummyRank = new Country(" ", rank, 0, 0, 0);
        Country *foundCountry = nullptr;
		dummyRank->sortSwitch = dummyRank->rankComparison;
        
        if (rankTree.getNode(dummyRank) != NULL) {
            while (toupper(charChoice) != 'Y' && toupper(charChoice) != 'N') {
                foundCountry = rankTree.getNode(dummyRank);
				cout << foundCountry << endl;
                cout << "Is this the country you would like to remove?" << endl;
                cout << "Y/N:  ";
                cin >> charChoice;
            }
            
            if (toupper(charChoice) == 'Y') {
                cohesiveRemove(foundCountry);
                cout << endl << foundCountry->countryName << " has been removed." << endl;
            }
        }
    }
    else { // Remove by Country
        string name = "a";
        cout << "Please enter the name of the Country:  ";
        cin >> name;
        Country *dummyCountry = new Country(name, 0, 0, 0, 0);
        Country *foundCountry = nullptr;
        
		dummyCountry->sortSwitch = dummyCountry->nameComparison;
        if (countryTree.contains(dummyCountry)) {
			while (toupper(charChoice) != 'Y' && toupper(charChoice) != 'N') {
                foundCountry = countryTree.getNode(dummyCountry);
				cout << foundCountry << endl;
				cout << "Is this the country you would like to remove?" << endl;
				cout << "Y/N:  ";
				cin >> charChoice;
                cin.clear();
                cin.ignore();
                
			}

			if (toupper(charChoice) == 'Y') {
                cohesiveRemove(foundCountry);
                cout << endl << foundCountry->countryName << " has been removed." << endl;
			}
		}
    }
    
    charChoice = 'a';
    while (toupper(charChoice) != 'Y' && toupper(charChoice) != 'N') {
        cout << "Would you like to try again?" << endl;
        cout << "Y/N:  ";
        cin >> charChoice;
    }
    
    if (toupper(charChoice) == 'Y') { // remove another or try again
        removeCountry();
    }
    else {
        cout << "Press [ENTER] to return to the Main Menu...";
        cin.get(); // pause system
        menu(); // return to menu
    }
}

/**
 *  Used to print a country after searching for it by rank.
 *
 *  @param value The rank to search for.
 */
void OMRA::printNodeRank(int value) { // can be used to PRINT node and SEARCH tree
    Country *dummyCountry = new Country(" ", value, 0, 0, 0);
    dummyCountry->sortSwitch = dummyCountry->rankComparison;
    if (value < 0 || value > rankTree.getSize()) {
        cout << "Item not found." << endl;
    }
    else {
        cout << setfill('-') << setw(80) << "-" << endl << setfill(' ');
        cout << rankTree.getNode(dummyCountry) << endl;
        cout << setfill('-') << setw(80) << "-" << endl << setfill(' ');
    }

}

/**
 *  User to print a country after searching for it by name.
 *
 *  @param value The name of the country to search for.
 */
void OMRA::printNodeCountry(string value) { // can be used to PRINT node and SEARCH tree
    Country *dummyCountry = new Country(value, 0, 0, 0, 0);
    dummyCountry->sortSwitch = dummyCountry->nameComparison;
    if (countryTree.contains(dummyCountry)) {
        cout << setfill('-') << setw(80) << "-" << endl << setfill(' ');
        cout << countryTree.getNode(dummyCountry) << endl;
        cout << setfill('-') << setw(80) << "-" << endl << setfill(' ');
    }
    else
        cout << "Item not found." << endl;
}
