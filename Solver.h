#include "graph.h"
#include "quickSort.h"
#include <iostream>
#include <time.h>
#include "Path.h"

using namespace std;

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"

class Solver
{
private:
    Graph *graph;
    Path *solution;
    int sizeGraph;
    int *freeAdy;
public:
    Solver();
    Solver(Graph *objective);
    ~Solver();

    /*Obtener los adyacentes de cada nodo*/
    void getFreeAdy();

    /*Ordena de mayor a menor todos los nodos*/
    void sort();

    /*Obtiene el nodo con menor grado de un nodo en particular, esto siempre y cuando no este
    ocupado en el camino*/
    Node *getSmallestDegreeFromNode(Node *theNode, Path *posiblyPath);

    Node *getSmallestFreeAdyFromNode(Node *theNode, Path* posiblyPath);
    Node *getHighestFreeAdyFromNode(Node *theNode, Path* posiblyPath);

    /*Consigue un camino empezando con un nodo con grado alto para continuar
    consiguiendo los de menor grado, esto hasta quedarse bloqueado*/
    Path *getPathForHighestDegree(Node *start);

    /*Setea en 'solution' el camino mas largo considerando solo los nodos con mayor grado*/
    void getLongestPathForHighestDegree();

    /**/
    bool rotationalTransformation(int opt);

    void invertSol();

    Path *getPath();

    bool solve();
};
