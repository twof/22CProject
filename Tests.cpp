#include <iostream>
#include "BST.h"
using namespace std;

void mainMenu(BST &bst);
void makeMenuChoice(BST &bst);
void addCountry(BST &bst);
void removeCountry(BST &bst);

int main() {
    BST bst;
    
    bst.add("Alisa", 1, 1000, 400, 50);
    bst.add("Sarah", 2, 300, 44, 21);
    
    // Read from file
    
    mainMenu(bst);
    
    return 0;
}

void mainMenu(BST &bst) {
    //system("CLS");
    int choice = 0;
    
    cout << "Welcome to Olympic Medals Records Agency.\n\nBegin by selecting an item from the list:" << endl;
    cout << "1.\t List by Rank" << endl;
    cout << "2.\t List by Country" << endl;
    cout << "3.\t Edit a Country" << endl;
    cout << "4.\t Add a Country" << endl;
    cout << "5.\t Remove a Country" << endl;
    cout << "6.\t Quit" << endl << endl;
    
    cout << "Choice #  ";
    cin >> choice;
    
    while (choice < 1 || choice > 6) {
        cout << "Please select a menu item between 1 and 6." << endl;
        cout << "Choice #  ";
        cin.ignore();
        cin >> choice;

    }
    
    
    if (choice == 1){
        bst.inOrderPrint();
        cout << "Press [ENTER] to return to main menu." << endl;
        cin.ignore();
        cin.get();
        mainMenu(bst);
    }
    else if (choice == 2);
    else if (choice == 3); // user input replace with found original. re-sort bst. print new.
    else if (choice == 4)
        addCountry(bst);
    else if (choice == 5)
        removeCountry(bst);
    else
        return;
}


void addCountry(BST &bst) { // Menu Option 4
    //system("CLS");
    string country;
    int rank, gold, silver, bronze;
    char choice = 'a';
    
    cout << "To add a country please insert the necessary information when prompted." << endl << endl;
    cout << "Country:  ";
    cin >> country;
    cout << "Rank:  ";
    cin >> rank;
    cout << "Gold Medals earned:  ";
    cin >> gold;
    cout << "Silver Medals earned:  ";
    cin >> silver;
    cout << "Bronze Medals earned:  ";
    cin >> bronze;
    
    bst.add(country, rank, gold, silver, bronze);
    
    while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "Would you like to add another?" << endl;
        cout << "Y/N:  ";
        cin >> choice;
    }
    
    if (toupper(choice) == 'Y')
        addCountry(bst);
    else {
        cout << "You will now be taken back to the Main Menu." << endl;
        system("pause");
        mainMenu(bst);
    }
}

void removeCountry(BST &bst) { // Menu Option 5
    //system("CLS");
    char choice = 'a';
    int rank = 0;
    
    while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "To remove a country you must know it's rank. Would you like to continue?" << endl;
        cout << "Y/N:  ";
        cin >> choice;
    }
    
    if (toupper(choice) == 'N') {
        cout << "You will now be taken back to the Main Menu." << endl;
        system("pause");
        mainMenu(bst);
    }
    else { // search for rank to remove
        cout << "Please enter country's rank #  ";
        cin >> rank;
        
        if (bst.search(rank)) {
            choice = 'a';
            while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
                cout << "Is this the country you would like to remove?" << endl;
                cout << "Y/N:  ";
                cin >> choice;
            }
            
            if (toupper(choice) == 'Y')
                bst.remove(rank);
            
        } // end of if rank is found
        
        while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
            cout << "Would you like to try again?" << endl;
            cout << "Y/N:  ";
            cin >> choice;
        }
        
        if (toupper(choice) == 'Y')
            removeCountry(bst);
        else {
            cout << "You will now be taken back to the Main Menu." << endl;
            system("pause");
            mainMenu(bst);
        }
    }
}