#include <iostream>
#include <vector>
#include <queue>
#define INF 10000000

using namespace std;

int n, m, k, s, t; // nodos, aristas, bidireccionales, inicio, destino

struct calle {
    int d; // conecta punto d con el punto c
    int c;
    int l;
};

vector<vector<calle>> calles;

bool operator>(calle c, calle c1){
    if(c.l > c1.l){
        return true;
    } else {
        return false; 
    }
}

int dijkstra() { // algoritmo dado en la clase práctica 
    vector<int> distancias(n + 1, INF);
    distancias[s] = 0;

    priority_queue<calle, vector<calle>, greater<calle>> cola;
    cola.push({0, s, 0});

    while (!cola.empty()) {
        int a = cola.top().c;
        int dist = cola.top().l;
        cola.pop();

        if (a == t) {
            return dist;
        }

        for (const calle& c : calles[a]) {
            int b = c.c;
            int dist2 = c.l;
            if (dist2 + dist < distancias[b]) {
                distancias[b] = dist2 + dist;
                cola.push({a, b, dist2 + dist});
            }
        }
    }

    return -1;
}

int main() {
    int casos;
    cin >> casos;

    while (casos > 0) {
        cin >> n >> m >> k >> s >> t;

        calles.clear();
        calles.resize(n + 1);

        for (int i = 0; i < m; i++) {
            int l, d, c;
            calle uni;
            cin >> d >> c >> l;
            uni.l = l;
            uni.d = d;
            uni.c = c;
            calles[d].push_back(uni);
        }

        int min_dist = INF;
        for (int i = 0; i < k; i++) {
            int l, u, v;
            calle bi;
            cin >> u >> v >> l;
            bi.l = l;
            bi.d = u;
            bi.c = v;
            calles[u].push_back(bi);
            bi.d = v;
            bi.c = u;
            calles[v].push_back(bi);

            int dist = dijkstra();
            min_dist = min(min_dist, dist);
   
            calles[u].pop_back();
            calles[v].pop_back();
        }

        if (min_dist == INF){
            cout << -1 << endl;
        } else {
            cout << min_dist << endl;
        }

        casos--;
    }

    return 0;
} 


