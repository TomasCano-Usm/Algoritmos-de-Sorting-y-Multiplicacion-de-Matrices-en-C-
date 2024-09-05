#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

//esta funcion transpone la matriz A
vector<vector<int>> transpuesta(vector<vector<int>> &matrix) {
    int size = matrix.size();
    vector<vector<int>> aux(size, vector<int>(size, 0));
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            // se intercambian los valores de la matriz para transponerla
            aux[i][j] = matrix[j][i];
        }
    }
    return aux;
}
//esta funcion multiplica las matrices
vector<vector<int>> MultiplicarMatrices(vector<vector<int>> &matrizA, vector<vector<int>> &matrizB, int n) {
    // se inicializa la matriz que contendra el resultado de la multiplicacion 
    vector<vector<int>> respuesta(n, vector<int>(n, 0));
    // este loop recorre horizontalmente a la matriz A
    for (int i = 0; i < n; i++) {
        // este loop recorre verticalmente a la matriz B
        for(int j = 0; j < n; j++) {
            // este loop recorre la fila k de la matriz A y la fila k de la matriz B
            for(int k = 0; k < n; k++) {
                respuesta[i][j] += matrizA[i][k] * matrizB[j][k];
            }
        }
    }
     // se retorna la matriz que tiene el resultado de la multiplicacion
    return respuesta;
}
//genera una matriz con elementos aleatorios entre 1 y N
vector<vector<int>> generarMatrizAleatoria(int N) {
    vector<vector<int>> matriz(N, vector<int>(N));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, N);
    
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
    //comenzamos a tomar el tiempo de ejecucion del algoritmo optimizado
    vector<vector<int>> transpuestaA = transpuesta(matrizA);
    auto start = high_resolution_clock::now();
    vector<vector<int>> matrizResult = MultiplicarMatrices(transpuestaA, matrizB, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // imprimimos en pantalla la duracion en microsegundos del algortimo
    cout << "El algoritmo ha demorado: " << duration.count() << " microsegundos" << "\n";
    return 0;
}
