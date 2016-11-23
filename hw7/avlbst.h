#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "bst.h"

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();
    
    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);
    
    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    
protected:
    int mHeight;
};

/*
 --------------------------------------------
 Begin implementations for the AVLNode class.
 --------------------------------------------
 */

/**
 * Constructor for an AVLNode. Nodes are initialized with a height of 0.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
: Node<Key, Value>(key, value, parent)
, mHeight(0)
{
    
}

/**
 * Destructor.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{
    
}

/**
 * Getter function for the height.
 */
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
 * Setter function for the height.
 */
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
 * Getter function for the parent. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
 * Getter function for the left child. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
 * Getter function for the right child. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
 ------------------------------------------
 End implementations for the AVLNode class.
 ------------------------------------------
 */

/**
 * A templated balanced binary search tree implemented as an AVL tree.
 */
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/removing elements from the tree. You must implement
    // both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);
    
private:
    /* Helper functions are strongly encouraged to help separate the problem
     into smaller pieces. You should not need additional data members. */
    
    // find the height of the node
    int totalHeight(const AVLNode<Key, Value>* root);
    
    /* find the difference in the height of two node
       return > 1 left side is unbalanced, zig left or zag left
       return < -1 right side is unbalanced, zig right or zag right
       if >1 or <-1, diffHeight(mleft or mRight), then
       if return > 0 left side more, zig zig
          return < 0 right side more, zig zag
    */
    int diffHeight(const AVLNode<Key, Value>* lhs, const AVLNode<Key, Value>* rhs);
    
    // zig zig right rotation
    AVLNode<Key, Value>* zig_right_rotation(AVLNode<Key, Value>* parent);
    
    // zig zig left rotation
    AVLNode<Key, Value>* zig_left_rotation(AVLNode<Key, Value>* parent);
    
    // zig zag right rotation
    AVLNode<Key, Value>* zag_right_rotation(AVLNode<Key, Value>* parent);
    
    // zig zag right rotation
    AVLNode<Key, Value>* zag_left_rotation(AVLNode<Key, Value>* parent);
    
    // balance
    AVLNode<Key, Value>* balance(AVLNode<Key, Value>* root);
    
    // insert helper
    AVLNode<Key, Value>* insert_helper(AVLNode<Key, Value>* root,
                                       const std::pair<Key, Value>& keyValuePair,
                                       AVLNode<Key, Value>* parent);
    
    // next largest value
    AVLNode<Key, Value>* nextAVLNode(AVLNode<Key, Value>* ptr);
    
    // find the value
    AVLNode<Key, Value>* findAVLNode(const Key& key);
    
    // remove helper
    AVLNode<Key, Value>* remove_helper(AVLNode<Key, Value>* root, const Key& key);
    
};

/*
 --------------------------------------------
 Begin implementations for the AVLTree class.
 --------------------------------------------
 */

/**
 * Insert function for a key value pair. Finds location to insert the node and then balances the tree.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    this->mRoot = insert_helper(static_cast<AVLNode<Key, Value>*>(this->mRoot), keyValuePair, NULL);
}

/**
 * Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
//    // TODO
//    AVLNode<Key, Value>* curr = findAVLNode(key);
//    if (curr != NULL) {
//        // curr on the leaves
//        if (curr->getLeft() == NULL && curr->getRight() == NULL) {
//            if (curr->getParent() != NULL) {
//                if (curr->getParent()->getLeft() == curr) {
//                    curr->getParent()->setLeft(NULL);
//                }
//                else if (curr->getParent()->getRight() == curr){
//                    curr->getParent()->setRight(NULL);
//                }
//            }
//            delete curr;
//            return;
//        }
//        
//        AVLNode<Key, Value>* next = nextAVLNode(curr);
//        curr->getItem().first = next->getItem().second;
//        curr->getItem().second = next->getItem().second;
//        AVLNode<Key, Value>* parent = next->getParent();
//        if (parent->getLeft() == next) {
//            parent->setLeft(NULL);
//        }
//        else if (parent->getRight() == next){
//            parent->setRight(NULL);
//        }
//        
//        if (next->getRight() != NULL) {
//            parent->setRight(next->getRight());
//            next->getRight()->setParent(parent);
//        }
//        
//        delete next;
//        next = NULL;
//        balance(parent);
//    }
//    else
//        std::cout << "Key not found\n";
//        return;
    this->mRoot = remove_helper(static_cast<AVLNode<Key, Value>*>(this->mRoot), key);
    
}

/*
 -------------Begin implementations for the helper function------------
 */
