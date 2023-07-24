#include <iostream> 
#include <vector> 


using namespace std; 

using Cuadrado_magico = vector<vector<int>>;

vector<Cuadrado_magico> cuadrados_magicos; 
int n, k ,numero_magico;

 

bool es_cuadrado_magico(Cuadrado_magico& cuadrado, vector<int>& sumas) {
  for(int i = 0; i < n+2; i++){
        if(sumas[i] != numero_magico){
            return false;
        }
    }
    return true; 
}


/*int suma_fila(int fila, int columna, Cuadrado_magico& cuadrado){
int res = 0; 
   for(int i = 0; i < columna; i++){
      res+= cuadrado[fila][i];
   }

   return res; 
} */


void calcular_cuadrados_magicos(int fila, int columna, int suma_actual, Cuadrado_magico& cuadrado, vector<bool>& usados, vector<int>& sumas){
   if(cuadrados_magicos.size() == k){
    return;
   } 


  if(fila == n && es_cuadrado_magico(cuadrado,sumas)){
      if(cuadrados_magicos.size() != 0){
              if(cuadrados_magicos[cuadrados_magicos.size() - 1] == cuadrado){ //esto es para evitar los repetidos, supongo
              //que es por esto que se nos pasa de tiempo. 
                return; 
              } else {
                 cuadrados_magicos.push_back(cuadrado);
                 
              }
        } else {
           cuadrados_magicos.push_back(cuadrado);  
             
        }  
    
      // cuadrados_magicos.push_back(cuadrado);
     return; 
        
  }

 if(columna == n){ //cuando termino la fila, si la suma es igual al nro magico, paso a la siguiente
    if(suma_actual == numero_magico){
        calcular_cuadrados_magicos(fila + 1, 0, 0,cuadrado,usados,sumas); 
        fila++;
        columna = 0;
        suma_actual = 0;
    } else {
        return;
    }
} 


/*if (suma_fila(fila, columna, cuadrado) > numero_magico){
   return;

}  */

for(int j = 0; j < n+2; j++){
    if(sumas[j] > numero_magico){
        return;
    }
}


  for(int i = 1; i < (n*n)+1; i++){
    if(usados[i] == false){
        if(suma_actual + i <= numero_magico){
            usados[i] = true; 
            cuadrado[fila][columna] = i;
            suma_actual = suma_actual + i;
            sumas[columna] += i;
                if(fila == columna){
                    sumas[n] += i;
                }
                if(fila + columna == n - 1){
                    sumas[n+1] += i;
                }
            calcular_cuadrados_magicos(fila, columna + 1, suma_actual,cuadrado,usados,sumas);
            suma_actual-=i;
            usados[i] = false; 
            sumas[columna] -= i;
                if(fila == columna){
                    sumas[n] -= i;
                }
                if(fila + columna == n - 1){
                    sumas[n+1] -= i;
                }
        } 
    }
 }

 

} 



int main(){

cin >> n >> k; 

numero_magico = ((n*n*n)+n)/2;
Cuadrado_magico cuadrado(n, vector<int>(n)); 
vector<bool> usados((n*n) + 1, false);
vector<int> sumas_parciales(n+2); //las primeras tres son las columnas, las ultimas dos las diagonales. 


calcular_cuadrados_magicos(0, 0, 0, cuadrado,usados,sumas_parciales);
int size = cuadrados_magicos.size();

//cout << size << endl; 
    if(cuadrados_magicos.size() >= k){
    Cuadrado_magico cuadr = cuadrados_magicos[k-1];  
    for(int j = 0; j < n; j++){
        for(int m = 0; m < n; m++){
            cout << cuadr[j][m] << " "; 
        }
        cout << endl;
    } 
} else {
    cout << "-1" << endl; 
}

return 0; 

}  







///// VERSION QUE FUNCIONA //// 



#include <iostream> 
#include <vector> 
 
 
using namespace std; 
 
using Cuadrado_magico = vector<vector<int>>;
 
vector<Cuadrado_magico> cuadrados_magicos; 
Cuadrado_magico res; 
int n, k ,numero_magico;
int k2 = 0;
 
 
 
