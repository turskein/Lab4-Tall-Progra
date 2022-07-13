#include "Solver.h"

int main(){
    Graph *newGraph = new Graph(5,1);
    Solver solution(newGraph);
    solution.solve();

    return 0;
}