#include "lliststring.h"
#include <iostream>

using namespace std;
int main() {
  LListString* list = new LListString();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, "Gandalf");

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == "Gandalf") {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // TODO: Continue adding tests for your program, or start your own file with your
  // own tests. Remember to submit a file that is named correctly!
	LListString* myListString = new LListString();
    myListString->insert(0, "first");
    cout << myListString->size() << endl;
    myListString->insert(1, "second");
    cout << myListString->get(1) << endl;
    myListString->remove(0);
    cout << myListString->get(0) << endl;
    myListString->insert(1, "third");
    cout << myListString->get(1) << endl;
    
    
    myListString->set(0, "first");
    cout << myListString->get(0) << endl;
    if (myListString->empty()) cout << "Finally empty!\n";
    else cout << "Not empty!\n";
    myListString->clear();
    if (myListString->empty()) cout << "Finally empty!\n";
    else cout << "Not empty!\n";
    for (int i = 0; i < 10; i++){
    	myListString->insert(i, "full");
    }
    
    cout << endl;
 	for (int i = 0; i < myListString->size(); i++){
 		cout << myListString->get(i) << endl;
 	}
 	int size = myListString->size();
 	for (int i = 0; i < size; i++){
 		myListString->remove(0);
 		cout << myListString->size() << endl;
 	}
 	if (myListString->empty()) cout << "Finally empty!\n";
    else cout << "Not empty!\n";
    for (int i = 0; i < myListString->size(); i++){
 		cout << myListString->get(i) << endl;
 	}
  // Clean up memory.
  delete list;
}
