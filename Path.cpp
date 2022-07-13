#include "Path.h"

Path::Path(int large){
    N = large;
    taken = new int[large];
    path = new Node*[large];
    position = 0;
}
Path::~Path(){
}

void Path::add(Node *newNode){
    path[position] = newNode;
    taken[newNode->getId()] = 1;
    position ++;
}

Node* Path::getHighestDegree(){
    Node *selected = path[1];
    for (int i = 2; i < position-1; i++){
        if(path[i]->getN() == N)
            return path[i];
        if(selected->getN() < path[i]->getN())
            selected = path[i];
    }
    return selected;
}

bool Path::istaken(Node *theNode){
    return taken[theNode->getId()] == 1;
}

Node *Path::getHead(){
    return path[position];
}

int Path::getLength(){
    return position;
}

