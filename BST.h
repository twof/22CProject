#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <queue>
#include <iomanip>
#include <assert.h>

using namespace std;

class BST
{
private:
    struct Node
    {
        string country;
        int rank;
        int gold;
        int silver;
        int bronze;
        Node* left;
        Node* right;
        
        Node() : left(NULL), right(NULL) {}
        Node(string ncountry, int nrank, int ngold, int nsilver, int nbronze) :
        left(NULL), right(NULL), country(ncountry), rank(nrank), gold(ngold), silver(nsilver), bronze(nbronze) {}
    };
    
    typedef struct Node* Nodeptr;
    
    Nodeptr root;
    int size;
    
    /**Private helper functions*/
    
    void addValue(Nodeptr root, string country, int rank, int gold, int silver, int bronze) {
        if (rank != root->rank) {
            if (rank < root->rank) {
                if (root->left == NULL) {
                    root->left = new Node(country, rank, gold, silver, bronze);
                    size++;
                }
                else
                    addValue(root->left, country, rank, gold, silver, bronze);
            }
            else { // value is greater then root
                if (root->right == NULL) {
                    root->right = new Node(country, rank, gold, silver, bronze);
                    size++;
                }
                else
                    addValue(root->right, country, rank, gold, silver, bronze);
            }
        }
        else {
            cout << "The country with rank '" << rank << "' will not be inserted into the tree because an equal value already exists." << endl;
        }
    }
    
    void printInOrder(Nodeptr root) {
        if (root != NULL) { // if list is not empty
            if (root->left != NULL) // move to smallest element
            {
                printInOrder(root->left);
                cout << endl;
            }
            
            cout << root->rank << ".\t" << setw(30) << root->country <<
            root->gold << "\t" << root->silver << "\t" << root->bronze << endl; // print data
            
            if (root->right != NULL) // if there is a next greater element, move there
            {
                cout << endl;
                printInOrder(root->right);
            }
        }
    } // completed with some help from a question by a user on stackoverflow.com
    
