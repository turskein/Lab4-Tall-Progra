#include "graph.h"
#include "node.h"
#include "quickSort.h"

int main()
{
    Graph myGraph(300,0.3);
    quickSort solver;
    solver.solve(myGraph.getAllNodes(), myGraph.getN());
    myGraph.print();
    return 0;
}
