#include "Solver.h"

using std::vector;
using namespace std;

int main(){
    char file[100] = "./graphs/alb1000.hcp";

    Graph *newGraph = new Graph(file);
    //Graph *newGraph = new Graph(15,0.18);
    cout << "Tamanio del grafo: "<< newGraph->getN()<<endl;
    Solver *solution = new Solver(newGraph);
    //newGraph->print();
    cout << "Inicio de algoritmo"<<endl;
    if(!solution->solve()){
        cout <<RED<<"No se completo el camino\nEste es el camino obtenido: \n"<<RESET<<endl;
        solution->getPath()->print();
        cout <<"Largo de solucion: " <<solution->getPath()->getLength()<<endl;
        }
    else
        cout << "Se encuentra camino"<<endl;

    return 0;
}