    void preOrder(Nodeptr root) {
        if (root != NULL) {
            cout << root->rank << ".\t" << setw(30) << root->country <<
            root->gold << "\t" << root->silver << "\t" << root->bronze << endl;
            
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    
    void postOrder(Nodeptr root) {
        if (root != NULL) {
            postOrder(root->left); // traverse left
            postOrder(root->right); // traverse right
            
            cout << root->rank << ".\t" << setw(30) << root->country <<
            root->gold << "\t" << root->silver << "\t" << root->bronze << endl;
        }
    }
    
    
    Nodeptr copyHelper(const Nodeptr &toCopy) {
        if (toCopy == NULL)
            return NULL; // end point (ends recursive call to left/right)
        
        Nodeptr newNode = new Node;
        
        if (toCopy->rank == NULL) {
            newNode->rank = NULL;
            newNode->country = " ";
            newNode->gold = NULL;
            newNode->silver = NULL;
            newNode->bronze = NULL;
        }
        else {
            string toCopyC = toCopy->country;
            int toCopyR = toCopy->rank;
            int toCopyG = toCopy->gold;
            int toCopyS = toCopy->silver;
            int toCopyB = toCopy->bronze;
            newNode->country = toCopyC;
            newNode->rank = toCopyR;
            newNode->gold = toCopyG;
            newNode->silver = toCopyS;
            newNode->bronze = toCopyB;
            size++;
        }
        
        newNode->left = copyHelper(toCopy->left); // recursive call left, copy values to newNode
        newNode->right = copyHelper(toCopy->right); // "	"	"	right, copy values to newNode
        return newNode; // final result
    }
    
    
    void destructHelper(const Nodeptr &root) {
        if (root != NULL && size > 0) {
            destructHelper(root->left);
            destructHelper(root->right);
            
            delete root;
            size--;
        }
    }
    
    int getHeightHelper(int i, Nodeptr root) {
        if (root != NULL) {
            getHeightHelper(i++, root->left);
            getHeightHelper(i++, root->right);
        }
        return i;
    }
    
    bool isBSTHelper(Nodeptr root, int min, int max) {
        if (root == NULL)
            return true;
        // an empty tree can be a bst (also indicated that we have gone as
        // far left/right as we can go)
        
        if (root->rank < min || root->rank > max)
            return false;
        // root is either less than min or greater than max and
        // is therefore not a binary search tree
        
        return isBSTHelper(root->left, min, max) && isBSTHelper(root->right, min, max);
        // go left and right to compare each element and see that it matched criteria
        
    } // completed with help from an online source
    
    bool searchHelper(int value, Nodeptr root) {
        if (root != NULL) {
            if (value == root->rank || value == root->gold || value == root->silver || value == root->bronze){
                cout << root->rank << ".\t" << setw(30) << root->country <<
                root->gold << "\t" << root->silver << "\t" << root->bronze << endl;
                return true;
            }
            else if (value < root->rank || value < root->gold || value < root->silver || value < root->bronze)
                return searchHelper(value, root->left); //Alex Changes
            else
                return searchHelper(value, root->right);
        }
        else
            return false;
    }
    
    // To recursively find the value (if necessary)
    void RemoveNodeHelper(int rankVal, Nodeptr root) {
        if (root->rank == rankVal)
            RemoveRootMatch();
        else {
            if (rankVal < root->rank && root->left != NULL)
                (root->left->rank == rankVal) ? RemoveMatch(root, root->left, true) : RemoveNodeHelper(rankVal, root->left);
            
            else if (rankVal > root->rank && root->right != NULL)
                (root->right->rank == rankVal) ? RemoveMatch(root, root->right, false) : RemoveNodeHelper(rankVal, root->right);
            else
                cout << "The rank, " << rankVal << ", was not found in the tree." << endl;
        }
    }
    
    // To remove a root's child node
    void RemoveMatch(Nodeptr root, Nodeptr match, bool left) {
        Nodeptr dltNode;
        int matchValue = match->rank;
        Nodeptr smallestInRight;
        string smallestC;
        int smallestR;
        int smallestG;
        int smallestS;
        int smallestB;
        
        
        if (match->left == NULL && match->right == NULL) {
            dltNode = match;
            (left == true) ? root->left = NULL : root->right = NULL;
            delete dltNode;
            size--;
        }
        else if (match->left == NULL && match->right != NULL) {
            (left == true) ? root->left = match->right : root->right = match->right;
            match->right = NULL;
            dltNode = match;
            delete dltNode;
            size--;
        }
        else if (match->right == NULL && match->left != NULL) {
            (left == true) ? root->left = match->left : root->right = match->left;
            match->left = NULL;
            dltNode = match;
            delete dltNode;
            size--;
        }
        else {
            smallestInRight = match->right;
            smallestC = smallestInRight->country;
            smallestR = smallestInRight->rank;
            smallestG = smallestInRight->gold;
            smallestS = smallestInRight->silver;
            smallestB = smallestInRight->bronze;
            while (smallestInRight->left != NULL) {
                smallestInRight = smallestInRight->left;
                smallestC = smallestInRight->country;
                smallestR = smallestInRight->rank;
                smallestG = smallestInRight->gold;
                smallestS = smallestInRight->silver;
                smallestB = smallestInRight->bronze;
            }
            RemoveNodeHelper(smallestInRight->rank, match);
            match->country = smallestC;
            match->rank = smallestR;
            match->gold = smallestG;
            match->silver = smallestS;
            match->bronze = smallestB;
        }
    }
    
    // To remove the root
    void RemoveRootMatch() {
        Nodeptr dltNode = root;
        int rootKey = root->rank;
        Nodeptr smallestInRight;
        string smallestC;
        int smallestR;
        int smallestG;
        int smallestS;
        int smallestB;
        
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
            delete dltNode;
            size--;
        }
        else if (root->left == NULL && root->right != NULL) {
            root = root->right;
            dltNode->right = NULL;
            delete dltNode;
            size--;
        }
        else if (root->right == NULL && root->left != NULL) {
            root = root->left;
            dltNode->left = NULL;
            delete dltNode;
            size--;
        }
        else {
            smallestInRight = root->right;
            smallestC = smallestInRight->country;
            smallestR = smallestInRight->rank;
            smallestG = smallestInRight->gold;
            smallestS = smallestInRight->silver;
            smallestB = smallestInRight->bronze;
            while (smallestInRight->left != NULL) {
                smallestInRight = smallestInRight->left;
                smallestC = smallestInRight->country;
                smallestR = smallestInRight->rank;
                smallestG = smallestInRight->gold;
                smallestS = smallestInRight->silver;
                smallestB = smallestInRight->bronze;
            }
            RemoveNodeHelper(smallestInRight->rank, root);
            root->country = smallestC;
            root->rank = smallestR;
            root->gold = smallestG;
            root->silver = smallestS;
            root->bronze = smallestB;
        }
        
    }
    
    void printLevelOrder(Nodeptr root) {
        if (root != NULL) {
            queue<Nodeptr> Q;
            Q.push(root);
            
            while (!Q.empty()) {
                Nodeptr current = Q.front();
                cout << current->rank << ".\t" << setw(30) << current->country <<
                current->gold << "\t" << current->silver << "\t" << current->bronze << endl;
                
                // put both children (if any) on the queue
                if (current->left != NULL)
                    Q.push(current->left);
                if (current->right != NULL)
                    Q.push(current->right);
                Q.pop(); // move on to next element
            }
        }
    } /* Completed with help from mycodeschool's "Binary tree: Level Order
       Traversal" YouTube video. */
    
    /*vector<string> getNextLineAndSplitIntoTokens(istream& str){
        vector<string> result;
        string line;
        getline(str,line);
        
        stringstream lineStream(line);
        string cell;
        
        while(getline(lineStream,cell,',')){
            result.push_back(cell);
        }
        return result;
    }*/
    
public:
    
    BST();
    BST(const BST &bst);
    ~BST();
    bool isEmpty();
    int getSize();
    void add(string country, int rank, int gold, int silver, int bronze);
    int getRoot();
    void inOrderPrint();
    void preOrderPrint();
    void postOrderPrint();
    
    void levelOrderPrint();
    
    int minimum(); //finds the minimum value in the BST and returns it
    int maximum(); //finds the maximum value in the BST and returns it
    int getHeight(); //recursively finds the height of the tree and returns it
    bool isBST(); //recursively determines whether the tree is a valid BST
    void remove(int value); //removes the specified value from the tree
    bool search(int value); //returns whether the value is in the tree
    
};


void BST::levelOrderPrint() {
    if (size > 0) {
        printLevelOrder(root);
        cout << endl;
    }
    else
        cout << "Cannot print an empty tree." << endl;
}


BST::BST() : size(0), root(NULL) {} // Default Constructor


BST::BST(const BST &toCopy) { // Copy Constructor
    root = copyHelper(toCopy.root);
}

BST::~BST() { // Destructor
    destructHelper(root);
    root = NULL;
}


int BST::minimum() { // Minimum
    int min = root->rank;
    Nodeptr temp = root;
    
    while (temp != NULL) {
        if (temp->rank < min)
            min = temp->rank;
        temp = temp->left;
    }
    return min;
}


int BST::maximum() { // Maximum
    int max = root->rank;
    Nodeptr temp = root;
    
    while (temp != NULL) {
        if (temp->rank > max)
            max = temp->rank;
        temp = temp->right;
    }
    return max;
}


int BST::getHeight() {
    return getHeightHelper(0, root);
}


bool BST::isBST() {
    return isBSTHelper(root, minimum(), maximum());
}


void BST::preOrderPrint() {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        assert(root == NULL);
    }
    else {
        preOrder(root);
        cout << endl;
    }
}


