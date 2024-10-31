#include <bits/stdc++.h>

#define POP_SEX 100
#define POP_ASSEX 100
#define GENES_MUT 2

using namespace std;

void melhorRandom(vector<vector<bool>> &individuos, int nItems);

void randomizador(vector<vector<bool>> &individuos, int nItems);

void treinamento(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv, 
    int *bestFit, int pesoMax, vector <int> &peso, vector <int> &valor);

int avaliacao(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv, 
    int *bestFit, int pesoMax, vector <int> &peso, vector <int> &valor);

vector<vector<bool>> cruzamento(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv);

vector<vector<bool>> mutacao(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv);

vector<vector<bool>> mutacao(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv){
    random_device rd;  
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> distrib(0, nItems - 1);

    vector<vector<bool>> newIndiv(POP_SEX, vector<bool>(nItems));
    newIndiv = individuos;

    newIndiv[POP_SEX] = bestIndiv;
    
    for(int i = POP_SEX+1; i < POP_SEX + POP_ASSEX; i++){
        // Certifique-se de que bestIndiv tem o mesmo tamanho de newIndiv[i]
        if(bestIndiv.size() != newIndiv[i].size()) {
            newIndiv[i] = vector<bool>(nItems, 0); // Inicializa com zeros
        } else {
            newIndiv[i] = bestIndiv;
        }
        for(int k=0; k<GENES_MUT; k++){
            int geneIndex = distrib(gen);
            newIndiv[i][geneIndex] = !newIndiv[i][geneIndex]; 
        }
    }

    return newIndiv;
}

void melhorRandom(vector <bool> &bestIndiv, int nItems){
    // randomizador da std
    random_device rd;  
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> distrib(0, 2);

    for(int j=0; j<nItems; j++){
        bestIndiv[j] = (distrib(gen)?1:0);
    }
}

//elitismo :D
vector<vector<bool>> cruzamento(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv){
    // randomizador da std
    random_device rd;  
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> distrib(0, 1);

    vector<vector<bool>> newIndiv(POP_SEX, vector<bool>(nItems)); 
    newIndiv = individuos;
    
    // Copia o melhor indivíduo da geração anterior para a nova geração
    newIndiv[0] = bestIndiv;

    for(int i=1; i<POP_SEX; i++){
        for(int j=0; j<nItems; j++){
            int numAleat = distrib(gen);
            newIndiv[i][j] = (numAleat ? bestIndiv[j] : individuos[i][j]);
        }
    }

    return newIndiv; 
}


void randomizador(vector<vector<bool>> &individuos, int nItems)
{
    // randomizador da std
    random_device rd;  
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> distrib(0, 2);

    for(int i=0; i<POP_SEX + POP_ASSEX; i++){
        for(int j=0; j<nItems; j++){
            int numAleat = distrib(gen);
            individuos[i][j] = numAleat;
            //cout<<individuos[i][j]<<" ";
        }
        //cout<<"\n";
    }
}

void treinamento(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv, 
    int *bestFit, int pesoMax, vector <int> &peso, vector <int> &valor)
{
    
    while(1){
        cout<<"Digite o numero de geracoes (0 para sair):\n";
        int n; cin>>n;

        if(n==0) return;

        for(int i=0; i<n; i++){
            if(i%100==0){    //famoso genocidio :o
                randomizador(individuos, nItems);
            }

            individuos = cruzamento(individuos, nItems, bestIndiv);
            individuos = mutacao(individuos, nItems, bestIndiv);

            int k = avaliacao(individuos, nItems, bestIndiv, bestFit, pesoMax, peso, valor);
            cout<<"Geracao "<<i+1<<" - Melhor fit da geracao: "<<k<<" - Melhor ever: "<<*bestFit<<"\n";
        }
            
    }
}

int avaliacao(vector<vector<bool>> &individuos, int nItems, vector <bool> &bestIndiv, 
    int *bestFit, int pesoMax, vector <int> &peso, vector <int> &valor)
    {

    int melhorVivo = 0;
    random_device rd;  
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> distrib(0, nItems-1);
    
    for(int i=0; i<POP_SEX + POP_ASSEX; i++){
        int pesoAtual = 0, valorAtual =0;
        for(int j=0; j<nItems; j++){
            pesoAtual += (individuos[i][j]? peso[j]:0);
            valorAtual += (individuos[i][j]? valor[j]:0);
        }

        //nao cumpriram a condicao
        //realizaremos uma mutacao aleatoria
        while(pesoAtual > pesoMax){
            int numAleat = distrib(gen);

            if(individuos[i][numAleat]){
                individuos[i][numAleat]=0;
                pesoAtual -= peso[numAleat];
                valorAtual -= valor[numAleat];
            }
        }
        melhorVivo = max (melhorVivo, valorAtual);
        
        if(valorAtual > *bestFit){
            bestIndiv = individuos[i];
            *bestFit = valorAtual;
        }
    }
    return melhorVivo;
}


int main(){

    int nItems, pesoMax, bestFit = 0;
    cin>>nItems>>pesoMax;

    vector <int> valores(nItems, 0);
    vector <int> pesos(nItems, 0);

    vector<vector<bool>> individuos(POP_SEX + POP_ASSEX, vector<bool>(nItems));
    vector <bool> bestIndiv(nItems, 0);

    for(int i=0; i<nItems; i++) cin >> valores[i];
    for(int i=0; i<nItems; i++) cin >> pesos[i];
    

    melhorRandom(bestIndiv, nItems);

    randomizador(individuos, nItems);
    treinamento(individuos, nItems, bestIndiv, &bestFit, pesoMax, pesos, valores);

    return 0;
}