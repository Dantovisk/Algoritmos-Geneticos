#include <bits/stdc++.h>

using namespace std;

class TwoSAT {
private:
    int numVars;
    unordered_map<string, int> varMap; //Hashmap dicionario de variaveis
    vector<vector<int>> implications, implicationsT; //lista de adjascencia para resolver 2SAT com kosaraju
    vector<int> assignment;
    vector<bool> visited;
    vector<int> parentComponent;
    stack <int> kosarajuStack;

    void dfs1(int u){
        visited[u] = true;
        for (int x: implications[u]){
            if(!visited[x]) dfs1(x);
        }
        kosarajuStack.push(u);
    }

    void dfs2(int u, int componentIndex) {
        visited[u] = true;
        parentComponent[u] = componentIndex;
        for (int x : implicationsT[u]) {
            if (!visited[x]) {
                dfs2(x, componentIndex);
            }
        }
    }

    //Recebe nome da variavel e retorna seu indice
    int getVarIndex(const string& var){
        //se nao encontrarmos a variavel vamos mapea-la
        if(varMap.find(var) == varMap.end()){
            int index = varMap.size();
            varMap[var] = index;
            return index;
        }

        return varMap[var];
    }

    //dado o indice de uma variavel, retornaremos o indice de sua versao negada
    int getNotVarIndex(int varIndex){
        return varIndex ^ 1;
    }

public:
    // construtor da classe TwoSAT
    // implications tem o dobro de tamanho considerando 
    // que cada variavel tem sua correspondente negada
     TwoSAT(int n) : numVars(n), implications(2 * n), implicationsT(2 * n), visited(2 * n, false) {}

    void addClause(const string& var1, bool reau1, const string& var2, bool reau2){
        int id1 = getVarIndex(var1) * 2 + !reau1;
        int id2 = getVarIndex(var2) * 2 + !reau2;

        implications[getNotVarIndex(id1)].push_back(id2); // !id1 => id2
        implications[getNotVarIndex(id2)].push_back(id1); // !id2 => id1

        //grafo reverso para realizar kosaraju
        implicationsT[id2].push_back(getNotVarIndex(id1));
        implicationsT[id1].push_back(getNotVarIndex(id2));
    }

    bool solve(){
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < 2 * numVars; ++i) {
            if (!visited[i]) {
                dfs1(i);
            }
        }

        fill(visited.begin(), visited.end(), false);
        parentComponent.assign(2 * numVars, -1);
        int componentIndex = 0;

        while (!kosarajuStack.empty()) {
            int v = kosarajuStack.top();
            kosarajuStack.pop();
            if (!visited[v]) {
                dfs2(v, componentIndex++);
            }
        }

        assignment.assign(numVars, -1);  // -1 = não atribuído
        for (int i = 0; i < numVars; ++i) {
            if (parentComponent[2 * i] == parentComponent[2 * i + 1]) {
                return false;  // variável e sua negação estão na mesma componente
            }
            assignment[i] = (parentComponent[2 * i] > parentComponent[2 * i + 1]);
        }
        return true;

    }
};

int main(){
    TwoSAT solver(3); // 3 variáveis: x, y, z

    solver.addClause("x", true, "y", true);   // x OR y
    solver.addClause("x", false, "z", true);  // ¬x OR z
    solver.addClause("y", false, "z", true);  // ¬y OR z
    solver.addClause("z", false, "x", true);  // ¬z OR x

    bool result = solver.solve();
    if (result) {
        cout << "Existe solução!" << endl;
    } else {
        cout << "Não há solução!" << endl;
    }

    return 0;
}