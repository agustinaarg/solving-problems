#include <iostream>
#include <vector> 
#include <algorithm> 
#include <utility>
#include <cmath>
#include <stddef.h>
#include<tuple>
#include <queue>
#include <limits.h>

using namespace std; 

int n, m, x;
const int INF = 10000000;

vector<vector<int>> adj;
vector<vector<int>> capacity;
vector<vector<int>> capacityAux; 

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacityAux[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacityAux[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n + 1);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacityAux[prev][cur] -= new_flow;
            capacityAux[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void ajustarCapacidadesPorK(int k){
    for (int i = 0; i < capacity.size(); i++){
        for (int j = 0; j < capacity.size(); j++){
            capacityAux[i][j] = capacity[i][j] / k;
        }
    }
    
}

void mostrarMatriz(vector<vector<int>> matriz){
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[i].size(); j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}


int main(){
    int cantTest; cin >> cantTest;

    while (cantTest != 0){
        cin >> n >> m >> x; 

        //Init y armado de red.
        capacity.assign(n+1,vector<int>(n+1,0));
        capacityAux.assign(n+1,vector<int>(n+1,0));
        adj.assign(n+1,vector<int>(0));

        for (int i = 0; i < m; i++){
            int u, v, c; cin >> u >> v >> c; // u -> v. Fix: u-- y v--?? Creo que no.
            capacity[u][v] = c; 
            capacityAux[u][v] = c; 
            adj[u].push_back(v);
            adj[v].push_back(u); // agrego la vuelta para el camino de aumento
        }

        int s = 1;   // el taller se encuentra en el 1
        int t = n;   // la casa rosada en el n 
        int maximoFlow = maxflow(s,t);
     
        // Si el flujo maximo es menor a la cantidad de compañeros.
        if(maximoFlow < x){ 
            cout << 0 << endl;
            cantTest--;
            continue;
        }

        // Hacemos busqueda binaria para encontrar la cantidad maxima de distribuidas equitativamente.
        
        int C_inferior = 0;  
        int C_superior = maximoFlow + 1;     
        int C = (C_superior + C_inferior)/2;   
       // int res = 0;
       
            
        while(C_inferior + 1 < C_superior){
           // cout << C << " "; 
            ajustarCapacidadesPorK(C); 
            maximoFlow = maxflow(s,t);
            
            if(maximoFlow >= x){  
               C_inferior = C; 
            } else {
               C_superior = C;   
            }

            C = (C_superior + C_inferior)/2;         
            
        }
        
        cout << (C * x) << endl;

        capacity.clear(); capacityAux.clear(); adj.clear();
        cantTest--;
    }
    
    return 0;
}
