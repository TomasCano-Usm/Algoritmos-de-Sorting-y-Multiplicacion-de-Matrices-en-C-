#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;
// Funcion de ordenamiento IsertionSort
// Creditos al canal de YouTube "Bro Code" por la implementacion en java del algortimo.
// https://www.youtube.com/watch?v=8mJ-OhcfpYg&list=LL&index=58&t=302s
// Posteriormente fue adaptada por mi en c++.

void InsertionSort(vector<int>& vector){
    //obtenemos el tamanio del vector a ordenar
    int size = vector.size();
    //inicio del ciclo for que recorre todo el vector de tamanio N
    for(int i = 1; i < size; i++){
        //guardamos temporalmente la posicion i del vector
        int temp = vector[i];
        //establecemos a j como la posicion anterior a i
        int j = i - 1;
        //construimos un ciclo while que nos dice que si el valor del vector en la posicion j es menor a la variable
        //temporal, entonces se intercambia la posicion j del vector con la j + 1, asi hasta que j sea menor que 0
        //o que se encuentre un valor en el arreglo que sea mayor que la variable temporal 
        while(j >= 0 && vector[j] > temp){
            vector[j + 1] = vector[j];
            j--;
        }
        //se establece a la posicion j + 1 como el nuevo lugar de la variable temporal
        vector[j+1] = temp;
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
    //mejor caso
    for (int a = 0; a < 1; ++a){
        //llamamos a la funcion del vector incremental
        vector<int> exampleVector = generarVectorIncremental(n);
        //testeamos el tiempo del algortimo Insertion Sort
        auto start = high_resolution_clock::now();
        InsertionSort(exampleVector);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        promedy += duration.count();
    }
    //registramos la duracion del algoritmo en la posicion 0 del vector respuestas
    respuestas[0] = promedy;
    promedy = 0;
    //caso promedio
    for (int a = 0; a < iteraciones; ++a){
        //establecemos el valor minimo y maximo para la generacion aleatoria de los valores del arreglo
        int minValor = 1;
        int maxValor = n;
        //llamamos a la funcion generar vector aleatorio para el caso de prueba
        vector<int> exampleVector = generarVectorAleatorio(n, minValor, maxValor);
        //testeamos el tiempo del algortimo Inserton Sort
        auto start = high_resolution_clock::now();
        InsertionSort(exampleVector);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        //registramos los valores para el posterior calculo
        promedy += duration.count();
    }
    //calculamos el promedio y lo guardamos en la poscion 1 del vector
    promedy = promedy / iteraciones;
    respuestas[1] = promedy;
    promedy = 0;
    //peor caso
    for (int a = 0; a < 1; ++a){
        //Generamos el vector decremental
        vector<int> exampleVector = generarVectorDecremental(n);
        //iniciamos el registro temporal del algoritmo
        auto start = high_resolution_clock::now();
        InsertionSort(exampleVector);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        promedy += duration.count();
    }
    //registramos en la posicion 2 el tiempo registrado
    respuestas[2] = promedy;
    promedy = 0;
    //retornamos el vector de largo 3 que tiene el siguiente formato:
    //[tiempo_mejor_caso, tiempo_caso_promedio, tiempo_peor_caso]
    return respuestas;
}


int main() {
    //ingresamos el valor N de la matriz N x N
    int n , decision;
    string nombre_archivo;
    cout <<"1. generar automaticamente 2. leer archivo de prueba: ";
    cin >> decision;
    if (decision == 1){
        cout << "Ingresa el tamaño n: ";
        cin >> n;
        vector<int> VectorTest = CompleteTestCase(n, 10); // El segundo número es la cantidad de iteraciones del caso promedio
        //imprimimimos por pantalla el resultado de los tiempos t (microsegundos) de la lista de largo largo N
        for (int j = 0; j < 3; j++) {
            cout << VectorTest[j] << " ";
        }
    cout << "\n";
    }else if(decision == 2){
        cout <<"Introduce el nombre del archivo (archivo.txt): ";
        cin >> nombre_archivo;
        cout << "Ingresa el tamaño de la lista n: ";
        cin >> n;
        ifstream archivo(nombre_archivo);   // Abre el archivo usando el nombre proporcionado
        vector<int> lista_numeros;          // Declara el vector para almacenar los números
        int numero;
        if (archivo.is_open()) {            // Verifica si el archivo se abrió correctamente
            while (archivo >> numero) {     // Lee cada número del archivo
            lista_numeros.push_back(numero);  // Lo agrega al vector
            }
            archivo.close();             // Cierra el archivo
            auto start = high_resolution_clock::now();
            InsertionSort(lista_numeros);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"tiempo del algortimo: "<<duration.count()<<"\n";
        for (int n : lista_numeros) {
            cout << n << endl;
        }
        } else {
            cerr << "No se pudo abrir el archivo." << endl;
            return 1;
        }
    }
    return 0;
}
