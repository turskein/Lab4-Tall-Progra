#include <iostream>
#include "node.h"

class Path{
private:
    int N;
    Node **path;
    int position;
    int *taken;
public:
    Path(int large);
    ~Path();
    void add(Node *newNode);
    bool istaken(Node *theNode);
    int getHighestDegree();
    int getSmallestDegree();
    Node *getHead();
    Node *getNode(int position);
    int getLength();
    void print();
};