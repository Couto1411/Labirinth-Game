#include "geraMatriz.hpp"
Matriz::Matriz(){
    this->tamanho=4;
    this->qtdMatriz=3;
}

void Matriz::GeraMatriz(){
    int maxItems;
    ofstream arquivo("dataset/input.data");
    cout << "Qual o máximo de items que um espaço pode ter?" <<endl;
    cin >> maxItems;
    if (!arquivo.is_open())
    {
        cout<<"Arquivo não abriu"<<endl;
        exit(7);
    }
    arquivo << this->tamanho <<' '<< this->tamanho <<' '<< this->qtdMatriz<<'\n';
    for (int k = 0; k < this->qtdMatriz; k++)
    {
        for (int i = 0; i < this->tamanho; i++)
        {
            for (int j = 0; j < this->tamanho; j++)
            {
                switch(rand() % 5)
                {
                case 0:
                    arquivo << '#' << ' ';
                    break;
                case 1:
                    arquivo << '*' << ' ';
                    break;
                case 2:
                case 3:
                case 4:
                    arquivo << rand() % maxItems << ' ';
                    break;
                default:
                    break;
                }
            }
            arquivo << '\n';
        }
        arquivo << '\n';
    }
    arquivo.close();
}

void Matriz::PreencheArquivos(){
    char opcao = 'N'; string aux;
    cout<<"O arquivo input.data está preenchido? (S/N)"<<endl;
    cin>>opcao;
    if(opcao=='N'){
        cout << "Qual o tamanho das matrizes?" <<endl;
        cin >> this->tamanho;
        cout << "Quantas matrizes?" <<endl;
        cin >> this->qtdMatriz;
        this->GeraMatriz();
    }
    ifstream input("dataset/input.data");
    input >> this->tamanho;
    input >> this->tamanho;
    input >> this->qtdMatriz;
    for (int i = 0; i < this->qtdMatriz; i++)
    {
        ofstream arquivo("dataset/Matriz"+to_string(i+1)+".data");
        for (int j = 0; j < this->tamanho; j++)
        {
            for (int k = 0; k < this->tamanho; k++)
            {
                input >> aux;
                arquivo << aux << ' ';
            }
            arquivo << '\n';
        }
        arquivo.close();
    }
    
}

int Matriz::getTamanho(){
    return this->tamanho;
}

void Matriz::setTamanho(int x){
    this->tamanho=x;
}

int Matriz::getQtdMatriz(){
    return this->qtdMatriz;
}

void Matriz::setQtdMatriz(int x){
    this->qtdMatriz=x;
}