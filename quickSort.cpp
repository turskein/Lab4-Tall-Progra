#include "quickSort.h"


quickSort::quickSort()
{
}

quickSort::~quickSort()
{
}

void quickSort::qs(Node **lista, int limite_izq, int limite_der)
{
    int izq,der,pivote;
    Node *temporal;

    izq=limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2]->getN();

    do{
        while(lista[izq]->getN()<pivote && izq<limite_der)izq++;
        while(pivote<lista[der]->getN() && der > limite_izq)der--;
        if(izq <=der)
        {
            temporal= lista[izq];
            lista[izq]=lista[der];
            lista[der]=temporal;
            izq++;
            der--;
        }

    }while(izq<=der);
    if(limite_izq<der){qs(lista,limite_izq,der);}
    if(limite_der>izq){qs(lista,izq,limite_der);}

}

void quickSort::solve(Node **lista,int n)
{
    qs(lista,0,n-1);
}