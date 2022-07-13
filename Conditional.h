#ifndef CONDITIONAL_
#define CONDITIONAL_
#include <iostream>
#include "node.h"

class Conditional{
public:
    Conditional();
    ~Conditional();
    virtual bool verify(Node *node) = 0;
};

#endif