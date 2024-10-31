#include <bits/stdc++.h>
//#include <random>

#define NITEMS 200
#define MAXW 100000
#define MAXVAL 1000000

using namespace std;

long long int v[NITEMS], w[NITEMS], dp[MAXW + 69];
int m = 0;


int main() {
    // Inicializa o gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd());

    // Distribuições para os intervalos especificados
    uniform_int_distribution<> distrib_value(0, MAXVAL);
    uniform_int_distribution<> distrib_weight(0, MAXW);

    // Cria e abre um arquivo para escrita
    ofstream inputFile("input.txt");
    
    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    m = distrib_weight(gen);
    inputFile<<NITEMS<<" "<<m<<"\n";

    // Gera e escreve os primeiros NITEMS números (0 a 10^7)
    for(int i = 0; i < NITEMS; i++) {
        v[i] = distrib_value(gen);
        inputFile << v[i] << " ";
    }

    // Quebra de linha no arquivo
    inputFile << endl;

    // Gera e escreve os próximos NITEMS números (0 a 10^5)
    for(int i = 0; i < NITEMS; i++) {
        w[i] = distrib_weight(gen);
        inputFile << w[i] << " ";
    }

    // Fecha o arquivo
    inputFile.close();

    cout << "Números gerados e exportados para 'input.txt'" << endl;


    for (int i = 0; i < NITEMS; i++) {
        for (int j = m; j > 0; j--) {
            if (j - w[i] >= 0) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }

    // Cria e abre um arquivo para escrita
    ofstream outputFile("output.txt");
    
    if (!outputFile) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // Escreve o resultado no arquivo
    outputFile << dp[m] << endl;

    // Fecha o arquivo
    outputFile.close();

    // Também imprime na tela
    cout << dp[m] << endl;

    return 0;
}