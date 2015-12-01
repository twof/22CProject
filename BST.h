//
//  BST.h
//  BST
//
//  Created by fnord on 10/21/15.
//  Copyright © 2015 fnord. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include <cstddef>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

template <class bstdata>
class BST{
private:
    struct Node
    {
        bstdata data;
        int distance;
        Node* parent;
        Node* left;
        Node* right;
        
        Node(): left(NULL), right(NULL){}
        Node(bstdata newdata): left(NULL), right(NULL), data(newdata){}
    };
    
    typedef struct Node* Nodeptr;
    
    Nodeptr root;
    int size;
    
    /**Private helper functions*/
    
    void addValue(Nodeptr root, bstdata value);
    void removeValue(Nodeptr root, bstdata value, Nodeptr prevSave);
    void printInOrder(Nodeptr root);
    void preOrderPrint(Nodeptr root);
    void postOrderPrint(Nodeptr root);
    bool containsValue(Nodeptr root, bstdata data);
    void deleteTree(Nodeptr root);
    bstdata findMin(Nodeptr root);
    bstdata findMax(Nodeptr root);
    int getHeight(Nodeptr root);
    void printLevelOrder(Nodeptr root, queue<Nodeptr> NPQueue);
    void initilizeAdjacency(Nodeptr root);
    bstdata getNodeHelper(Nodeptr root, bstdata data);
    
    
public:
    BST();
    BST(BST<bstdata> const &bst); //
     ~BST();
    bool isEmpty();
    int getSize();
    int getHeight(); //
    void add(bstdata value);
    void remove(bstdata value);
    bstdata getRoot();
    void inOrderPrint();
    void postOrderPrint();
    void preOrderPrint();
    bool contains(bstdata data);
    bool isBST();
    bstdata minimum();
    bstdata maximum();
    void levelOrderPrint();
    bstdata getNode(bstdata data);
};

template <class bstdata>
void BST<bstdata>::addValue(Nodeptr root, bstdata value){
    if (is_pointer<bstdata>::value) {
        if (*value == *root->data){
            cout << "AddValue: Item is already in tree" << endl;
            return;
        }
        
        if (*value < *root->data){
            if(root->left == NULL){
                root->left = new Node(value);
                size++;
            }else{
                addValue(root->left, value);
            }
        }else{
            if (root->right == NULL){
                root->right = new Node(value);
                size++;
            }else{
                addValue(root->right, value);
            }
        }
    }else{
        
        if (value == root->data){
            cout << "AddValue: Item is already in tree" << endl;
            return;
        }
        
        if (value < root->data){
            if(root->left == NULL){
                root->left = new Node(value);
                size++;
            }else{
                addValue(root->left, value);
            }
        }else{
            if (root->right == NULL){
                root->right = new Node(value);
                size++;
            }else{
                addValue(root->right, value);
            }
        }
    }
}


template <class bstdata>
BST<bstdata>::BST(): size(0), root(NULL) {}

template <class bstdata>
BST<bstdata>::~BST(){
    deleteTree(root);
    
}

template <class bstdata>
BST<bstdata>::BST(BST<bstdata> const &bst){
    Nodeptr temp = *new Nodeptr(bst->getRoot);
    add(bst->getRoot());
    while (temp != NULL) {
        
    }
}

template <class bstdata>
bstdata BST<bstdata>::getNode(bstdata data){
    return getNodeHelper(this->root, data);
}

template <class bstdata>
bstdata BST<bstdata>::getNodeHelper(Nodeptr root, bstdata data){
    if (is_pointer<bstdata>::value) {
		if (*data == *root->data) {
            return root->data;
        }
		if (*data < *root->data) {
            if (root->left == NULL) {
                return NULL;
            }else{
                return getNodeHelper(root->left, data);
            }
        }else{
            if (root->right == NULL) {
                return NULL;
            }else{
                return getNodeHelper(root->right, data);
            }
        }
//      return NULL;
    }else{
        if (root->data == data) {
            return root->data;
        }
        if (root->data > data) {
            if (root->left == NULL) {
                return NULL;
            }else{
                return getNodeHelper(root->left, data);
            }
        }else if (root->data < data){
            if (root->right == NULL) {
                return NULL;
            }else{
                return getNodeHelper(root->right, data);
            }
        }
        return NULL;
    }
}

