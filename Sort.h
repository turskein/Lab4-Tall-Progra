#ifndef SortMine_
#define SortMine_
#include "node.h"
#include "graph.h"

using namespace std;

class Sort
{
private:
    Graph *objective;
    int sizeGraph;
    int majorDegreeNode;
    Node **stacks;
public:
    Sort(Graph *objective);
    ~Sort();
    bool verifyAllNodes();
    void solve();
};





#endif