#include <iostream>
#include <vector> 
#include <algorithm> 
#include <utility>
#include <cmath>
#include<tuple>
#include <queue>


using namespace std; 

int n, f, c; 
int cant_filas = 0,  cant_col = 0, cant_nodos; 
vector<vector<int>> tablero;
vector<vector<int>> ady; 
vector<vector<int>> filas;
vector<vector<int>> columnas; 

const int INF = 10000000;

// Implementacion de Edmonds-Karp tomada de CP-Algorithm
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : ady[cur]) {
                    
            if (parent[next] == -1 && tablero[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, tablero[cur][next]);
               
                if (next == t){
                    return new_flow;}
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent((2 * cant_nodos) + 2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            
            int prev = parent[cur];
            tablero[prev][cur] -= new_flow;
            tablero[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


void contar_fyc(){
    //cuento filas  
      int ant = 0; 
       for(int i = 0; i < n; i++){
           cant_filas++; 
        for(int j = 0; j < n; j++){
              if(filas[i][j] == -1){
                if(ant != -1 && j != 0 && j != n){
                    ant = filas[i][j];
                    cant_filas++;
                    continue;
                } 
                ant = filas[i][j];
                continue;
              } else {
                filas[i][j] = cant_filas;
                ant = filas[i][j]; 
              }
        }
       }


    //cuento columnas  
        ant = 0; 
       for(int j = 0; j < n; j++){
           cant_col++; 
        for(int i = 0; i < n; i++){
              if(columnas[i][j] == -1){
                if(ant != -1 && i != 0 && i != n){
                    ant = columnas[i][j];
                    cant_col++; 
                    continue;
                } 
                ant = columnas[i][j];
                continue;
              } else {
                columnas[i][j] = cant_col;
                ant = columnas[i][j]; 
              }
        }
       }
}

int main(){
     int cantTest; cin >> cantTest;

    while (cantTest != 0){
        cin >> n;
        filas.assign(n, vector<int>(n, 0));
        columnas.assign(n, vector<int>(n, 0));
        

       for(int i = 0; i < n; i++){   
            for(int j = 0; j < n; j++){
                int r;  cin >> r;
                if(r == 1){
                  filas[i][j] = -1;
                  columnas[i][j] = -1; //Asigno -1 a los rotos
                }
            }
       }  
       
      contar_fyc();  //cuenta cuantas filas y columnas me quedan con los casilleros rotos 
      
      cant_nodos = cant_filas + cant_col + 2; 
      tablero.assign(cant_nodos, vector<int>(cant_nodos, 0)); //tablero con capacidades 
      ady.resize(cant_nodos); 
      
       int s = 0; 
       int t = cant_nodos - 1; 


       for(int i = 1; i < cant_filas + 1; i++){ //conecto el s a todas las filas con capacidad 1 
            tablero[s][i] = 1; 
            ady[s].push_back(i);
            ady[i].push_back(s);
       }
       
        for(int i = cant_filas + 1; i < (cant_nodos - 1); i++){ //conecto el t a todas las col con capacidad 1 
            tablero[i][t] = 1;  
            ady[t].push_back(i);  
            ady[i].push_back(t);
       }


       for(int i = 0; i < n; i++){  // conecto las filas con las columnas                                     
        for(int j = 0; j < n; j++){
            if(filas[i][j] != -1){
               int fila = filas[i][j]; 
               int col = columnas[i][j] + cant_filas; 
               tablero[fila][col] = 1;  
               ady[fila].push_back(col);
               ady[col].push_back(fila); 

            } else {
                continue;
            }     
         }
       }
  
        cout << maxflow(s,t) << endl;

        tablero.clear(); ady.clear(); filas.clear(); columnas.clear(); 
        cant_col = 0; cant_filas = 0; cant_nodos = 0; 
        cantTest--;
    }

    return 0;
}