void BST::postOrderPrint() {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        assert(root == NULL);
    }
    else {
        postOrder(root);
        cout << endl;
    }
}



void BST::add(string country, int rank, int gold, int silver, int bronze) {
    if (root == NULL) {
        root = new Node(country, rank, gold, silver, bronze); //if the tree is empty insert the value at the root
        size++;
    }
    else
        addValue(root, country, rank, gold, silver, bronze); //otherwise call the helper function, passing it the root
}


void BST::remove(int rankVal) {
    if (root != NULL) {
        if (root->rank == rankVal) {
            RemoveRootMatch(); // node to be removed is at root
        }
        else {
            if (rankVal < root->rank && root->left != NULL) { 
                (root->left->rank == rankVal) ? RemoveMatch(root, root->left, true) : RemoveNodeHelper(rankVal, root->left);
            }
            else if (rankVal > root->rank && root->right != NULL) {
                (root->right->rank == rankVal) ? RemoveMatch(root, root->right, false) : RemoveNodeHelper(rankVal, root->right);
            }
            else
                cout << "The rank, " << rankVal << ", was not found." << endl;
        }
    }
    else
        cout << "The tree is empty." << endl;
}


bool BST::search(int value) {
    if (isEmpty()) {
        cout << "Tree is empty." << endl;
        return false;
    }
    else {
        if (!searchHelper(value, root)) {
            cout << "Item was not found." << endl;
            return false;
        }
        else
            return true;
    }
}


bool BST::isEmpty() {
    return (size == 0) ? true : false;
}


int BST::getSize() {
    return size;
}


int BST::getRoot() {
    if (isEmpty()) {
        cout << "BST is empty!" << endl;
        return NULL; 
    } else {
        cout << root->rank << ".\t" << setw(30) << root->country <<
        root->gold << "\t" << root->silver << "\t" << root->bronze << endl;
        return root->rank;
    }
}


void BST::inOrderPrint() {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        assert(root == NULL);
    }
    else {
        printInOrder(root);
        cout << endl;
    }
}


#endif