#include <bits/stdc++.h>    // Utilizaremos para encontrar uma solução ótima

using namespace std;

int v[110], w[110], dp[100010];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = m; j > 0; j--) {
            if (j - w[i] >= 0) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }

    // Cria e abre um arquivo para escrita
    ofstream outputFile("resultado.txt");
    
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
