#include "cond_op1.h"

cond_op1::cond_op1(){
}

bool cond_op1::path1majorthanpath2(Path *path1, Path *path2){
   return path1->getLength() > path2->getLength();
}
