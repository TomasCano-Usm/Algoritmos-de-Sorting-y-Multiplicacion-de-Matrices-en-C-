#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// esta funcion multplica matrices de orden N x N
vector<vector<int>> MultiplicarMatrices(vector<vector<int>> &matrizA, vector<vector<int>> &matrizB, int n){
    // se inicializa la matriz que contendra el resultado de la multiplicacion 
    vector<vector<int>> respuesta(n, vector<int>(n, 0));
    // este loop recorre horizontalmente a la matriz A
    for (int i = 0; i < n; i++){
        // este loop recorre verticalmente a la matriz B
        for(int j = 0; j < n; j++){
            // este loop recorre la fila k de la matriz A y la columna k de la matriz B
            for(int k = 0; k < n; k++){
                // aqui se le asigna el valor de la multiplicacion y suma a la posicion (i, j) de la matriz
                // de respuesta
                respuesta[i][j] += matrizA[i][k]*matrizB[k][j];
            }
        }
    }
    // se retorna la matriz que tiene el resultado de la multiplicacion
    return respuesta;
}
//genera una matriz con elementos aleatorios entre 1 y N
vector<vector<int>> generarMatrizAleatoria(int N) {
    // Crear una matriz de tamaño N x N
    vector<vector<int>> matriz(N, vector<int>(N));

    // Configurar el generador de números aleatorios
    random_device rd; // Fuente de entropía
    mt19937 gen(rd()); // Mersenne Twister: generador de números pseudoaleatorios
    uniform_int_distribution<> dis(0, N); // Distribución uniforme en el rango [0, N]
    
    // Llenar la matriz con valores aleatorios
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = dis(gen);
        }
    }
    
    return matriz;
}

int main() {
    //ingresamos el valor N de la matriz N x N
    int N;
    cout << "Choose your N: ";
    cin >> N;
    //generamos e inicializamos las matrices A y B aleatorias
    vector<vector<int>> matrizA = generarMatrizAleatoria(N);
    vector<vector<int>> matrizB = generarMatrizAleatoria(N);
    //comenzamos a tomar el tiempo de ejecucion del algoritmo
    auto start = high_resolution_clock::now();
    vector<vector<int>> matrizResult = MultiplicarMatrices(matrizA, matrizB, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // imprimimos en pantalla la duracion en microsegundos del algortimo
    cout<<"El algortimo ha demorado: "<<duration.count()<<" microsegundos"<<"\n";
    return 0;
}