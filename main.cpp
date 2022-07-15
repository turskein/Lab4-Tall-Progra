#include "Solver.h"
#include <unistd.h>

int main(){
    unsigned t0, t1; // Tiempos a resta
    bool sol;
    double time, tAver = 0;
    float prob = 0, probAver = 0;

    float intentos = 50;
    int tamanio = 15, integer = intentos;
    Graph **toSolve = new Graph*[integer*integer];
    Solver **solution = new Solver*[integer*integer];
    

    for (float i = 0; i < intentos; i++)
    {
        
        for(float j = 1; j/intentos < 1; j = j + 1){
            integer = intentos*i + j;
            prob = j /intentos;
            toSolve[integer] = new Graph(tamanio, prob);
            solution[integer] = new Solver(toSolve[integer]);
            
            t0 = clock();
            if(solution[integer]->solve()){
                t1 = clock();
                break; 
            }
            t1 = clock();
            toSolve[integer]->~Graph();
            solution[integer]->~Solver();
            
        }
        probAver = probAver + prob;
        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout << GREEN <<"[" << i + 1 << "]" << "Solved in: " << time << "[s]"<< " con probabilidad: "<< prob << RESET << endl;
    }

    cout << "Tiempo promedio de encontrar:  "<<tAver/intentos<<endl;
    cout << "Probabilidad promedio de encontrar: "<< probAver/intentos << endl;
    
        
    return 0;
}