bool es_cuadrado_magico(Cuadrado_magico& cuadrado, vector<int>& suma_c) {
    for(int i = 0; i < n; i++){
        if(suma_c[i] != numero_magico){
            return false;
        }
    }
      
    
    return true; 
}
 
 
void calcular_cuadrados_magicos(int fila, int columna, int suma_actual, Cuadrado_magico& cuadrado, vector<bool>& usados, vector<int>& suma_f, vector<int>& suma_c, vector<int>& suma_d ){
   if(k2 == k){
       return;
   } 
   
 
 
  if(fila == n - 1 && columna == n /*&& es_cuadrado_magico(cuadrado, suma_c)*/){
     if(suma_d[0] == numero_magico){
     k2++;
        if(k2 == k){ 
            res = cuadrado; 
            return; 
        }
        return;
     }
     return;   
  }
   
 
 
    if(columna == n){ //cuando termino la fila, si la suma es igual al nro magico, paso a la siguiente
        if(suma_actual == numero_magico){
            //calcular_cuadrados_magicos(fila + 1, 0, 0,cuadrado,usados,sumas); 
            fila++;
            columna = 0;
            suma_actual = 0;
        } else {
            return;
        }
    } 
 
  
    
   if(suma_c[columna] > numero_magico || suma_f[fila] > numero_magico || suma_d[0] > numero_magico || suma_d[1] > numero_magico){ // si le pongo >= ? 
       return; 
    }  
 
 
  for(int i = 1; i < (n*n)+1; i++){
    if(usados[i] == false){
        if(fila == n - 1 && suma_c[columna] + i != numero_magico){
            continue;
        }
        if(fila == n - 1 && columna == 0 && suma_d[1] + i != numero_magico){
            continue;
        }
        if(suma_actual + i <= numero_magico){ //podria agregar aca que si es igual al nm y no es la ult columna, corte 
            usados[i] = true; 
            cuadrado[fila][columna] = i;
            suma_actual = suma_actual + i;
            suma_f[fila] += i;
            suma_c[columna] += i;
            if(fila == columna){
                suma_d[0] += i;
            }
            if(fila + columna == n - 1){
                suma_d[1] += i;
            }    
            calcular_cuadrados_magicos(fila, columna + 1, suma_actual,cuadrado,usados,suma_f, suma_c, suma_d);
            suma_actual-=i;
            usados[i] = false; 
            suma_f[fila] -= i;
            suma_c[columna] -= i; 
            if(fila == columna){
                suma_d[0] -= i;
            }
            if(fila + columna == n - 1){
                suma_d[1] -= i;
            }
        } 
    }
 }
 
 
 
} 
 
 
 
int main(){
 
cin >> n >> k; 
 
 
numero_magico = ((n*n*n)+n)/2;
Cuadrado_magico cuadrado(n, vector<int>(n)); 
vector<bool> usados((n*n) + 1, false);
//vector<int> sumas_parciales(n+2); //las primeras n son las columnas, las ultimas dos las diagonales. 
 
vector<int> suma_columnas(n);
vector<int> suma_filas(n);
vector<int> suma_diagonales(2);
 
 
calcular_cuadrados_magicos(0, 0, 0, cuadrado,usados,suma_columnas, suma_filas,suma_diagonales);
//int size = cuadrados_magicos.size();
 
//cout << size << endl; 
   /* if(cuadrados_magicos.size() >= k){
    Cuadrado_magico cuadr = cuadrados_magicos[k-1];  
    for(int i = 0; i < size; i++){
        for(int j = 0; j < n; j++){
            for(int m = 0; m < n; m++){
                cout << cuadrados_magicos[i][j][m] << " "; 
            }
            cout << endl;
        } 
        cout << endl;
    }
    } else {
        cout << "-1" << endl; 
    } */
    if(k2 == k){
          for(int j = 0; j < n; j++){
            for(int m = 0; m < n; m++){
                cout << res[j][m] << " "; 
            }
            cout << endl;
        } 
    } else {
        cout << "-1" << endl; 
    }
 
return 0; 
 
} 