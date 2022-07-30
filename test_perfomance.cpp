#include "Solver.h"
#include <unistd.h>

int main(){
    int intentos = 50;
    int tamanio = 1000, k;
    float prob = 0.2;

    unsigned t0, t1; // Tiempos a resta
    double time, tAver = 0;

    Graph *toSolve = new Graph(tamanio, prob);
    Solver *solution = new Solver(toSolve);

    for (int i = 0; i < 30; i++){
        k = 0;
        
        t0 = clock();
        if(solution->solve()){
            k = 1;
        }
        t1 = clock();
        
        toSolve->reset(prob);
        solution->reset(toSolve);

        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout <<"[" << i + 1 << "]" << "Solved in: " << time << "[s] - ";
        if(k == 1){
            cout << GREEN << "ENCONTRADO EL HCP"<<RESET<<endl;
        }else{
            cout << RED << "NO ENCONTRADO EL HCP"<<RESET<<endl;
        }
    }

    cout << "Tiempo promedio :  "<<tAver/intentos<<endl;
        
    return 0;
}
