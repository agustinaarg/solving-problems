#include <iostream> 
#include <vector>
#include <iomanip>
#include <set>

 
using namespace std; 
 
 
long n,m; //n: cant de nodos, m: cant de aristas 
int puentes = 0; 
long long cant_nodos = 0;
int actual = 0; 
vector<vector<int>> grafo;
vector<int> descubrimientos; 
vector<int> distancias; 
vector<int> visitados;
set<pair<int, int>> aristas_puente;
vector<long long> comp_conexas;

 
bool es_puente(pair<int,int> arista){

  if (aristas_puente.find(arista) != aristas_puente.end()){ //O(log (puentes.size())) 
      return true; 
  } else {
    return false;
  }

} 


void dfs(int nodo) {
    visitados[nodo] = true;
    cant_nodos++;
    for (int u : grafo[nodo]) {
        if (!visitados[u] && !es_puente({u,nodo})){ 
           // cout << "soy el: " << nodo << " ";
            dfs(u);
        } 
   }
 
   
}
 
 
long long formas_de_ganar(){
    long long res = 0; 
    visitados.assign(n + 1, false); 
  
  
    for(int i = 1; i <= n; i++){
      if(!visitados[i]){  
        cant_nodos = 0;
        dfs(i); 
        comp_conexas.push_back(cant_nodos); //cuento cuantos nodos tiene cada componente conexa 
        }
    }
  
  for(int i = 0; i < comp_conexas.size(); i++){
        //cout << comp_conexas[i] << endl;  
        long long cant = (comp_conexas[i] * (comp_conexas[i] - 1)) / 2;
        res += cant; 
        //sumo la cant de pares que puedo elegir en cada componente conexa, que serian los pares ganadores 
  } 
     
    return res;
 
}
 

void encontrar_puentes(int nodo, int padre){
   visitados[nodo] = true; 
   actual++; 
   descubrimientos[nodo] = actual;
   distancias[nodo] = actual;
  
   for(int u : grafo[nodo]){
     if(!visitados[u]){
        encontrar_puentes(u, nodo);
        distancias[nodo] = min(distancias[nodo], distancias[u]);
         if(distancias[u] > descubrimientos[nodo]){
            puentes++; 
            aristas_puente.insert({u,nodo});
            aristas_puente.insert({nodo,u});
            } 
     } else if (u != padre){
       distancias[nodo] = min(distancias[nodo], descubrimientos[u]);
     }
   }
}
 
 
int main(){
  
cin >> n >> m; 
grafo.resize(n + 1); //lista de adyacencia
descubrimientos.resize(n + 1);
distancias.resize(n + 1); 
visitados.resize(n + 1, false);
//comp_conexas.resize(n + 1);
 
 
for(int i = 0; i < m; i++){
   int v,w; 
   cin >> v >> w; 
   grafo[v].push_back(w); 
   grafo[w].push_back(v);
}
 
  for (int i = 1; i <= n; i++) {
        if (!visitados[i]) {
           encontrar_puentes(i, 0);
        }
    }
 
 
long long fdg = formas_de_ganar(); 
long long formas_de_jugar = (n * (n - 1) / 2); //cant de pares de nodos que puedo elegir
 
 
cout << fixed << setprecision(5) << (1.0 - 1.0 * fdg / formas_de_jugar) << endl;
 
 
return 0; 
 
}





