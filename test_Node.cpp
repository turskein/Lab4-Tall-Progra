#include <iostream>
#include "node.h"

using namespace std;

int main()
{
    Node *myNode = new Node(0);
    myNode->addAdy(new Node(1));
    myNode->addAdy(new Node(2));
    cout << myNode->getNode(0)->getId() << endl;
    cout << myNode->getNode(1)->getId() << endl;
    return 0;
}
