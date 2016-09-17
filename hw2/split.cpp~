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
void printLL(Node* in){
    while (in != NULL){
        cout << in->value << " ";
        in = in->next;
    }
    cout << endl;
}

int main(){
    // create a linklist
    Node* in = new Node;
    Node* odd = new Node;
    Node* even = new Node;
    in->value = 0;
    in->next = NULL;
    //int num;
    Node* head = in;
    
    for (int i = 1; i < 20; i ++) {
        
        
        Node* nNode = new Node;
        nNode->value = i;
        nNode->next = NULL;
        in->next = nNode;
        in = in->next;
        
    }
    
    printLL(head);
    split(head, odd, even);
    
    
    //print Node
    
    printLL(even);
    printLL(odd);
    
    return 0;
}

