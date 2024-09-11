#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

//Este codigo esta basado en las impementaciones anteriores.
//Inicializamos vectores incrementalel de tipo 1 a N
vector<int> generarVectorIncremental(int n) {
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
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
vector<int> generarVectorAleatorio(int n, int minValor, int maxValor) {
    vector<int> vec(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minValor, maxValor);
    for (int i = 0; i < n; ++i) {
        vec[i] = dis(gen);
    }
    return vec;
}
//Esta funcion nos testea los 3 casos de prueba, el mejor caso, el caso promedio y el peor caso
//Ademas toma como entrada el largo N de la matriz y la cantidad de iteraciones para el caso aleatorio
//con la finalidad de obtener el caso promedio.
vector<int> CompleteTestCase(int n, int iteraciones) {
    vector<int> respuestas(3);
    long long promedy;

    // Mejor caso
    promedy = 0;
    for (int a = 0; a < 1; ++a) {
        //llamamos a la funcion del vector incremental
        vector<int> exampleVector = generarVectorIncremental(n);
        //inicio del registro de tiempo
        auto start = high_resolution_clock::now();
        //ordenamos la lista con la funcion de sorting
        sort(exampleVector.begin(), exampleVector.end());
        //finalizacion del registro de tiempo
        auto stop = high_resolution_clock::now();
        //calculo de la duracion
        auto duration = duration_cast<microseconds>(stop - start);
        //añadimos el valor al promedio
        promedy += duration.count();
    }
    // guardamos en la posicion 0 del vector respuestas
    respuestas[0] = promedy;

    // Caso promedio
    promedy = 0;
    for (int a = 0; a < iteraciones; ++a) {
        //establecemos el valor mayor y menor
        int minValor = 1;
        int maxValor = n;
        //llamamos a la funcion del vector incremental
        vector<int> exampleVector = generarVectorAleatorio(n, minValor, maxValor);
        //iniciamos la toma de tiempo
        auto start = high_resolution_clock::now();
        //ordenamos la lista con la funcion de sorting
        sort(exampleVector.begin(), exampleVector.end());
        auto stop = high_resolution_clock::now();
        //finalizamos la toma de tiempo
        auto duration = duration_cast<microseconds>(stop - start);
        //añadimos el valor al promedio
        promedy += duration.count();
    }
    //calculamos el promedio y lo ingresamos en la posicion 1 del vector de respuestas
    respuestas[1] = promedy / iteraciones;

    // Peor caso
    promedy = 0;
    for (int a = 0; a < 1; ++a) {
        //llamamos a la funcion del vector decremental
        vector<int> exampleVector = generarVectorDecremental(n);
        //iniciamos la toma de tiempo
        auto start = high_resolution_clock::now();
        //ordenamos la lista con la funcion de sorting
        sort(exampleVector.begin(), exampleVector.end());
        //finalizamos la toma de tiempo
        auto stop = high_resolution_clock::now();
        //calculo de la duracion
        auto duration = duration_cast<microseconds>(stop - start);
         //añadimos el valor al promedio
        promedy += duration.count();
    }
    // guardamos en la posicion 2 del vector respuestas
    respuestas[2] = promedy;
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
            sort(lista_numeros.begin(), lista_numeros.end());
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
