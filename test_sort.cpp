#include "quickSort.h"
#include "Sort.h"
#include <unistd.h>

int main()
{
    Graph *myGraph = new Graph(30000, 0.3);
    Sort *sorter = new Sort(myGraph);
    unsigned t0, t1;
    double time, tAver = 0;
    int iteraciones = 1;

    for (int i = 0; i < iteraciones; i++)
    {
        if(!sorter->verifyAllNodes()){
            cout << "La wea tiene pocas conexiones"<< endl;
            break;
        }
        cout <<"["<<i<<"] "<< "inicio de ordenamiento -> ";
        
        t0 = clock();
        sorter->solve();
        t1 = clock();
        time = (double(t1 - t0) / CLOCKS_PER_SEC);
        tAver = tAver + time;
        cout << "Tiempo que se tarda: "<<time << endl;
        while(1);
        myGraph->reset(0.3);
    }

    cout << "Tiempo promedio : "<< tAver/iteraciones << endl; 
    
    return 0;
}
