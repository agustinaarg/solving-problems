#include iostream
#include vector
#include algorithm

using namespace std; 

long long n, m;
long long sumD, sumR;
double c, maxC, cDiv;

struct conexion 
{
 long long u;
 long long  v;
 long long  d;
 long long r;
};

vectorconexion costos;
double C;

struct DSU {
    DSU(long long n) {
         Aca solo hace init con -1 para padre e init con 1 de todo rank.
        padre = rank = vectorlong long(n,-1); 
        for (long long v = 0; v  n; v++) padre[v] = v;
    }

    long long find(long long v) {
        if (v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(long long u, long long v) {
        u = find(u), v = find(v);
        if (u == v) {
            return;
        }
        if (rank[u]  rank[v]) {
            swap(u, v);
        }
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
    } 
    
    vectorlong long padre;
    vectorlong long rank;
};

bool cmp(conexion a, conexion b){ return (a.d - C  a.r  b.d - C  b.r); }

pairlong long,long long kruskal() {
    long long dParcial = 0, rParcial = 0; 

    DSU dsu(n);
    sort(costos.begin(), costos.end(), cmp); 

    long long aristas = 0;
    for (conexion costo  costos) {
         Acceder a los elementos de la tupla por índice
        long long u = costo.u;long long v = costo.v; long long d = costo.d; long long r = costo.r;
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            dParcial += d;
            rParcial += r;
            aristas++;
        }
        if(aristas == n-1) break;
    }
    
    return {dParcial, rParcial};
}

pairlong long,long long maximoAgm(pairlong long,long long agmKruskal, pairlong long,long long res){
    double agKruskal = agmKruskal.first (double)agmKruskal.second;
    double resKruskal = res.first  (double)res.second; 

    pairlong long, long long max; 

    if(agKruskal  resKruskal){
        max = agmKruskal;
    }else{
        max = res;
    }

    return max;
}

int main(){
    long long cantTest; 
    cin  cantTest; 

    while(cantTest != 0){
        cin  n  m;
        costos.clear();
        for(long long i = 0; i  m; i++){
            long long u, v, d, r;
            cin  u  v  d  r; 
            sumD += d; sumR += r;
            u--;v--;
            costos.push_back({u,v,d,r});
        }

         Siguiendo la sugerencia vamos a buscar un valor C = DR.
         Definimos que C puede estar acotado entre 1 = C = sumarTodasLasDistancias
        double C_inferior = 0, C_superior = sumD; 
        pairlong long,long long res;
        pairlong long,long long resMax = make_pair(0,1);
        while((C_superior - C_inferior)  0.001){  Dif((C_superior - C_inferior))  epsilon 
            C = (C_inferior + C_superior)2.0;

            res = kruskal(); 
            
            double C_AGM = (double)res.first  (double)res.second;

            if (C_AGM  C){ 
                C_inferior = C;
            }else{
                C_superior = C; 
            }
            resMax = maximoAgm(res,resMax);
        }

        pairlong long,long long reslong long = make_pair((long long)resMax.first,(long long)resMax.second);

        cout  resMax.first     resMax.second  endl; 

        sumD = 0; sumR = 0; C = 0;
        cantTest--;
    }

    return 0;
}
