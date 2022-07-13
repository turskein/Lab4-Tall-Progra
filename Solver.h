#include "graph.h"
#include "quickSort.h"
#include <iostream>
#include <time.h>
#include "Path.h"

using namespace std;

class Solver
{
private:
    Graph *graph;
    Path *solution;
public:
    Solver();
    Solver(Graph *objective);
    ~Solver();

    /*Ordena de mayor a menor todos los nodos*/
    void sort();

    /*Obtiene el nodo con menor grado de un nodo en particular, esto siempre y cuando no este
    ocupado en el camino*/
    Node *getSmallestDegreeFromNode(Node *theNode, Path *posiblyPath);

    /*Consigue un camino empezando con un nodo con grado alto para continuar
    consiguiendo los de menor grado, esto hasta quedarse bloqueado*/
    Path *getPathForHighestDegree(Node *start);

    /*Setea en 'solution' el camino mas largo considerando solo los nodos con mayor grado*/
    void getLongestPathForHighestDegree();

    void solve();
};
