#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std::chrono;
using namespace std;


//La autoria del algoritmo de strassen esta creado por ChatGpt.
//El resto del codigo, que corresponde al analisis temporal del algortimo y la generacion de matrices, esta basado
//en algoritmos anteriores.

// funcion que suma 2 matrices
void addMatrix(vector<vector<int>>& C, const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            // se recorren ambas matrices y se va almacenando el resultado de la suma de Aij y Bij en Cij
            C[i][j] = A[i][j] + B[i][j];
}
// funcion que resta 2 matrices
void subtractMatrix(vector<vector<int>>& C, const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            // se recorren ambas matrices y se va almacenando el resultado de la resta de Aij y Bij en Cij
            C[i][j] = A[i][j] - B[i][j];
}
// funcion que multiplica 2 matrices de forma convencional ya vista en algoritmos anteriores
void conventionalMult(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
}

// algortimo de strassen
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    // Definimos el tamaño nuevo de cada submatriz como la mitad del tamaño original, ya que si era
    // originalmente de tamaño 4 x 4, ahora cada submatriz sera de 2 x 2.
    if (size <= 64) { // Umbral para el uso de multiplicación convencional
        vector<vector<int>> C(size, vector<int>(size, 0));
        conventionalMult(A, B, C, size);
        return C;
    }
    int newSize = size / 2;
    // inicializamos el espacio para cada submatriz con el tamaño definido, tanto como para la
    // matriz A como la matriz B
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));
    vector<vector<int>> C11(newSize, vector<int>(newSize));
    vector<vector<int>> C12(newSize, vector<int>(newSize));
    vector<vector<int>> C21(newSize, vector<int>(newSize));
    vector<vector<int>> C22(newSize, vector<int>(newSize));

    // Dividir matrices A y B en submatrices
    for (int i = 0; i < newSize; i++) {
        // Se asignan los valores correspondientes a cada submatriz a partir de las originales
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    // inicializamos mas espacio de matrices para almacenar y calcular los resultados
    vector<vector<int>> M1(newSize, vector<int>(newSize));
    vector<vector<int>> M2(newSize, vector<int>(newSize));
    vector<vector<int>> M3(newSize, vector<int>(newSize));
    vector<vector<int>> M4(newSize, vector<int>(newSize));
    vector<vector<int>> M5(newSize, vector<int>(newSize));
    vector<vector<int>> M6(newSize, vector<int>(newSize));
    vector<vector<int>> M7(newSize, vector<int>(newSize));
    vector<vector<int>> tempA(newSize, vector<int>(newSize));
    vector<vector<int>> tempB(newSize, vector<int>(newSize));
    // se llama a la funcion addMatrix para calcular el resultado de la suma de las matrices
    addMatrix(tempA, A11, A22, newSize);
    addMatrix(tempB, B11, B22, newSize);
    //llamamos recursivamente al algortimo de strassen para calcular la sub matriz M1
    M1 = strassen(tempA, tempB, newSize);
    // Sumamos las matrices A21 y A22
    addMatrix(tempA, A21, A22, newSize);
    // llamamos rescursivamente a strassen para calcular M2
    M2 = strassen(tempA, B11, newSize);
    // restamos las matrices B12 y B22
    subtractMatrix(tempB, B12, B22, newSize);
    // llamamos rescursivamente a strassen para calcular M3
    M3 = strassen(A11, tempB, newSize);
    // restamos las matrices B21 y B11
    subtractMatrix(tempB, B21, B11, newSize);
    // llamamos rescursivamente a strassen para calcular M4
    M4 = strassen(A22, tempB, newSize);
    // Sumamos las matrices A11 y A12
    addMatrix(tempA, A11, A12, newSize);
    // llamamos rescursivamente a strassen para calcular M5
    M5 = strassen(tempA, B22, newSize);
    // restamos las matrices A21 y A11
    subtractMatrix(tempA, A21, A11, newSize);
    // Sumamos las matrices B11 y B12
    addMatrix(tempB, B11, B12, newSize);
    // llamamos rescursivamente a strassen para calcular M6
    M6 = strassen(tempA, tempB, newSize);
    // restamos las matrices A12 y A22
    subtractMatrix(tempA, A12, A22, newSize);
    // Sumamos las matrices B21 y B22
    addMatrix(tempB, B21, B22, newSize);
    // llamamos rescursivamente a strassen para calcular M7
    M7 = strassen(tempA, tempB, newSize);
    // Sumamos las matrices M1 y M2
    addMatrix(tempA, M1, M4, newSize);
    // restamos las matrices tempA y M5
    subtractMatrix(tempB, tempA, M5, newSize);
    // Sumamos las matrices temB y M7
    addMatrix(C11, tempB, M7, newSize);
    // Sumamos las matrices M3 y M5
    addMatrix(C12, M3, M5, newSize);
    // Sumamos las matrices M2 y M4
    addMatrix(C21, M2, M4, newSize);
    // Sumamos las matrices M1 y M3
    addMatrix(tempA, M1, M3, newSize);
    // restamos las matrices tempA y M2
    subtractMatrix(tempB, tempA, M2, newSize);
    // Sumamos las matrices tempB y M6
    addMatrix(C22, tempB, M6, newSize);
    //inicializamos el vector del resultado y asignamos los valores correspondientes
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    // retornamos el resultado de la multiplicacion
    return C;
}

// Genera una matriz de orden N x N con elementos aleatorios entre 0 y 99 para la eficioencia a la
// hora de multiplicar
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100; // Números aleatorios entre 0 y 99
        }
    }
    return matrix;
}

int main() {
    //ingresamos el valor N de la matriz N x N
    int N;
    cout << "Choose your N: ";
    cin >> N;
    //generamos e inicializamos las matrices A y B aleatorias
    vector<vector<int>> matrizA = generateMatrix(N);
    vector<vector<int>> matrizB = generateMatrix(N);
    //comenzamos a tomar el tiempo de ejecucion del algoritmo de strassen
    auto start = high_resolution_clock::now();
    vector<vector<int>> matrizResult = strassen(matrizA, matrizB, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // imprimimos en pantalla la duracion en microsegundos del algortimo
    cout << "El algoritmo ha demorado: " << duration.count() << " microsegundos" << "\n";
    return 0;
}