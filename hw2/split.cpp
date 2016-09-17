#include <iostream>
#include <sstream>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void split (Node*& in, Node*& odds, Node*& evens);

///////////////////
void split (Node*& in, Node*& odds, Node*& evens){
    if (in->next == NULL){
        return;
    }
    else{
        if (in->value % 2 == 0) {
            evens = in;
            in = in->next;
            evens->next = NULL;
            split(in, odds, evens->next);
        }
        else if(in->value % 2 != 0){
            odds = in;
            in = in->next;
            odds->next = NULL;
            split(in, odds->next, evens);
        }
        
    }
}
///////////////

