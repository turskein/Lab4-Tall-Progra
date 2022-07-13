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
    Node* getHighestDegree();
    Node *getHead();
    int getLength();
};