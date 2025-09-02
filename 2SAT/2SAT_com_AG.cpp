#include <bits/stdc++.h>
#include <fstream>

#define POP_SIZE 100

using namespace std;

class TwoSAT {
private:
    int numVars;
    vector<int> assignment;
    unordered_map<string, int> varMap; //Hashmap dicionario de variaveis

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
    TwoSAT(int n) : numVars(n) {}

    void addClause(const string& var1, bool reau1, const string& var2, bool reau2){
        int id1 = getVarIndex(var1) * 2 + !reau1;
        int id2 = getVarIndex(var2) * 2 + !reau2;

        
    }

    bool solve(){
        
    }
        
    vector<int> getAssignment() const {
        return assignment;
    }
};



int main() {
    
    return 0;
}