#include "Personagem.hpp"

Personagem::Personagem(){
    this->vida=10;
    this->sacola=0;
}

int Personagem::getVida(){return this->vida;}
bool Personagem::diminuiVida(){
    this->vida--;
    if (this->vida<=0)
    {
        cout<<"Personagem Morreu" << endl;
        return false;
    }
    return true;
    
}

int Personagem::getSacola(){return this->sacola;}
void Personagem::aumentaSacola(){
    this->sacola++;
    if (this->sacola%4==0 && this->vida<10) this->vida++;
}
