#include "graph.h"
#include "node.h"
#include "quickSort.h"

int main(){
    Graph *myGraph = new Graph(10000, 0.3);
    quickSort *sorter = new quickSort();
    int *peo = new int[1];
    unsigned t0, t1;
    double time, tAver = 0;
    int iteraciones = 100;

    for (int i = 0; i < iteraciones; i++){
        cout <<"["<<i<<"] "<< "inicio de ordenamiento -> ";
        
        t0 = clock();
        sorter->solve(myGraph->getAllNodes(),myGraph->getN());
        t1 = clock();
        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout << "Tiempo que se tarda: "<< time << endl;
        myGraph->reset(0.3);
    }

    cout << "Tiempo promedio : "<< tAver/iteraciones << endl;
}
