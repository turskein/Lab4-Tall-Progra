#include "cond_op2.h"

cond_op2::cond_op2(){
}

bool cond_op2::verify(Node *node){
    return node->getN() == 2;
}