template<class bstdata>
void BST<bstdata>::deleteTree(Nodeptr root){
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
    }else{
        delete root;
    }
}

template <class bstdata>
int BST<bstdata>::getHeight(Nodeptr root){
    if (root == NULL) {
        return -1;
    }
    int rightHeight = getHeight(root->right);
    int leftHeight = getHeight(root->left);
    
    if (rightHeight > leftHeight) {
        return rightHeight + 1;
    }else{
        return leftHeight + 1;
    }
}

template <class bstdata>
bstdata BST<bstdata>::minimum(){
    if (root == NULL){
        cout << "Minimum: Tree is empty" << endl;
        //will need to include cstdlib for exit below
        exit(-1); //you can also use assert here if desired
    }else{
        return findMin(root);
    }
}

template <class bstdata>
bstdata BST<bstdata>::maximum(){
    if (root == NULL) {
        cout << "Maximum: Tree is empty" << endl;
        exit(-1);
    }else{
        return findMax(root);
    }
}



template<class bstdata>
bstdata BST<bstdata>::findMin(Nodeptr root){
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

template<class bstdata>
bstdata BST<bstdata>::findMax(Nodeptr root){
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

template <class bstdata>
bool BST<bstdata>::isEmpty(){
    return size==0;
}

template <class bstdata>
int BST<bstdata>::getSize(){
    return size;
}

template <class bstdata>
void BST<bstdata>::add(bstdata value){
    if (root == NULL){
        root = new Node(value); //if the tree is empty insert the value at the root
        size++;
    }else
        addValue(root, value); //otherwise call the helper function, passing it the root
}

template <class bstdata>
bstdata BST<bstdata>::getRoot(){
    return this->root->data;
}

template <class bstdata>
void BST<bstdata>::inOrderPrint() {
    printInOrder(root);
}

template <class bstdata>
void BST<bstdata>::printInOrder(Nodeptr root) {
    if (root->left !=  NULL) {
        printInOrder(root->left);
    }
    cout << root->data << endl;
    if (root->right != NULL) {
        printInOrder(root->right);
    }
}

template <class bstdata>
void BST<bstdata>::preOrderPrint(Nodeptr root){
    if (root != NULL) {
        cout << root->data << endl;
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }
}

template <class bstdata>
void BST<bstdata>::postOrderPrint(Nodeptr root){
    if (root != NULL) {
        postOrderPrint(root->left);
        postOrderPrint(root->right);
        cout << root->data << endl;
    }
}


template <class bstdata>
void BST<bstdata>::postOrderPrint(){
    postOrderPrint(this->root);
}


template <class bstdata>
void BST<bstdata>::preOrderPrint(){
    preOrderPrint(this->root);
}

template <class bstdata>
bool BST<bstdata>::contains(bstdata data){
    return containsValue(this->root, data);
}


template <class bstdata>
bool BST<bstdata>::containsValue(Nodeptr root, bstdata data){
    if (is_pointer<bstdata>::value) {
        if (*root->data == *data) {
            return true;
        }
        if (*root->data > *data) {
            if (root->left == NULL) {
                return false;
            }else{
                if(containsValue(root->left, data)){
                    return true;
                }
            }
        }else{
            if (root->right == NULL) {
                return false;
            }else{
                if(containsValue(root->right, data)){
                    return true;
                }
            }
        }
        return false;
    }else{
        if (root->data == data) {
            return true;
        }
        if (root->data > data) {
            if (root->left == NULL) {
                return false;
            }else{
                if(containsValue(root->left, data)){
                    return true;
                }
            }
        }else if (root->data < data){
            if (root->right == NULL) {
                return false;
            }else{
                if(containsValue(root->right, data)){
                    return true;
                }
            }
        }
        return false;
    }
}

template <class bstdata>
void BST<bstdata>::removeValue(Nodeptr rootptr, bstdata value, Nodeptr prevSave){
    if (is_pointer<bstdata>::value) {
        if (rootptr == NULL) {
            cout << "Remove: The value doesn't exist in the tree." << endl;
            return;
        }else if (*value < *rootptr->data){
            removeValue(rootptr->left, value, rootptr);
        }else if (*value > *rootptr->data){
            removeValue(rootptr->right, value, rootptr);
        }else{
            if (rootptr->right == NULL && rootptr->left == NULL){
                if(prevSave == NULL){
                    this->root = nullptr;
                }else if (prevSave->left == rootptr) {
                    prevSave->left = NULL;
                }else{
                    prevSave->right = NULL;
                }
                delete rootptr;
                size--;
            }else if (rootptr->left == NULL && rootptr->right != NULL){
                if(prevSave == NULL){
                    this->root = rootptr->right;
                }else if (prevSave->left == rootptr) {
                    prevSave->left = rootptr->right;
                }else{
                    prevSave->right = rootptr->right;
                }
                delete rootptr;
                size--;
            }else if (rootptr->left != NULL && rootptr->right == NULL){
                if(prevSave == NULL){
                    this->root = rootptr->left;
                }else if (prevSave->left == rootptr) {
                    prevSave->left = rootptr->left;
                }else{
                    prevSave->right = rootptr->left;
                }
                delete rootptr;
                size--;
            }else{
                bstdata minRight = findMin(rootptr->right);
                rootptr->data = minRight;
                removeValue(rootptr->right, minRight, rootptr);
                return;
            }
        }
    }else{
        if (rootptr == NULL) {
            cout << "Remove: The value doesn't exist in the tree." << endl;
            return;
        }else if (value < rootptr->data){
            removeValue(rootptr->left, value, rootptr);
        }else if (value > rootptr->data){
            removeValue(rootptr->right, value, rootptr);
        }else{
            if (rootptr->right == NULL && rootptr->left == NULL){
                delete rootptr;
                if (prevSave->left == rootptr) {
                    prevSave->left = NULL;
                }else{
                    prevSave->right = NULL;
                }
                size--;
            }else if (rootptr->left == NULL && rootptr->right != NULL){
                Nodeptr temp = rootptr;
                rootptr = rootptr->left;
                delete temp;
                size--;
            }else if (rootptr->left != NULL && rootptr->right == NULL){
                Nodeptr temp = rootptr;
                rootptr = rootptr->right;
                delete temp;
                size--;
            }else{
                bstdata minRight = findMin(rootptr->right);
                rootptr->data = minRight;
                removeValue(rootptr->right, minRight, rootptr);
                return;
            }
        }
    }
}

template <class bstdata>
void BST<bstdata>::remove(bstdata value){
    if (size == 0) {
        cout << "can't remove from an empty tree" << endl;
    }else{
        removeValue(root, value, NULL);
    }
}

template <class bstdata>
void BST<bstdata>::printLevelOrder(Nodeptr root, queue<Nodeptr> nodeptrQueue){
    cout << root->data << endl;
    
    if (root->left != NULL) {
        nodeptrQueue.push(root->left);
    }
    if(root->right != NULL) {
        nodeptrQueue.push(root->right);
    }
    
    nodeptrQueue.pop();
    if (!nodeptrQueue.empty()) {
        printLevelOrder(nodeptrQueue.front(), nodeptrQueue);
    }
}

template<class bstdata>
void BST<bstdata>::initilizeAdjacency(Nodeptr root){
    if (root->left !=  NULL) {
        initilizeAdjacency(root->left);
    }
    root->distance = -1;
    root->parent = NULL;
    if (root->right != NULL) {
        initilizeAdjacency(root->right);
    }
}

template<class bstdata>
void BST<bstdata>::levelOrderPrint(){
    queue<Nodeptr> nodeptrQueue;
    nodeptrQueue.push(root);
    initilizeAdjacency(root);
    printLevelOrder(root, nodeptrQueue);
}

#endif /* BST_h */
