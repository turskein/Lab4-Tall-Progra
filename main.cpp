#include "Solver.h"
#include <unistd.h>

int main(){
    unsigned int microsecond = 3000000;
    unsigned t0, t1; // Tiempos a resta
    bool sol;
    double time, tAver = 0;
    float prob = 0, probAver = 0;

    float intentos = 30;
    int tamanio = 100;

    Graph *toSolve = new Graph(tamanio, 1/intentos);
    Solver *solution = new Solver(toSolve);
    for (float i = 0; i < intentos; i = i +1)
    {
        
        for(float j = 1; j/intentos < 1; j = j + 1){
            prob = j /intentos;
            
            t0 = clock();
            if(solution->solve()){
                t1 = clock();
                break; 
            }
            t1 = clock();
            toSolve->reset(j/intentos);
            solution->reset(toSolve);
        }
        
        probAver = probAver + prob;
        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout << GREEN <<"[" << i + 1 << "]" << "Solved in: " << time << "[s]"<< " with probability: "<< prob << RESET << endl;
    }

    cout << "Tiempo promedio de encontrar:  "<<tAver/intentos<<endl;
    cout << "Probabilidad promedio de encontrar: "<< probAver/intentos << endl;
        
    return 0;
}
