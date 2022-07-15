#include "Solver.h"

Solver::Solver(Graph *objective){
    sizeGraph = objective->getN();
    graph = objective;
    solution = new Path(sizeGraph);
    freeAdy = new int[sizeGraph];
}

void Solver::sort(){
    quickSort solver;
    solver.solve(graph->getAllNodes(), sizeGraph);
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
        if(!posiblyPath->isTaken(theNode->getNode(i))){
            selected = theNode->getNode(i);
            i=N;
        }
    }

    // For para determinar un nodo menor que el seleccionado
    for(int i = position+1; i < N; i++){
        if(theNode->getNode(i)->getN() < selected->getN() && !posiblyPath->isTaken(theNode->getNode(i))){
            selected  = theNode->getNode(i);
        }
    }
    return selected;
}

void Solver::invertSol(){
    Path *posiblyPath = new Path(sizeGraph), *aux;
    for (int i = solution->getLength()-1; i >= 0; i++){
        posiblyPath->add(solution->getNode(i));
    }
    aux = solution;
    solution = posiblyPath;
    aux->~Path();
}

Path *Solver::getPathForHighestDegree(Node *start){
    Path *posiblyPath = new Path(sizeGraph);
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
    solution = getPathForHighestDegree(graph->getNode(sizeGraph-1));
    
    Path *posiblyPath, *aux;
    int highest =graph->getNode(sizeGraph-1)->getN(), i = 2;

    while(graph->getNode(sizeGraph-i)->getN() == highest){
        posiblyPath = getPathForHighestDegree(graph->getNode(sizeGraph-i));
        if(posiblyPath->getLength() > solution->getLength()){
            aux = solution;
            solution = posiblyPath;
            aux->~Path();
        }else{
            posiblyPath->~Path();
        }
        i++;
        if(i > sizeGraph)
            break;
    }
}

bool Solver::rotationalTransformation(int opt){
    //Largo de la solucion
    int lengthSolution = solution->getLength(), i;
    // Indexacion de nodo seleccionado
    int selectedForNewEnd = -1;
    // Se usara bastante el nodo final de camino actual
    Node*head = solution->getHead();
    if(!(solution->getLength()>0))
        return false;

    if(opt == 1){    // Seleccion del nodo con mayor cantidad de adyacentes libres
        if (freeAdy[solution->getNode(0)->getId()] > 0)
            selectedForNewEnd = 0;
        else
            for (i = 1; i < lengthSolution; i++){
                // Verificar que el anterior nodo anterior es adyacente al actual nodo final
                if(freeAdy[solution->getNode(i)->getId()] > 0 && head->isAdy(solution->getNode(i-1))){
                    selectedForNewEnd = i;
                    break;
                }
            }

        // Iteraciones para buscar el mas alto
        while(i < lengthSolution){

            if(head->isAdy(solution->getNode(i-1))){
                // Actualiza el nodo en caso de encontrar un nodo con mas adyacentes libres
                if(freeAdy[selectedForNewEnd] < freeAdy[solution->getNode(i)->getId()])
                    selectedForNewEnd = i;
            }
            i++;
        }
    }else if(opt == 0){
        for (i = 1; i < lengthSolution-1; i++)
            // Verificar que el anterior nodo anterior es adyacente al actual nodo final
            if(head->isAdy(solution->getNode(i-1))){
                selectedForNewEnd = i;
                break;
            }
        
        // Iteraciones para buscar el mas alto
        while(i < lengthSolution-1){

            if(head->isAdy(solution->getNode(i-1))){
                // Actualiza el nodo en caso de encontrar un nodo con mas adyacentes libres
                if(solution->getNode(selectedForNewEnd)->getN() > solution->getNode(i)->getN())
                    selectedForNewEnd = i;
            }
            i++;
        }
    }

    // Verifica si no escogio ningun nodo
    if(selectedForNewEnd < 0){
        return false;
    }


    Path *rotated = new Path(sizeGraph);

    //Se agregan todos los anteriores antes del nodo con mayor grado
    for (int i = 0; i < selectedForNewEnd; i++){
        rotated->add(solution->getNode(i));
    }
    
    //Se agregan todos los posteriores del nodo con mayor grado,
    // pero desde la cabeza hacia atrás
    for (int i = solution->getLength()-1; i > selectedForNewEnd; i--){
        rotated->add(solution->getNode(i));
    }
    //agregar el nodo con mayor grado del camino
    rotated->add(solution->getNode(selectedForNewEnd));
    

    Path *aux = solution;
    solution=rotated;
    aux->~Path();
    

    return true;
}

