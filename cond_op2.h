#ifndef CONDITIONAL_OP2_
#define CONDITIONAL_OP2_
#include <iostream>
#include "node.h"
#include "Conditional.h"

class cond_op2: public Conditional{
public:
    cond_op2();
    ~cond_op2();
    bool verify(Node *node);
};
#endif
