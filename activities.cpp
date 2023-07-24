#include <iostream>
#include <vector> 


using namespace std;

int n;

struct actividad {
    int s; // inicio
    int t; // fin
    int ubi; // ubicación en el arreglo original
};

vector<int> acts_sin_solapar(vector<actividad> actividades) {
    vector<int> acts;
    int tiempo_final = -1;

    for (int i = 0; i < n; i++) {  //O(n)
        if (actividades[i].s >= tiempo_final) {
            acts.push_back(actividades[i].ubi);
            tiempo_final = actividades[i].t;
        }
    }

    return acts;
}

vector<actividad> concatenar_bucket(vector<actividad> actividades, vector<vector<actividad>> bucket) {
    vector<actividad> ordenadas;
    for (int i = 0; i < ((2*n) + 1); i++) {  //O(2n) = O(n)
        ordenadas.insert(ordenadas.end(), bucket[i].begin(), bucket[i].end()); //O(tamaño de bucket[i])
    }

    return ordenadas;
}

int main() {
    cin >> n; 
    vector<actividad> actividades; 
     vector<vector<actividad>> bucket(((2*n)+1), vector<actividad>());

    for (int i = 0; i < n; i++) { //O(n)
        int s, t; 
        cin >> s >> t; 
        actividad a; 
        a.s = s; 
        a.t = t;
        a.ubi = i + 1;
        actividades.push_back(a);  //O(1)
        bucket[t].push_back(a);  //O(1)
    }

    vector<actividad> ordenadas = concatenar_bucket(actividades, bucket);
     vector<int> res = acts_sin_solapar(ordenadas);


    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++) {  //O(res.size), siempre va a ser menor o igual a n, O(n) en el peor caso
        cout << res[i] << " ";
    }  
    cout << endl;

    return 0; 
}