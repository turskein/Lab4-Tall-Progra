#include "graph.h"
#include "quickSort.h"
#include <iostream>
#include <time.h>
#include "Path.h"
#include "Conditional.h"
#include "cond_op1.h"
#include "sort.h"

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
public:
    Solver();
    Solver(Graph *objective);
    ~Solver();

    /*Obtener los adyacentes de cada nodo*/
    void getFreeAdy();

    /*Ordena de mayor a menor todos los nodos*/
    bool sort();

    /*Obtiene el nodo con menor grado de un nodo en particular, esto siempre y cuando no este
    ocupado en el camino*/
    bool extendSolution(Path *posiblyPath);

    /*Obtiene el nodo con menor grado de un nodo en particular, esto siempre y cuando no este
    ocupado en el camino*/
    Node *getSmallestDegreeFromNodeWithRestrictions(Path *posiblyPath);

    /*Consigue un camino empezando con un nodo con grado alto para continuar
    consiguiendo los de menor grado, esto hasta quedarse bloqueado*/
    Path *getPathForHighestDegree(Node *start);

    /*Setea en 'solution' el camino mas largo considerando solo los nodos con mayor grado*/
    void getLongestPathForHighestDegree();

    /*Metodo incorporado del paper entregado*/
    bool rotationalTransformation(int opt);

    /*Invierte la solucion actualmente conseguida*/
    void invertSol();

    /*Entrega el camino actual*/
    Path *getPath();

    /*Encuentra y verifica si existe un ciclo hamiltoniano en el grafo entregado*/
    bool solve();

    /*Redefine sus variables*/
    void reset(Graph *objective);

    bool addAloneNodes();
};
