#include "labirinto.hpp"

Labirinto::Labirinto() : Couto(){
    this->PreencheArquivos();
    this->caminhoEZero=true;
    this->passouNasMatrizes=false;
    this->contCasas=0;
    this->contPerigos=0;
    this->matrizAtual=1;
    this->posicaoInicial = make_pair(rand() % this->getTamanho(), rand() % this->getTamanho());
    this->matriz= new pair<int,int>*[this->getTamanho()+1];
    for (int i = 0; i < this->getTamanho()+1; i++) this->matriz[i]=new pair<int,int>[this->getTamanho()];
    this->PreencheMatriz(1,&this->posicaoInicial, false);
}

void Labirinto::StartQuest(){
    pair<int,int> posicaoAtual = this->posicaoInicial;
    int matrizAnterior=this->matrizAtual;
    bool passouNasMartrizesUmaVez =false;
    while (this->Couto.getVida()>0)
    {   
        if (matrizAnterior!=this->matrizAtual){
            this->passouNasMatrizes=true;
            this->matrizAtual>this->getQtdMatriz()?this->matrizAtual=1:this->matrizAtual=this->matrizAtual;
            if(this->matrizAtual==1) 
                passouNasMartrizesUmaVez=true;
            // this->PrintMatriz(); //Printa a matriz que acabou de percorrer
            this->AtualizaMatriz(matrizAnterior);
            matrizAnterior=this->matrizAtual;
            this->PreencheMatriz(this->matrizAtual, &posicaoAtual, passouNasMartrizesUmaVez);
            // this->PrintMatriz(); //Printa a matriz que vai percorrer
            if (this->matriz[posicaoAtual.first][posicaoAtual.second].first == -2){ // verifica se é perigo
                this->contPerigos++;
                if(!this->Couto.diminuiVida()) return; // diminui a vida do personagem, e se morrer, fecha o programa
            }
            else if(this->matriz[posicaoAtual.first][posicaoAtual.second].first>0){
                this->contCasas++;
                this->caminhoEZero=false; // achou um numero diferente de 0
                this->matriz[posicaoAtual.first][posicaoAtual.second].first--;
                this->Couto.aumentaSacola();
            }else this->contCasas++;
            this->matriz[posicaoAtual.first][posicaoAtual.second].second++;
            
        }
        
        if(posicaoAtual==posicaoInicial && this->matrizAtual==1 && this->passouNasMatrizes){
            if (caminhoEZero)
            {
                cout << "O caminho foi completo de 0's" << endl;
                return;
            }
            this->passouNasMatrizes=false;
            this->caminhoEZero=true;
        }
        
        switch (rand()%8)
        {
        case 0: if(!this->AndaMatriz(&posicaoAtual, 0,1)) return;   // direita
            break;
        case 1: if(!this->AndaMatriz(&posicaoAtual, 1,1)) return;   // diagonal direita-baixo
            break;
        case 2: if(!this->AndaMatriz(&posicaoAtual, 1,0)) return;   // baixo
            break;
        case 3: if(!this->AndaMatriz(&posicaoAtual, 1,-1)) return;  // diagonal esquerda-baixo
            break;
        case 4: if(!this->AndaMatriz(&posicaoAtual, 0,-1)) return;  // esquerda
            break;
        case 5: if(!this->AndaMatriz(&posicaoAtual, -1,-1)) return; // diagonal esquerda-cima
            break;
        case 6: if(!this->AndaMatriz(&posicaoAtual, -1,0)) return;  // cima
            break;
        case 7: if(!this->AndaMatriz(&posicaoAtual, -1,1)) return;  // diagonal direita-cima
            break;
        default:
            break;
        }
    }
}

void Labirinto::ReviewQuest(){
    int contCasasNaoPercorridas=0;
    cout<<"-------------Review-------------"<<endl;
    cout<<"Foram percorridas "<< this->contCasas << " casas."<<endl;
    cout<<"Foram consumidos "<< this->Couto.getSacola() << " items."<<endl;
    cout<<"Foram encontrados "<< this->contPerigos << " perigos."<<endl;
    char inputData;
    ofstream resultado("dataset/resultado.data");
    for (int k = 0; k < this->getQtdMatriz(); k++)
    {
        ifstream input("dataset/Matriz"+to_string(k+1)+".data");
        for (int i = 0; i < this->getTamanho(); i++)
        {
            for (int j = 0; j < this->getTamanho(); j++)
            {
                input >> inputData;
                if(inputData=='#'){
                    input >> inputData;
                    resultado << '=' << ' ';
                }else{
                    input >> inputData;
                    if(inputData=='0'){
                        resultado << '0';
                        contCasasNaoPercorridas++;
                    }else resultado<<'1';
                    resultado << ' ';
                }
            }
            resultado << '\n';
        }
        resultado << '\n';
    }
    cout<<"Não foram exploradas "<< contCasasNaoPercorridas << " casas."<<endl;
    
}

