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
};

template <class bstdata>
void BST<bstdata>::addValue(Nodeptr root, bstdata value){
    if (value == root->data){
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

template <class bstdata>
void BST<bstdata>::removeValue(Nodeptr root, bstdata value, Nodeptr prevSave){
    if (root == NULL) {
        cout << "Remove: The value doesn't exist in the tree." << endl;
        return;
    }else if (value < root->data){
        removeValue(root->left, value, root);
    }else if (value > root->data){
        removeValue(root->right, value, root);
    }else{
        if (root->right == NULL && root->left == NULL){
            delete root;
            if (prevSave->left == root) {
                prevSave->left = NULL;
            }else{
                prevSave->right = NULL;
            }
            size--;
        }else if (root->left == NULL && root->right != NULL){
            Nodeptr temp = root;
            root = root->left;
            delete temp;
            size--;
        }else if (root->left != NULL && root->right == NULL){
            Nodeptr temp = root;
            root = root->right;
            delete temp;
            size--;
        }else{
            bstdata minRight = findMin(root->right);
            root->data = minRight;
            removeValue(root->right, minRight, root);
            return;
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
