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


    // Opcion de obtener el nodo con menor cantidad de adyacentes libres
    /* if(head->isAdy(solution->getNode(0)) && freeAdy[solution->getNode(0)->getId()] == 1)
        selectedForNewEnd = 0;
    else{
        // Seleccion del nodo con menor cantidad de adyacentes libres
        for (i = 1; i < lengthSolution; i++)
        {
            // Verificar que el anterior nodo anterior es adyacente al actual nodo final
            if(head->isAdy(solution->getNode(i-1))){
                // Si se encuentra un nodo con adyacentes libres == 1 es el elegido
                if(freeAdy[solution->getNode(i)->getId()] == 1){
                    selectedForNewEnd = i;
                    i = lengthSolution;
                }
                // De otra manera se busca el primero que tenga caminos libres
                if(freeAdy[solution->getNode(i)->getId()] > 0){
                selectedForNewEnd = i;
                break;
                }
            }
        }
        
        // Iteraciones para buscar el mas bajo
        while(i < lengthSolution){

            if(head->isAdy(solution->getNode(i-1))){
                // Si se encuentra un nodo con adyacentes libres == 1 es el elegido
                if(freeAdy[solution->getNode(i)->getId()] == 1){
                    selectedForNewEnd = i;
                    i = lengthSolution;
                }
                // De otra manera se busca el primero que tenga caminos libres
                if(freeAdy[selectedForNewEnd] > freeAdy[solution->getNode(i)->getId()])
                    selectedForNewEnd = i;
            }
            i++;
        }
    } */

    // Seleccion del nodo con menor cantidad de adyacentes libres
    for (i = 1; i < lengthSolution; i++)
    {
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
    if(selectedForNewEnd < 0){
        cout << "No se puede ejecutar una rotacion" << endl;
        return false;
    }


    Path *rotated = new Path(sizeGraph);

    //Se agregan todos los anteriores antes del nodo con mayor grado
    for (int i = 0; i < selectedForNewEnd; i++){
        cout << ".";
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
    freeAdy[selectedForNewEnd] ++;
    freeAdy[head->getId()] --;

    return true;
}

void Solver::getFreeAdy(){
    int **matrix = new int*[sizeGraph];
    for (int i = 0; i < sizeGraph; i++){
        matrix[i] = new int[sizeGraph];
        freeAdy[graph->getNode(i)->getId()] = graph->getNode(i)->getN();
    }

    int N, id;
    Node *theNode;

    for (int i = 0; i < solution->getLength(); i++){
        theNode = solution->getNode(i);
        id = theNode->getId();
        N =theNode->getN(); 
        for (int j = 0; j < N; j++){
            if(matrix[id][theNode->getNode(j)->getId()] == 0 || matrix[theNode->getNode(j)->getId()][id] == 0){
                freeAdy[id]--;
                freeAdy[theNode->getNode(j)->getId()] --;
                matrix[id][theNode->getNode(j)->getId()] = 1;
                matrix[theNode->getNode(j)->getId()][id] = 1;
            }
        }
    }
    cout << endl;
}

bool Solver::solve(){
    // Se ordenan los nodos segun grado
    sort();

    // Se setea en solution el camino más largo para los nodos de mayor grado
    getLongestPathForHighestDegree();


    // Obtener los adyacentes libre
    getFreeAdy();

    cout << endl;

    // Fase 2, extender el camino mas largo ya encontrado
    int i = 0;
    while(solution->getLength() != sizeGraph){
        if(!rotationalTransformation(1)){
            return false;
        }
        Node* start = solution->getHead();
            if(i == 100)
                return false;
            while(1)
            {
                i++;
                start = getSmallestDegreeFromNode(start, solution);
                if(start){
                    i = 0;
                    solution->add(start);
                }else{
                    break;
            }
        }
    }
    // Fase 3, transformar el camino mas corto ya encontrado

    return true;
}

Path *Solver::getPath(){
    return solution;
}