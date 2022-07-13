#include "Solver.h"

Solver::Solver(Graph *objective){
    graph = objective;
    solution = new Path(objective->getN());
}

void Solver::sort(){
    quickSort solver;
    solver.solve(graph->getAllNodes(), graph->getN());
}

Solver::~Solver(){
    solution->~Path();
}

/*Considerar que es posible verificar planteamientos en esta parte,
es decir, aprovechar iteraciones para verificar cosas*/

Node *Solver::getSmallestDegreeFromNode(Node *theNode, Path *posiblyPath){
    int N = theNode->getN(), position = 0;
    Node *selected = nullptr;
    //Primer for para encontrar un nodo no tomado
    for (int i = 0; i < N; i++){
        position = i;
        if(!posiblyPath->istaken(theNode->getNode(i))){
            selected = theNode->getNode(i);
            i=N;
        }
    }

    // For para determinar un nodo menor que el seleccionado
    for(int i = position+1; i < N; i++){
        if(theNode->getNode(i)->getN() < selected->getN() && !posiblyPath->istaken(theNode->getNode(i))){
            selected  = theNode->getNode(i);
        }
            
    }
    return selected;
}

Path *Solver::getPathForHighestDegree(Node *start){
    Path *posiblyPath = new Path(graph->getN());
    posiblyPath->add(start);
    while (1){
        start = getSmallestDegreeFromNode(start, posiblyPath);
        if(start){
            posiblyPath->add(start);
        }else{
            return posiblyPath;
        }
    }
}

void Solver::getLongestPathForHighestDegree(){
    solution = getPathForHighestDegree(graph->getNode(graph->getN()-1));
    cout << "First solution: "<< solution->getLength()<<endl;

    Path *posiblyPath, *aux;
    int highest =graph->getNode(graph->getN()-1)->getN(), i = 2;

    while(graph->getNode(graph->getN()-i)->getN() == highest){
        posiblyPath = getPathForHighestDegree(graph->getNode(graph->getN()-i));
        if(posiblyPath->getLength() > solution->getLength()){
            cout << "Another selected: "<< posiblyPath->getLength()<<endl;
            aux = solution;
            solution = posiblyPath;
            aux->~Path();
        }else{
            cout << "Else : Not seleected: "<< posiblyPath->getLength()<<endl;
            posiblyPath->~Path();
        }
        i++;
        if(i > graph->getN())
            break;
    }
}



void Solver::solve(){
    sort();
    graph->print();
    getLongestPathForHighestDegree();

    
/*     
    Node* selected = graph->getNode(graph->getN()-1);
    solution->add(selected);
    graph->print();
    if(i != graph->getN()){

    } */
}