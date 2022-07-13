#include "graph.h"

Graph::Graph(){
}
Graph::Graph(int cant, float p){
    srand(time(NULL));
    Graph::N = cant;
    Graph::nodes = new Node*[cant];
    
    for (int i = 0; i < N; i++)
        nodes[i] = new Node(i);
    for(int i = 0; i < N; i++)
        for(int j = i + 1; j < N; j++)
            if((double(rand())/RAND_MAX) < p){
                nodes[i]->addAdy(nodes[j]);
                nodes[j]->addAdy(nodes[i]);
            }
}

Graph::~Graph(){
    delete[] nodes;
}

int Graph::getN(){
    return N;
}

Node *Graph::getNode(int i){
    return nodes[i];
}

void Graph::print(){
    for(int i = 0; i < N; i++){
        cout << nodes[i]->getId()<<".-> "<< nodes[i]->getN()<< "->";
        nodes[i]->printAdy();
    }
    cout << endl;
}

Node **Graph::getAllNodes(){
    return nodes;
}

