#ifndef CONDITIONAL_
#define CONDITIONAL_
#include <iostream>
#include "node.h"
#include "Path.h"

class Conditional{
public:
    Conditional();
    ~Conditional();
    virtual bool path1majorthanpath2(Path *path1, Path *path2) = 0;
};

#endif