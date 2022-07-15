#include "Solver.h"
#include <ctime>

int main(){


    Graph *newGraph = new Graph(1000,0.6);
    
    Solver *solution = new Solver(newGraph);
    /* newGraph->print(); */
    
    if(solution->solve()){
        Path *camino = solution->getPath();
        /* camino->print(); */
        for (int i = 0; i < 4; i++)
        {
            if(!camino->getNode(i)->isAdy(camino->getNode(i+1)))
                cout <<i<< ".-No es camino"<<endl;
        }
        if(!camino->getNode(4)->isAdy(camino->getNode(0)))
            cout << "4 .- No es camino"<<endl;
        
    }
    return 0;
}