#ifndef NodoMine_
#define NodoMine_
#include <iostream>
#include <vector>


using std::vector;
using namespace std;

/*
 * Abstraccion de nodo con conexión a otros nodos
 */
class Node{
private:
    // identificador numérico
    int id;
    // Cantidad de conexiones
    int N;
    // Nodos a los que tiene acceso
    vector <Node*> ady;

    Node *next;
public:
    // Constructor sin parámetros
    Node();
    // Constructor con id asociado
    Node(int i);
    // Asociado
    ~Node();
    // Obtener numero de adyacentes
    int getN();
    // Obtener id
    int getId();
    // Agregar nodo a los adyacentes de este
    void addAdy(Node *newAdy);
    //Pertenece a los adyacentes
    bool isAdy(Node *theAdy);
    // Obtener un nodo a través de su posición en el "ady"
    Node* getNode(int i);
    // Imprimir los identificadores de los nodos adyacentes
    void printAdy();
    //Elimina todas las conexiones con los otros nodos
    void clearAdy();

    void stacker(Node *theNext);

    Node *getNext();
};

#endif