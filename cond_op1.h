#ifndef CONDITIONAL_OP1_
#define CONDITIONAL_OP1_
#include <iostream>
#include "node.h"
#include "Conditional.h"

class cond_op1: public Conditional{
public:
    cond_op1();
    ~cond_op1();
    bool verify(Node *node);
};
#endif
