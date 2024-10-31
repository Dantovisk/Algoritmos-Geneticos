#include <bits/stdc++.h>

using namespace std;

class TwoSAT {
private:
    int numVars;
    unordered_map<string, int> varMap; //Hashmap dicionario de variaveis
    vector<vector<int>> implications, implicationsT; //lista de adjascencia para resolver com grafo
    vector<int> assignment;
    vector<bool> visited;
    vector<int> parentComponent;

    void dfs1(int u){

    }

    void dfs2(int u, int componentIndex){

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
    TwoSAT(int n) : numVars(n), implications(2*n) {}

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
        for(int i=0; i < 2*numVars; ++i){
            if(!visited[i]) dfs1(i);
        }

        fill(visited.begin(), visited.end(), false);

        int componentIndex = 0;

        for(int i = 2 * numVars - 1; i>=0; i--){
            int v = parentComponent[i];
            if(!visited[v]){
                dfs2(v, componentIndex++);
            }
        }
    }
};

int main(){





    return 0;
}