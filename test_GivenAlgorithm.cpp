#include "Solver.h"

using std::vector;
using namespace std;

int main(){
    char file[100] = "./graphs/graph10.hcp";

    Graph *newGraph = new Graph(file);

    Solver *solution = new Solver(newGraph);
    newGraph->print();
    cout << "Inicio de algoritmo"<<endl;
    if(!solution->solve()){
        solution->getPath()->print();
        cout <<"Largo de solucion: " <<solution->getPath()->getLength()<<endl;
        }
    else
        cout << "Se encuentra camino"<<endl;

    return 0;
}
