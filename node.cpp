#include "node.h"

Node::Node(){
    N = 0;
}

Node::Node(int i){
    id = i;
}

bool Node::isAdy(Node *theAdy){
    for (int i = 0; i < N; i++){
        if(getNode(i)->getId() == theAdy->getId())
            return true;
    }
    return false;
}

Node::~Node(){
    ady.~vector();
}

void Node::addAdy(Node *newAdy){
    N ++;
    Node::ady.push_back(newAdy);
}

int Node::getN(){
    return N;
}

int Node::getId(){
    return id;
}

Node* Node::getNode(int i){
    if(N == 0) {
        cout << "Adyacentes empty\n";
        return NULL;
        }
    return ady[N-1-i];
}

void Node::printAdy(){
    for(int i = 0; i < N; i++)
        cout << getNode(i)->getId() <<" - ";
    cout << endl;
}