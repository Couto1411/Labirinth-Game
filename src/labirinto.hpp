#ifndef Labirinto_H
#include "geraMatriz.hpp"
#include "Personagem.hpp"
#include <bits/stdc++.h>
using namespace std;

class Labirinto : public Matriz
{
private:
    int matrizAtual, contCasas, contPerigos;
    bool caminhoEZero, passouNasMatrizes;
    pair<int,int> posicaoInicial;
    pair<int,int> **matriz;
    Personagem Couto;
public:
    Labirinto();
    void StartQuest();
    void ReviewQuest();
    bool AndaMatriz(pair<int,int>*posicaoAtual, int linha, int coluna);
    void PreencheMatriz(int matriz,pair<int,int>* posicaoAtual, bool passouNasMartrizesUmaVez);
    void AtualizaMatriz(int matriz);
    void PrintMatriz();
};


#endif