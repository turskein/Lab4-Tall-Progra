#include "Path.h"

int main(){

    Path *myPath = new Path(10);
    myPath->add(new Node(3));
    myPath->add(new Node(4));
    myPath->add(new Node(6));
    myPath->add(new Node(5));
    myPath->add(new Node(8));
    myPath->print();
    cout << "Largo del camino: "<< myPath->getLength() << endl;
    return 0;
}
