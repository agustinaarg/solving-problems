#include <iostream>
#include <vector> 
#include <iomanip>
#include <cmath>
#include <bits/stdc++.h>

#define UTP 0 
#define FIBRA_OPTICA 1

using namespace std; 

int n; // cantidad de oficinas
int r; // distancia a partir de la cual no se puede usar UTP
int w; // cantidad de modems 
int u; // costo por centímetro de los UTP
int v; // costo por centímetro de la fibra óptica
int caso = 1; 
vector<pair<int, int>> grafo;
bool sumar = false; 
 
using ll = long long;
const ll inf = 1e18;

struct costo {
  double costo; 
  int tipo_de_cable; 
  int coord_1;
  int coord_2; 
};

vector<costo> costos; 
double costo_utp;
double costo_fibra_optica; 

double distancia(int x1, int x2, int y1, int y2) { 
    double res = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return res; 
}

bool comp(costo a, costo b) {
    return a.costo < b.costo; 
}

struct DSU {
    DSU(int n) {
        padre = rank = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
        componentes = n;
    }

    int find(int v) {
        if (v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return;
        }
        if (rank[u] < rank[v]) {
            swap(u, v);
        }
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
        componentes = componentes - 1;
        sumar = true; 
    } 
    

    vector<int> padre;
    vector<int> rank;
    int componentes;
};

void calcular_costos() {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distancia(grafo[i].first, grafo[j].first, grafo[i].second, grafo[j].second); 
            if (dist <= r) {
                costo d; 
                d.costo = dist * u;
                d.tipo_de_cable = UTP;
                d.coord_1 = i; 
                d.coord_2 = j; 
                costos.push_back(d); 
            } else {
                costo d; 
                d.costo = dist * v;
                d.tipo_de_cable = FIBRA_OPTICA;
                d.coord_1 = i; 
                d.coord_2 = j; 
                costos.push_back(d); 
            }
        }
    }
}

void kruskal() {
    sort(costos.begin(), costos.end(), comp);
    ll res = 0;
    int aristas = 0;
    DSU dsu(n);
    for (auto [co, t, c1, c2] : costos) {
        if (dsu.find(c1) != dsu.find(c2)) {
            dsu.unite(c1, c2);
            aristas++;
       if(sumar == true){
            if (t == UTP){
                costo_utp += co;
                sumar = false;
            } else {
                costo_fibra_optica += co; 
                sumar = false;
            } 
        }
         if (w == dsu.componentes) {
                break;
        }
        }
    }
}

int main() {
    int c; 
    cin >> c;

    while (c > 0) { 
        cin >> n >> r >> w >> u >> v; 
        costo_utp = 0;
        costo_fibra_optica = 0; 
        costos.clear(); 
        grafo.clear();
        grafo.resize(n); 

        for (int i = 0; i < n; i++) {
            int x, y; 
            cin >> x >> y;  
            grafo[i].first = x; 
            grafo[i].second = y;  
        }

        calcular_costos(); 
        kruskal();
        
       cout << "Caso #" << caso << ": "<< fixed << setprecision(3) << costo_utp << " " << costo_fibra_optica << endl;

        c--; 
        caso++;
    }

    return 0; 
}

