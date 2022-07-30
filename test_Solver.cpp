#include "Solver.h"
#include <ctime>

int main(){


    int N = 10000;
    float probability = 0.1;

    Graph *newGraph = new Graph(N,probability);
    
    Solver *solution = new Solver(newGraph);

    int *verify = new int[N];

    if(solution->solve()){
        cout <<GREEN <<"se encuentra un camino"<<RESET<<endl;
        Path *camino = solution->getPath();
        /* camino->print(); */
        for (int i = 0; i < N-2; i++)
        {
            if(!camino->getNode(i) == 0){
                verify[i] = 1;
            }else{
                cout << "Aparece mas de una vez, por ende, funciona mal el algoritmo" << endl;
                i = N;
            }
            if(!camino->getNode(i)->isAdy(camino->getNode(i+1)))
                cout <<i<< ".-No es ciclo"<<endl;
        }
        if(!camino->getNode(N-1)->isAdy(camino->getNode(0))){
            cout << "Last .- No es ciclo"<<endl;
            if(camino->getNode(N-1) == 0){
                cout << "Aparece mas de una vez, por ende, funciona mal el algoritmo" << endl;
            }
        }
    }else{
        cout <<RED <<"No se encuentra un camino"<<RESET<<endl;
    }
    return 0;
}