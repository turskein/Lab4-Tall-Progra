#ifndef PATHMine_
#define PATHMine_
#include <iostream>
#include "node.h"
#include <string.h>

/*
 * Abtraccion de los que se entendera como el camino solucion
 */

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"

class Path{
private:
    // Largo del camino
    int N;
    // Secuencia de nodos que representara el camino
    Node **path;
    // posicion siguiente a la del ultimo nodo puesto
    int head;
    // Nodos ya tomados dentro del camino
    bool *taken;
    // Nodos adyacentes libre de cada nodo
    int *freeAdy;
    //posicion dentro del camino
    int *position;
public:
    // Constructor
    Path(int large, Node**allNodes);
    // Destructor
    ~Path();
    // Agregar nodos dentro del camino
    void add(Node *newNode);
    // Verificar si esta tomado determinado nodo
    bool isTaken(Node *theNode);
    // Obtener el nodos con mayor grado
    int getHighestDegreeNode();
    // Obtener el nodo con menor grado
    int getSmallestDegreeNode();
    // obtener ultimo nodo puesto
    Node *getHead();
    // Obtener un nodo a partir de su posicion dentro del camino
    Node *getNode(int position);
    // Obtener el largo del camino
    int getLength();
    // Obtener la cantidad de adyacentes que tiene un 
    // nodo a partir de su posicion dentro del camino
    int getFreeAdy(int position);
    // Obtener cantidad de adyacentes libre de acuerdo al id
    int getFreeAdyById(Node *theNode);
    // Obtienes la posicion de un nodo en particular
    int getPositionByNode(Node *theNode);
    // Imprimir por pantalla el camino
    void print();
    // Imprime los nodos adyacentes libres de cada nodo
    void printFreeAdj();
};

#endif
