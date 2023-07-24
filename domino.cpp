#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> grafo;
vector<vector<int>> grafo_reverso;
vector<bool> visitados;
stack<int> stack_comp;


void dfs(int nodo) { // con stack
    visitados[nodo] = true;
    for (int u : grafo[nodo]) {
        if (!visitados[u]) {
            dfs(u);
        }
    }
    stack_comp.push(nodo);
}


void dfs_reverso(int nodo, vector<int>& comp_conexa) {
    visitados[nodo] = true;
    comp_conexa.push_back(nodo);
    for (int u : grafo_reverso[nodo]) {
        if (!visitados[u]) {
            dfs_reverso(u, comp_conexa);
        }
    }
}

void dfs_normal(int nodo) {
    visitados[nodo] = true;
   for (int u : grafo[nodo]) {
        if (!visitados[u]) {
            dfs_normal(u);
        }
    }
}


vector<vector<int>> encontrar_comp_conexas() { //kosaraju 
    for (int i = 1; i <= n; i++) {
        if (!visitados[i]) {
            dfs(i);
        }
    }

    visitados.assign(n + 1, false);
    vector<vector<int>> comp_conexas;

    while (!stack_comp.empty()) {
        int nodo = stack_comp.top(); 
        stack_comp.pop();

        if (!visitados[nodo]) {
            vector<int> comp_conexa;
            dfs_reverso(nodo, comp_conexa);
            comp_conexas.push_back(comp_conexa);
           
        }
        
    }
    
    return comp_conexas;
}



 vector<int> encontrar_conj_optimo(vector<vector<int>> &comp_conexas){
    visitados.assign(n + 1, false);
    vector<int> conj_optimo;

    for(int i = 0; i < comp_conexas.size(); i++){
        for(int j = 0; j < comp_conexas[i].size(); j++){
            if(!visitados[comp_conexas[i][j]]){
               conj_optimo.push_back(comp_conexas[i][j]);
               dfs_normal(comp_conexas[i][j]);
            }
        }
        
    }

  return conj_optimo;
 }


int main() {
   
    cin >> n >> m;

    grafo.resize(n + 1);
    grafo_reverso.resize(n + 1);
    visitados.assign(n + 1, false);
   

    for (int q = 0; q < m; q++) {
        int i, j;
        cin >> i >> j;
        grafo[i].push_back(j);
        grafo_reverso[j].push_back(i);
    }

    vector<vector<int>> comp_conexas = encontrar_comp_conexas();
    vector<int> conjunto_optimo = encontrar_conj_optimo(comp_conexas);
    reverse(conjunto_optimo.begin(), conjunto_optimo.end());

    cout << conjunto_optimo.size() << endl;
    for(int i = 0; i < conjunto_optimo.size(); i++){
        cout << conjunto_optimo[i] << " ";
    }
    cout << endl;  

    return 0;
}

