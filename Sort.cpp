#include "Sort.h"

Sort::Sort(Graph *objective){
    Sort::objective = objective;
    sizeGraph = objective->getN();
}
Sort::~Sort(){

}
bool Sort::verifyAllNodes(){
    if(objective->getNode(0)->getN() > 1){
        majorDegreeNode = objective->getNode(0)->getN();
    }else{
        return false;
    }

    for (int i = 1; i < sizeGraph; i++){
        if(objective->getNode(i)->getN() > 1){
            if(objective->getNode(i)->getN() > majorDegreeNode){
                majorDegreeNode = objective->getNode(i)->getN();
            }
        }else{
            return false;
        }
    }
    return true;
}

void Sort::solve(){
    Node *theNode, *aux;
    int position, index = 0, c;
    stacks = new Node*[majorDegreeNode-1];
    int *indices = new int[majorDegreeNode];

    for (int i = 0; i < majorDegreeNode-1; i++)
    {
        indices[i] = 0;
    }
    
    for (int i = 0; i < sizeGraph; i++){
        theNode = objective->getNode(i);
        position = theNode->getN()-2;
        aux = stacks[position];
        stacks[position] = theNode;
        indices[position]++;
        theNode->stacker(aux);
    }

    Node **theNodes = objective->getAllNodes();
    for (int i = 0; i < majorDegreeNode-1; i++){
        while(0 < indices[i]){
            theNodes[index] = stacks[i];
            index++;
            stacks[i] = stacks[i]->getNext();
            indices[i]--;
        }
        if(index == sizeGraph) return;
    }
    delete[] stacks;
    delete[] indices;
}