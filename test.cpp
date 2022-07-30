#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    int *data = new int[10];
    for (int i = 0; i < 10; i++)
    {
        *(data+i) = 3;
    }
    cout << endl;
    delete[] data;
    
    bool *moredata = new bool[10];
    //memset(moredata, 0, sizeof(int)*10);

    for(int i = 0; i < 10; i++)
        cout << moredata[i]<< " - ";
    delete[] moredata;

    return 0;
}
