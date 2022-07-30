#include "Solver.h"

Solver::Solver(Graph *objective){
    sizeGraph = objective->getN();
    graph = objective;
    solution = new Path(sizeGraph, graph->getAllNodes());
}

void Solver::reset(Graph *objective){
    sizeGraph = objective->getN();
    Path *aux = solution;
    solution = new Path(sizeGraph, graph->getAllNodes());
    aux->~Path();
}

bool Solver::sort(){
    Sort *sorter = new Sort(graph);
    if(sorter->verifyAllNodes()){
        sorter->solve();
        sorter->~Sort();
        return true;
    }
    sorter->~Sort();
    return false;
}

Solver::~Solver(){
    solution->~Path();
}

Node *Solver::getSmallestDegreeFromNodeWithRestrictions(Path *posiblyPath){
    // Conseguir nodo cabeza
    Node *headNode = posiblyPath->getHead(), *ady;
    int N = headNode->getN(), position = 0, subN, verify = 0;
    Node *selected = nullptr;
    //Primer for para encontrar un nodo no tomado con el cual realizar futuras comparaciones
    for (int i = 0; i < N; i++){
        position = i;
        // Nodo adyacente al actual nodo fin del camino
        ady = headNode->getNode(i);
        // Grado del nodo adyacente
        subN = ady->getN();
        // Verifica que no este tomado el nodo
        if(!posiblyPath->isTaken(ady)){
            // Variabla que en caso de ser 0 permitira tomar el nodo, de los contrario no
            verify = 0;
            // Verificacion de que la cantidad de nodos libres que tienen los adyacentes al actual son mayores a 1
            for (int j = 0; j < subN; j++){
                if(posiblyPath->getFreeAdyById(ady->getNode(j)) < 2 && !posiblyPath->isTaken(ady->getNode(j))){
                    verify = 1;
                    break;
                }
            }
            if(verify == 0){
                selected = headNode->getNode(i);
                i=N;
            }
        }
    }

    // For para determinar un nodo menor que el seleccionado
    for(int i = position+1; i < N; i++){
        // comparacion para encontrar el mejor nodo
        if(headNode->getNode(i)->getN() < selected->getN() && !posiblyPath->isTaken(headNode->getNode(i))){
            ady = headNode->getNode(i);
            subN = ady->getN();
            verify = 0;
            // Verificacion de que la cantidad de nodos libres que tienen los adyacentes al actual son mayores a 1
            for (int j = 0; j < subN; j++){
                if(posiblyPath->getFreeAdyById(ady->getNode(j)) < 2 && !posiblyPath->isTaken(ady->getNode(j))){
                    verify = 1;
                    break;
                }
            }
            if(verify == 0){
                selected = headNode->getNode(i);
            }
        }
    }
    return selected;
}

void Solver::invertSol(){
    Path *posiblyPath = new Path(sizeGraph, graph->getAllNodes()), *aux;
    for (int i = solution->getLength()-1; i >= 0; i++){
        posiblyPath->add(solution->getNode(i));
    }
    aux = solution;
    solution = posiblyPath;
    aux->~Path();
}

Path *Solver::getPathForHighestDegree(Node *start){
    Path *posiblyPath = new Path(sizeGraph, graph->getAllNodes());
    posiblyPath->add(start);
    while (1){
        start = getSmallestDegreeFromNodeWithRestrictions(posiblyPath);
        if(start){
            posiblyPath->add(start);
        }else{
            while(extendSolution(posiblyPath));
            return posiblyPath;
        }
    }
}

void Solver::getLongestPathForHighestDegree(){
    Conditional *intento = new cond_op1();

    solution = getPathForHighestDegree(graph->getNode(sizeGraph-1));
    Path *posiblyPath, *aux;
    int highest =graph->getNode(sizeGraph-1)->getN(), i = 2;

    while(graph->getNode(sizeGraph-i)->getN() == highest){
        posiblyPath = getPathForHighestDegree(graph->getNode(sizeGraph-i));
        if(intento->path1majorthanpath2(posiblyPath,solution)){
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
        if (solution->getFreeAdy(0) > 0)
            selectedForNewEnd = 0;
        else
            for (i = 1; i < lengthSolution; i++)
                // Verificar que el anterior nodo anterior es adyacente al actual nodo final
                if(solution->getFreeAdy(i) > 0 && head->isAdy(solution->getNode(i-1))){
                    selectedForNewEnd = i;
                    break;
                }

        // Iteraciones para buscar el mas alto
        while(i < lengthSolution){

            if(head->isAdy(solution->getNode(i-1))){
                // Actualiza el nodo en caso de encontrar un nodo con mas adyacentes libres
                if(solution->getFreeAdy(selectedForNewEnd) < solution->getFreeAdy(i) && solution->getFreeAdy(i)>0)
                    selectedForNewEnd = i;
            }
            i++;
        }
    }else if(opt == 0){ // Selecciona el nodo con menor grado
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

    // Generacion de nuevo camino
    Path *rotated = new Path(sizeGraph, graph->getAllNodes());

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

bool Solver::solve(){
    // Se ordenan los nodos segun grado
    
    if(!sort()){
        return false;
    }
    //Fase 1
    // Se setea en solution el camino más largo para los nodos de mayor grado
    getLongestPathForHighestDegree();
    Node *start , * head;
    
    // Fase 2, extender el camino mas largo ya encontrado
    int i = 0, verify = 0, k = 0;
    while(solution->getLength() != sizeGraph){
        k = 0;
        if(!rotationalTransformation(1)){
            if(!addAloneNodes()) return false;
        }
        while(extendSolution(solution)) k = 1;
        if(k == 0) return false;
    }
    // Fase 3, conectar ultimo nodo con primero
    i = 0;
    while(!solution->getHead()->isAdy(solution->getNode(0))){
        if(!rotationalTransformation(0) || i == 100)
            return false;
        i ++;
    }

    return true;
}

bool Solver::addAloneNodes(){
    Node *aloneNode = nullptr;
    for (int i = 0; i < graph->getN(); i++){
        if(!solution->isTaken(graph->getNode(i))){
            aloneNode = graph->getNode(i);
            for (int j = 1; j < solution->getLength(); j++){
                if(aloneNode->isAdy(solution->getNode(j-1)) && aloneNode->isAdy(solution->getNode(j))){
                    Path *newPath = new Path(sizeGraph, graph->getAllNodes()), *aux;
                    for (int k = 0; k < j; k++)
                    {
                        newPath->add(solution->getNode(k));
                    }
                    newPath->add(aloneNode);
                    for (int k = j; k < solution->getLength(); k++)
                    {
                        newPath->add(solution->getNode(k));
                    }
                    aux = solution;
                    solution = newPath;
                    aux->~Path();
                    return true;
                }

            }
            return false;
        }
    }
    return true;
}

Path *Solver::getPath(){
    return solution;
}

bool Solver::extendSolution(Path *posiblyPath){

    int N, position;
    Node *selected, *theNode;
    N = posiblyPath->getHead()->getN();
    selected = nullptr;
    position = 0;
    theNode = posiblyPath->getHead();
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
        /* if(theNode->getNode(i)->getN() < selected->getN() && !posiblyPath->isTaken(theNode->getNode(i))){
            selected  = theNode->getNode(i);
        } */
        if(posiblyPath->getFreeAdyById(theNode->getNode(i)) > posiblyPath->getFreeAdyById(selected) && !posiblyPath->isTaken(theNode->getNode(i)))
            selected  = theNode->getNode(i);
            
    }
    if(selected){
        posiblyPath->add(selected);
        return true;
    }else
        return false;
}