#include "cond_op1.h"

cond_op1::cond_op1(){
}

bool cond_op1::verify(Node *node){
    return node->getN() == 1;
}

