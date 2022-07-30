#ifndef GRAPHMine_
#define GRAPHMine_
#include <iostream>
#include "node.h"
#include <time.h>

using namespace std;

/*
 * Abstracción de grafo, es decir, de conexión de distintos nodos.
 * El objetivo de este grafo es establecer conexiones aleatorias 
 * entre los distintos nodos. Adicionalmente, lograr obtener un 
 * camino hamiltoniano lo más óptimo posible.
 * 
*/
class Graph{
private:
    // Cantidad de nodos
    int N;
    // Donde se guardan los distintos nodos
    Node **nodes;
    // Elimina las conexiones de todos los nodos
    void clearAdy();
public:
    // Constructor vacío
    Graph();
    //Constructor a partir de nodos de un archivo de tipo .hcp
    Graph(char p[]);
    // Constructor a partir de una cantidad de nodos señalado y probabilidad de conexión
    Graph(int cant, float p);
    // Destructor
    ~Graph();
    // Obtener cantidad de Nodos
    int getN();
    // Obtener un nodo en particular a partir de su identificador
    Node *getNode(int i);
    // Imprimir nodos del grafo
    void print();
    // Se resuelve el grafo buscando la existencia de un camino hamiltoniano
    Node *solve();
    // Obtiene el array de nodos
    Node **getAllNodes();
    /* Elimina las conexiones antiguas de los 
    nodos para recrearlo de acuerdo a una nueva probabilidad*/
    void reset(float p);
};

#endif