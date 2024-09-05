#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// Las funciones proporcionadas por ChatGpt son las de merge y mergeSort que estan basadas en el trabajo de
// Bro code, quien proporciono el codigo en java que posteriormente
// fue adaptado a c++ y luego al codigo de testeo.
// https://www.youtube.com/watch?v=3j0SWDX4AtU&list=LL&index=52
// Función para fusionar dos subvectores en un solo vector ordenado
void merge(vector<int>& vec, int left, int mid, int right) {
    // Tamaño de los subvectores
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear vectores temporales
    vector<int> L(n1);
    vector<int> R(n2);

    // Copiar los datos a los vectores temporales
    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    // Fusionar los vectores temporales de vuelta al vector original
    int i = 0; // Índice inicial del primer subvector
    int j = 0; // Índice inicial del segundo subvector
    int k = left; // Índice inicial del vector fusionado

    //Se construye un while que recorre simultaneamente ambos vectores y
    //los compara posicion por posicion tal que: 
    while (i < n1 && j < n2) {
        //Entra al if si la posicion i del vector L(left) es menor o igual a la posicion
        //j del vector R (Right), de ser asi en el vector de salida se inserta en la posicion k
        //el valor del elemento en la posicion i del vector L.
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            //En el caso contrario el elemento j del vector R es menor, por lo que se inserta
            //en la posicion k del vector de salida 
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L, si hay alguno
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R, si hay alguno
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva de Merge Sort
void mergeSort(vector<int>& vec, int left, int right) {
    //esta funcion lo que busca, a rasgos generales, es dividir a la mitad el vector
    //y ordenarlo de forma recursiva hasta que no se pueda subdividir mas
    //al final fusiona las partes que ordenadas que fueron divididas por la recursion.
    if (left < right) {
        // Encuentra el punto medio
        int mid = left + (right - left) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        // Fusionar las dos mitades ordenadas
        merge(vec, left, mid, right);
    }
}

//Inicializamos vectores incrementalel de tipo 1 a N
vector<int> generarVectorIncremental(int n){
    vector<int> vec(n);
    for(int i = 0; i < n; i++){
        vec[i] = i + 1;
    }
    return vec;
}

//Inicializamos vectores decrementales de tipo N a 1
vector<int> generarVectorDecremental(int n){
    int copy_n = n;
    vector<int> miVector = generarVectorIncremental(copy_n);
    reverse(miVector.begin(), miVector.end());
    return miVector;
}

//generamos un vector aleatorio de largo N, estableciendo el valor minimo como 1 y el maximo como N
vector<int> generarVectorAleatorio(int n, int minValor, int maxValor) { //promedy case
    vector<int> vec(n);
    
    // Configurar el generador de números aleatorios
    random_device rd; // Fuente de entropía
    mt19937 gen(rd()); // Mersenne Twister: generador de números pseudoaleatorios
    uniform_int_distribution<> dis(minValor, maxValor); // Distribución uniforme en el rango [minValor, maxValor]
    
    // Llenar el vector con valores aleatorios
    for (int i = 0; i < n; ++i) {
        vec[i] = dis(gen);
    }
    
    return vec;
}
//Esta funcion nos testea los 3 casos de prueba, el mejor caso, el caso promedio y el peor caso
//Ademas toma como entrada el largo N de la matriz y la cantidad de iteraciones para el caso aleatorio
//con la finalidad de obtener el caso promedio.
vector<int> CompleteTestCase(int n, int iteraciones){
    vector<int> respuestas(3);
    int promedy = 0;
    // mejor caso
    for (int a = 0; a < 1; ++a){
        //se genera el vector incremental
        vector<int> exampleVector = generarVectorIncremental(n);
        //se comienza a registrar el tiempo de ejecucion del algortimo
        auto start = high_resolution_clock::now();
        mergeSort(exampleVector,0,n-1);
        auto stop = high_resolution_clock::now();
        //se guarda el valor de la duracion
        auto duration = duration_cast<microseconds>(stop - start);
        promedy += duration.count();
    }
    //Se guarda en la posicion 0 del vector de respuestas el tiempo registrado
    respuestas[0] = promedy;
    promedy = 0;
    
    // caso promedio
    for (int a = 0; a < iteraciones; ++a){
        int minValor = 1;
        int maxValor = n;
        //se genera el vector de parametros aleatorios
        vector<int> exampleVector = generarVectorAleatorio(n, minValor, maxValor);
        //se comienza a registrar el tiempo de ejecucion del algortimo
        auto start = high_resolution_clock::now();
        mergeSort(exampleVector,0,n-1);
        auto stop = high_resolution_clock::now();
        //se guarda el valor de la duracion por cada iteracion
        auto duration = duration_cast<microseconds>(stop - start);
        promedy += duration.count();
    }
    //se calcula el promedio y se guarda en la posicion 1 del vector de respuestas
    promedy = promedy / iteraciones;
    respuestas[1] = promedy;
    promedy = 0;

    // peor caso
    for (int a = 0; a < 1; ++a){
        //se genera el vector decremental
        vector<int> exampleVector = generarVectorDecremental(n);
        //se comienza a registrar el tiempo de ejecucion del algortimo
        auto start = high_resolution_clock::now();
        mergeSort(exampleVector, 0, n-1);
        auto stop = high_resolution_clock::now();
        //se guarda el valor de la duracion
        auto duration = duration_cast<microseconds>(stop - start);
        promedy += duration.count();
    }
    //Se guarda en la posicion 2 del vector de respuestas el tiempo registrado
    respuestas[2] = promedy;
    promedy = 0;
    //retornamos el vector de largo 3 que tiene el siguiente formato:
    //[tiempo_mejor_caso, tiempo_caso_promedio, tiempo_peor_caso]
    return respuestas;

}

int main(){
    //ingresamos el valor N de la matriz N x N
    int n;
    cout << "choose your n: ";
    cin >> n;
    vector<int> VectorTest = CompleteTestCase(n,10); // El segundo número es la cantidad de iteraciones del caso promedio
    //imprimimimos por pantalla el resultado de los tiempos t (microsegundos) de la matriz de ancho y largo N
    for(int j = 0; j < 3; j++){ 
        cout << VectorTest[j]<< " ";
    }
    cout<<"\n";
    return 0;
}