#ifndef GeraMatriz_H
#include <bits/stdc++.h>
using namespace std;

class Matriz
{
    private:
        int tamanho, qtdMatriz;
    public:
        Matriz();
        void GeraMatriz();
        void PreencheArquivos();
        int getTamanho();
        void setTamanho(int x);
        int getQtdMatriz();
        void setQtdMatriz(int x);
};


#endif