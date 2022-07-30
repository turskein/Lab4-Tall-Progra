#include "Path.h"

Path::Path(int large, Node **allNodes){
    N = large;
    taken = new bool[large];
    path = new Node*[large];
    freeAdy = new int[large];
    position = new int[large];
    head = 0;
    for(int i = 0; i < large; i ++)
        freeAdy[allNodes[i]->getId()] = allNodes[i]->getN();
    
}
Path::~Path(){
    delete[] taken;
    delete[] path;
    delete[] freeAdy;
    delete[] position;
}

void Path::add(Node *newNode){
    path[head] = newNode;
    taken[newNode->getId()] = 1;
    position[newNode->getId()] = head;
    for (int i = 0; i < newNode->getN(); i++)
        freeAdy[newNode->getNode(i)->getId()]--;
    head ++;
}

Node *Path::getNode(int position){
    return path[position];
}

int Path::getHighestDegreeNode(){
    int selected = 0;
    for (int i = 1; i < head-1; i++){
        if(path[i]->getN() == N)
            return i;
        if(path[selected]->getN() < path[i]->getN())
            selected = i;
    }
    return selected;
}

int Path::getSmallestDegreeNode(){
    int selected = 0;
    for (int i = 1; i < head-1; i++){
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
    return path[head-1];
}

int Path::getLength(){
    return head;
}

int Path::getFreeAdy(int position){
    return freeAdy[getNode(position)->getId()];
}

int Path::getFreeAdyById(Node *theNode){
    return freeAdy[theNode->getId()];
}

int Path::getPositionByNode(Node *theNode){
    if(taken[theNode->getId()])
        return position[theNode->getId()];
    return -1;
}

void Path::print(){
    for (int i = 0; i < head; i++)
    {
        cout << getNode(i)->getId() << "-";
    }
    cout << endl;
}

void Path::printFreeAdj(){
    for (int i = 0; i < N; i++)
    {
        cout << GREEN << i << RESET <<" -> " << RED << freeAdy[i]<<RESET<<" ## ";
    }
    cout <<endl;
    
}

