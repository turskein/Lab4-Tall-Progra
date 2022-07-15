#include "Solver.h"
#include <unistd.h>

int main(){
    int intentos = 50;
    int tamanio = 10000, k;

    unsigned t0, t1; // Tiempos a resta
    double time, tAver = 0;
    float prob = 0, probAver = 0;

    Graph **toSolve = new Graph*[intentos];
    Solver **solution = new Solver*[intentos];

    for (int i = 0; i < 1; i++){
        k = 0;
        toSolve[i] = new Graph(tamanio, 0.2);
        solution[i] = new Solver(toSolve[i]);
        
        t0 = clock();
        if(solution[i]->solve()){
            k = 1;
        }
        t1 = clock();

        toSolve[i]->~Graph();
        solution[i]->~Solver();
        
        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout <<"[" << i + 1 << "]" << "Solved in: " << time << "[s] - ";
        if(k == 1){
            cout << GREEN << "ENCONTRADO EL HCP"<<RESET<<endl;
        }else{
            cout << RED << "NO ENCONTRADO EL HCP"<<RESET<<endl;
        }
    }

    cout << "Tiempo promedio de encontrar:  "<<tAver/intentos<<endl;
        
    return 0;
}