bool Labirinto::AndaMatriz(pair<int,int>* posicaoAtual, int linha, int coluna){
    if( ((*posicaoAtual).first+linha   < this->getTamanho() && (*posicaoAtual).first+linha   >= 0) &&  // verifica se está dentro da matriz (linha)
        ((*posicaoAtual).second+coluna < this->getTamanho() && (*posicaoAtual).second+coluna >= 0)){   // verifica se está dentro da matriz (coluna)
        this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].second++;
        if(this->matriz[(*posicaoAtual).first+linha][(*posicaoAtual).second+coluna].first != -1){ //verifica se não é parede
            (*posicaoAtual).first+=linha;       // atualiza posição (linha)
            (*posicaoAtual).second+=coluna;     // atualiza posição (coluna)
            if (this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].first == -2){ //verifica se é perigo
                this->contPerigos++;
                if(!this->Couto.diminuiVida()) return false; // diminui a vida do personagem, e se morrer, fecha o programa
            }
            else if(this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].first > 0){ // verifica se o número não é zero
                this->contCasas++;
                this->caminhoEZero=false; // achou um numero diferente de 0
                //cout<<this->matriz[(*posicaoAtual).first][(*posicaoAtual).second]<<endl; // Mostra a casa que andou
                this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].first--;  // diminui a quantidade de itens
                this->Couto.aumentaSacola();                                    // aumenta a sacola, se der 4 aumenta a vida
            } else this->contCasas++;
        } 
        if(this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].second>50){ this->matrizAtual++;
            cout << this->caminhoEZero;
        }
    }
    else this->matrizAtual++;
    return true;
}

void Labirinto::PreencheMatriz(int matriz,pair<int,int>* posicaoAtual, bool passouNasMartrizesUmaVez){
    string temp;
    ifstream arquivo("dataset/Matriz"+to_string(matriz)+".data");
    if (arquivo.is_open())
    {
        for (int i = 0; i < this->getTamanho(); i++)
        {
            for (int j = 0; j < this->getTamanho(); j++){
                arquivo >> temp;
                if (temp=="#") this->matriz[i][j].first=-1;
                else if (temp=="*") this->matriz[i][j].first=-2;
                else this->matriz[i][j].first=stoi(temp);
                if(!passouNasMartrizesUmaVez) this->matriz[i][j].second=false;
                else arquivo >> this->matriz[i][j].second;
            }
        }
        if (posicaoAtual!=nullptr)
        {
            do
            {
                (*posicaoAtual) = make_pair(rand() % this->getTamanho(), rand() % this->getTamanho());
            } while (this->matriz[(*posicaoAtual).first][(*posicaoAtual).second].first==-1);
        }
        arquivo.close();
    }
    else
    {
        cout<<"Arquivo não abriu"<<endl;
        exit(9);
    }
}

void Labirinto::AtualizaMatriz(int matriz){
    ofstream arquivo("dataset/Matriz"+to_string(matriz)+".data");
    if (arquivo.is_open())
    {
        for (int i = 0; i < this->getTamanho(); i++)
        {
            for (int j = 0; j < this->getTamanho(); j++){
                if (this->matriz[i][j].first==-1) arquivo << '#';
                else if (this->matriz[i][j].first==-2) arquivo << '*';
                else arquivo << this->matriz[i][j].first;
                arquivo << ' ';
                this->matriz[i][j].second>0?arquivo <<1<<' ':arquivo <<0<<' ';
            }
            arquivo<<'\n';
        }
        arquivo.close();
    }
    else
    {
        cout<<"Arquivo não abriu"<<endl;
        exit(9);
    }
}

void Labirinto::PrintMatriz(){
    cout<< this->posicaoInicial.first << " "<< this->posicaoInicial.second<<endl;
    for (int i = 0; i < this->getTamanho(); i++)
    {
        for (int j = 0; j < this->getTamanho(); j++)
            cout << this->matriz[i][j].first << "\t";
        cout << endl;
    }
    cout << endl;
}