Node *Solver::getSmallestFreeAdyFromNode(Node *theNode, Path* posiblyPath){
    int N = theNode->getN(), i;
    Node *selected = nullptr;
    //Primer for para encontrar un nodo no tomado
    for (i = 0; i < N; i++){
        if(!posiblyPath->isTaken(theNode->getNode(i)) && freeAdy[theNode->getNode(i)->getId()]>0){
            selected = theNode->getNode(i);
            break;
        }
    }

    // For para determinar un nodo menor que el seleccionado
    for(i = i+1; i < N; i++){
        if(freeAdy[theNode->getNode(i)->getId()] < freeAdy[selected->getId()] && !posiblyPath->isTaken(theNode->getNode(i))){
            selected  = theNode->getNode(i);
        }
    }
    return selected;
}
/* Node *Solver::getHighestFreeAdyFromNode(Node *theNode, Path* posiblyPath){

} */

void Solver::getFreeAdy(){
    /*Obtener la cantidad total de conexiones por nodo*/
    for (int i = 0; i < sizeGraph; i++){
        freeAdy[graph->getNode(i)->getId()] = graph->getNode(i)->getN();
    }

    int N, id;
    Node *theNode;
    
    // Se va restando por cada conexion ya hecha en el camino
    for (int i = 1; i < solution->getLength()-1; i++){
        // Se recorre el camino uno a uno
        theNode = solution->getNode(i);
        id = theNode->getId();
        N =theNode->getN(); 
        // Se le resta a los nodos adyacentes al actual la conexión presente
        for (int j = 0; j < N; j++){
            freeAdy[theNode->getNode(j)->getId()]--;
        }
    }
    
    if(solution->getLength()>1){
    
    freeAdy[solution->getNode(1)->getId()]--;
    freeAdy[solution->getNode(solution->getLength()-1)->getId()]--;
    }
}

bool Solver::solve(){
    // Se ordenan los nodos segun grado
    
    sort();
    
    // Se setea en solution el camino más largo para los nodos de mayor grado
    getLongestPathForHighestDegree();
    
    // Obtener los adyacentes libre
    getFreeAdy();
    
    Node *start , * head;
    
    // Fase 2, extender el camino mas largo ya encontrado
    int i = 0, verify = 0;
    while(solution->getLength() != sizeGraph){
        if(!rotationalTransformation(1)){
            solution->getHead()->printAdy();
            for (int i = 0; i < sizeGraph; i++){
            cout << GREEN << i << "->" <<RED<<freeAdy[i]<<"__" <<RESET;
            }
            cout << endl;
            if(verify == 1){
                return false;    
            }else
                verify = 1;
        }
        for (int i = 0; i < sizeGraph; i++)
        {
            cout << GREEN << i << "->" <<RED<<freeAdy[i]<<"__" <<RESET;
        }
        cout << endl;
        
        start = solution->getHead();
        if(i == 10)
            return false;
        while(1)
        {
            i++;
            start = getSmallestDegreeFromNode(start, solution);
            if(start){
                i = 0;
                verify = 0;
                solution->add(start);
                cout << "Elegido : "<< start->getId() <<endl;
                Node *head = solution->getHead();
                if(solution->getLength()>2){
                    freeAdy[solution->getNode(solution->getLength()-2)->getId()]--;
                }
                for (int i = 0; i < head->getN(); i++){
                    freeAdy[head->getNode(i)->getId()]--;
                }
            }else
                break;
        }
    }
    return true;

    // Fase 3, conectar ultimo nodo con primero
    i = 0;
    while(!solution->getHead()->isAdy(solution->getNode(0))){
        if(!rotationalTransformation(0) || i == 1000)
            return false;
        i ++;
    }

    return true;
}

Path *Solver::getPath(){
    return solution;
}