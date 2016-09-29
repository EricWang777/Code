#include "lliststring.h"
#include <cstdlib>
#include <stdexcept> // See the comment directly below.

/**
 * This implementation uses exceptions in both versions of 'get'. 
 * You do not need to change the if-statements that use exceptions, 
 * nor do you need to test for exceptions. 
 *
 * In case you are interested, you can find more information here:
 * http://www.cplusplus.com/doc/tutorial/exceptions/
 * 
 * We will cover exceptions later this semester. 
 */

LListString::LListString()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListString::~LListString()
{
  clear();
}

bool LListString::empty() const
{
  return (size_ == 0);
}

int LListString::size() const
{
  return size_;
}

void LListString::insert(int pos, const std::string& val)
{
  // TODO: complete the insert function.
    if (pos < 0 || pos > size_) {
        throw std::invalid_argument("bad location to be inserted");
    }
    
    Item* newNode = new Item;
    newNode->val = val;
    if (empty()) {
        newNode->next = NULL;
        newNode->prev = NULL;
        head_ = newNode;
        tail_ = newNode;
    }
    else if (pos == 0){ // the first one
        newNode->prev = NULL;
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
    }
    else if (pos == size_){ // the last one
        newNode->next = NULL;
        newNode->prev = tail_;
        tail_->next = newNode;
        tail_ = newNode;
    }
    else{
        Item* toInsert = getNodeAt(pos);
        newNode->prev = toInsert->prev;
        newNode->next = toInsert;
        toInsert->prev->next = newNode;
        toInsert->prev = newNode;
    }
    size_++;
}

void LListString::remove(int pos)
{
  // TODO: complete the remove function.
    
    if (pos < 0 || pos >= size_) {
        throw std::invalid_argument("bad location to be removed");
    }
    if (size_ == 0) {
        throw std::invalid_argument("cannot remove empty linkedlist");
    }
    Item* toRemove = getNodeAt(pos);
    if (toRemove->prev) toRemove->prev->next = toRemove->next;
    else head_ = head_->next;
    if (toRemove->next) toRemove->next->prev = toRemove->prev;
    else tail_ = tail_->prev;
    delete toRemove;
    size_--;
}



void LListString::set(int pos, const std::string& val)
{
  if(pos >= 0 && pos < size_) {
  	Item *temp = getNodeAt(pos);
    temp->val = val;	
  }
}

std::string& LListString::get(int pos)
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

std::string const & LListString::get(int pos) const
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

void LListString::clear()
{
  while(head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListString::Item* LListString::getNodeAt(int pos) const
{
  // TODO: complete the getNodeAt function.
    // consideration: pos < 0; pos >= size
    if (pos < 0 || pos >= size_) {
        throw std::invalid_argument("bad location in getNodeAt");
    }
    else{
        int i = 0;
        Item* reval = head_;
        while (i < pos) {
            reval = reval->next;
            i++;
        }
        return reval;
    }

}

///////////////////// HW3
LListString::LListString (const LListString& other){
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    for (int i = 0; i < other.size(); ++i) {
        this->insert(i, other.get(i));
    }
}

LListString& LListString::operator = (const LListString& other){
    
    if (this == &other) {
        return *this;
    }
    else {
        this->clear();
        for (int i = 0; i < other.size(); ++i) {
            this->insert(i, other.get(i));
        }
        return *this;
    }
}

std::string const & LListString::operator[] (int pos) const{
    return get(pos);
}

LListString LListString::operator+ (const LListString& other) const{
    LListString newCopy = LListString(*this);
    
    for (int i = 0; i < other.size(); ++i) {
        newCopy.insert(newCopy.size(), other.get(i));
    }
    
    return newCopy;
}
//////////////////// HW3









