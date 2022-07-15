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

Graph::Graph(char p[]){
    int i = 0, node1, node2;
    int dimension;
    char peo[100];
    FILE * file = fopen(p,"r");
    if(file == NULL){
        cout << "Error al abrir el archivo"<<endl;
        exit(0);
    }
    while(i < 19){
        if(i == 14){
            fscanf(file,"%d",&dimension);
        }else{
            fscanf(file,"%s",peo);
        }
        i++;
    }
    N = dimension;
    nodes = new Node*[dimension];
    for (i = 0; i < N; i++)
        nodes[i] = new Node(i);
    i = 0;
    
    while (1){
        fscanf(file,"%d %d",&node1,&node2);
        if(node1 == -1){
            break;
        }else{
            nodes[node1-1]->addAdy(nodes[node2-1]);
            nodes[node2-1]->addAdy(nodes[node1-1]);
        }
        i++;
    }
}

Graph::~Graph(){

}

int Graph::getN(){
    return N;
}

Node *Graph::getNode(int i){
    return nodes[i];
}

void Graph::print(){
    for(int i = 0; i < N; i++){
        cout << nodes[i]->getId()<<".-> "<< nodes[i]->getN()<< "-> ";
        nodes[i]->printAdy();
    }
    cout << endl;
}

Node **Graph::getAllNodes(){
    return nodes;
}

