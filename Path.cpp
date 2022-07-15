#include "Path.h"

Path::Path(int large){
    N = large;
    taken = new bool[large];
    path = new Node*[large];
    position = 0;
}
Path::~Path(){
    delete[] taken;
    delete[] path;
}

void Path::add(Node *newNode){
    path[position] = newNode;
    taken[newNode->getId()] = 1;
    position ++;
}

Node *Path::getNode(int val){
    return path[val];
}

int Path::getHighestDegree(){
    int selected = 0;
    for (int i = 1; i < position-1; i++){
        if(path[i]->getN() == N)
            return i;
        if(path[selected]->getN() < path[i]->getN())
            selected = i;
    }
    return selected;
}

int Path::getSmallestDegree(){
    int selected = 0;
    for (int i = 1; i < position-1; i++){
        if(path[i]->getN() == N)
            return i;
        if(path[selected]->getN() > path[i]->getN())
            selected = i;
    }
    return selected;
}

bool Path::isTaken(Node *theNode){
    return taken[theNode->getId()];
}

Node *Path::getHead(){
    return path[position-1];
}

int Path::getLength(){
    return position;
}

void Path::print(){
    for (int i = 0; i < position; i++)
    {
        cout << getNode(i)->getId() << "-";
    }
    cout << endl;
    
}

