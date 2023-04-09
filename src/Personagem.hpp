#ifndef Personagem_H
#include <bits/stdc++.h>
using namespace std;

class Personagem
{
    private:
        int vida, sacola;
    public:
        Personagem();
        int getVida();
        bool diminuiVida();
        int getSacola();
        void aumentaSacola();
};
#endif