// different height from left to right
template<typename Key, typename Value>
int AVLTree<Key, Value>::diffHeight(const AVLNode<Key, Value>* lhs, const AVLNode<Key, Value>* rhs){
    int l_height = totalHeight(lhs);
    int r_height = totalHeight(rhs);
    return l_height - r_height;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::totalHeight(const AVLNode<Key, Value>* root){
    int height = 0;
    if (root != NULL) {
        int left_height = totalHeight(root->getLeft());
        int right_height = totalHeight(root->getRight());
        int max_height = std::max(left_height, right_height);
        height = max_height + 1;
    }
    return height;
}

// zig zig right rotation
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::zig_right_rotation(AVLNode<Key, Value>* parent){
    AVLNode<Key, Value>* temp;
    temp = parent->getRight();
    temp->setParent(parent->getParent());
    if (temp->getParent() != NULL) {
        if (temp->getParent()->getLeft() != NULL) {
            if (temp->getParent()->getLeft() == parent) {
                temp->getParent()->setLeft(temp);
            }
        }
        else if (temp->getParent()->getRight() != NULL){
            if (temp->getParent()->getRight() == parent) {
                temp->getParent()->setRight(temp);
            }
        }
    }
    parent->setRight(temp->getLeft());
    if (temp->getLeft() != NULL) {
        temp->getLeft()->setParent(parent);
    }
    temp->setLeft(parent);
    parent->setParent(temp);
    return temp;
}

// zig zig left rotation
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::zig_left_rotation(AVLNode<Key, Value>* parent){
    AVLNode<Key, Value>* temp;
    temp = parent->getLeft();
    temp->setParent(parent->getParent());
    if (temp->getParent() != NULL) {
        if (temp->getParent()->getLeft() != NULL) {
            if (temp->getParent()->getLeft() == parent) {
                temp->getParent()->setLeft(temp);
            }
        }
        else if (temp->getParent()->getRight() != NULL){
            if (temp->getParent()->getRight() == parent) {
                temp->getParent()->setRight(temp);
            }
        }
    }
    parent->setLeft(temp->getRight());
    if (temp->getRight() != NULL) {
        temp->getRight()->setParent(parent);
    }
    temp->setRight(parent);
    parent->setParent(temp);
    return temp;
}

// zig zag right rotation
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::zag_right_rotation(AVLNode<Key, Value>* parent){
    AVLNode<Key, Value>* temp;
    temp = parent->getRight();
    parent->setRight(zig_left_rotation(temp));
    return zig_right_rotation(parent);
}

// zig zag left rotation
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::zag_left_rotation(AVLNode<Key, Value>* parent){
    AVLNode<Key, Value>* temp;
    temp = parent->getLeft();
    parent->setLeft(zig_right_rotation(temp));
    return zig_left_rotation(parent);
}

// balance
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::balance(AVLNode<Key, Value>* root){
    int diff = diffHeight(root->getLeft(), root->getRight());
    if (diff > 1) {
        if (diffHeight(root->getLeft()->getLeft(), root->getLeft()->getRight()) > 0){
            // zig zig left
            //std::cout << "Zig Zig Left" << std::endl;
            root = zig_left_rotation(root);
        }
        else{
            // zig zag left
            //std::cout << "Zig Zag Left" << std::endl;
            root = zag_left_rotation(root);
        }
    }
    else if (diff < -1){
        if (diffHeight(root->getRight()->getLeft(), root->getRight()->getRight()) > 0){
            // zig zag right
            //std::cout << "Zig Zag Right" << std::endl;
            root = zag_right_rotation(root);
        }
        else{
            // zig zig right
            //std::cout << "Zig Zig Right" << std::endl;
            root = zig_right_rotation(root);
        }

    }
    return root;
}

// insert helper
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::insert_helper(AVLNode<Key, Value>* root,
                                                       const std::pair<Key, Value>& keyValuePair, AVLNode<Key, Value>* parent)
{
    
    if (root == NULL) {
        root = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
        root->setLeft(NULL);
        root->setRight(NULL);
        return root;
    }
    else if (keyValuePair.first < root->getKey()){
        root->setLeft(insert_helper(root->getLeft(), keyValuePair, root));
        root = balance(root);
    }
    else if (keyValuePair.first > root->getKey()){
        root->setRight(insert_helper(root->getRight(), keyValuePair, root));
        root = balance(root);
    }
    else if (keyValuePair.first == root->getKey()){
        root->setValue(keyValuePair.second);
    }
    return root;
}

// next largest value
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::nextAVLNode(AVLNode<Key, Value>* ptr){
    if (ptr->getRight() != NULL) {
        ptr = ptr->getRight();
        while (ptr->getLeft() != NULL) {
            ptr = ptr->getLeft();
        }
        return ptr;
    }
    while (ptr->getParent() != NULL) {
        if (ptr->getParent()->getLeft() == ptr) {
            return ptr->getParent();
        }
        ptr = ptr->getParent();
    }
    return NULL;
}

// find the value
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::findAVLNode(const Key& key){
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->mRoot);
    while (curr)
    {
        if (curr->getKey() == key)
        {
            return curr;
        }
        else if (key < curr->getKey())
        {
            curr = curr->getLeft();
        }
        else
        {
            curr = curr->getRight();
        }
    }
    return NULL;
}

// remove helper
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::remove_helper(AVLNode<Key, Value>* root, const Key& key){
    if (root == NULL) {
        return NULL;
    }
    
    
    if (key < root->getKey()) {
        root->setLeft(remove_helper(root->getLeft(), key));
    }
    else if (key > root->getKey()) {
        root->setRight(remove_helper(root->getRight(), key));
    }
    
    else{
        if (root->getLeft() == NULL || root->getRight() == NULL) {
            AVLNode<Key, Value>* temp = NULL;
            if (root->getLeft() == NULL && root->getRight() != NULL) {
                temp = root->getRight();
            }
            else if (root->getLeft() != NULL && root->getRight() == NULL) {
                temp = root->getLeft();
            }
            
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else{
                AVLNode<Key, Value>* temp_parent = root->getParent();
                *root = *temp;
                root->setParent(temp_parent);
            }
            //delete temp;
        }
        else{
            AVLNode<Key, Value>* temp = nextAVLNode(root);
            root->getItem().first = temp->getItem().first;
            root->getItem().second = temp->getItem().second;
            
            root->setRight(remove_helper(root->getRight(), temp->getKey()));
        }
    }
    
    if (root == NULL) {
        return root;
    }
    
    return balance(root);
}

/*
 -------------End implementations for the helper function------------
 */

/*
 ------------------------------------------
 End implementations for the AVLTree class.
 ------------------------------------------
 */

#endif