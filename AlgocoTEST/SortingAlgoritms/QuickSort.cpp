#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// Este codigo esta basado en el trabajo de Bro Code en su forma general, que incluye solo a la implementacion
// tradicional del algoritmo QuickSort, que posteriormente fue adaptado por ChatGpt a codigo en c++, usando vectores.
// https://www.youtube.com/watch?v=Vtckgz38QHs&list=LL&index=48
// El resto del codigo es implementacion propia y trabajo con ChatGpt para mover al pivote en la mediana
// e implementar el QuickSort de esta forma para el mejor caso de prueba.

//Esta funcion intercambia la direccion de memoria entre dos posiciones de un vector
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// Esta funcion retorna la posicion del nuevo pivote
int partition(std::vector<int> &array, int left, int right) {
    // se espablece el valor del pivote y el valor de i
    int pivot = array[right];
    int i = left - 1;
    // se recorre de izquierda a derecha el vector
    for (int j = left; j < right; j++) {
        // si el elemento en la posicion j del vector es menor que el pivote
        // entonces se suma 1 a i y se intercambia este elemento j con el pivote
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    // al finalizar  se intercambia la posicion del ultimo elemento de la derecha con el 
    // elemento en la posicion i + 1 del vector
    swap(array[i + 1], array[right]);
    return i + 1;
}

// esta funcion recibe un array, la posicion de la izquierda y la derecha a trabajar
void quicksort(std::vector<int> &array, int left, int right) {
    // verifica que el arreglo no sea de un tamanio ivalido para la ejecucion del algoritmo
    if (left < right) {
        // se llama a la funcion partition para obtener el pivote para la recursion
        int pivot_index = partition(array, left, right);
        // se llama recursivamente a quicksort, particionandolo de izquierda al pivote y desde
        // el pivote a la derecha, dejando al pivote en su posicion original al ya estar ordenado.
        quicksort(array, left, pivot_index - 1);
        quicksort(array, pivot_index + 1, right);
    }
}

// calcula la mediana de 3
int median_of_three(std::vector<int> &array, int left, int right) {
    // calcula la mitad como la distancia entre la posicion izquierda y la mitad de la diferencia
    // entre la posicion derecha e izquierda
    int mid = left + (right - left) / 2;
    // condiciones de intercambio entre pivotes para dejarlo en su lugar
    if (array[left] > array[mid])
        swap(array[left], array[mid]);
    if (array[left] > array[right])
        swap(array[left], array[right]);
    if (array[mid] > array[right])
        swap(array[mid], array[right]);
    // retorna la mediana
    return mid;
}

// Esta funcion retorna la posicion de la mediana
int partitionMedian(std::vector<int> &array, int left, int right) {
    // se establece la mitad como la el valor de la mediana de 3
    int mid = median_of_three(array, left, right);
    // se intercambia el valor del centro por el de mas a la derecha
    swap(array[mid], array[right]);
    // se procede como en el quicksort tradicional, como en la funcion partition
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[right]);
    // retorna el valor de la mediana
    return i + 1;
}

// esta funcion realiza el quickSort pero utilizando siempre la mediana como pivote
void quicksortMedian(std::vector<int> &array, int left, int right) {
    // verifica que el arreglo no sea de un tamanio ivalido para la ejecucion del algoritmo
    if (left < right) {
        // se establece al pivote como la mediana
        int pivot_index = partitionMedian(array, left, right);
        // se llama recursivamente al algortimo quicksortMedian
        quicksortMedian(array, left, pivot_index - 1);
        quicksortMedian(array, pivot_index + 1, right);
    }
}

// funcion que genera un vector incremental desde 1 a N
vector<int> generarVectorIncremental(int n) {
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = i + 1;
    }
    return vec;
}

//genera un vector aleatorio de largo N, estableciendo el valor minimo como 1 y el maximo como N
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
        // generamos un vector icremental
        vector<int> exampleVector = generarVectorIncremental(n);
        // comenzamos a tomar el tiempo de ejecucion del algortimo cuando el pivote es la mediana
        auto start = high_resolution_clock::now();
        quicksortMedian(exampleVector, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // guardamos la duracion de la ejecucion en microsegundos
        promedy += duration.count();
    }
    // establecemos a la posicion 0 del vector de respuestas como la duracion en el mejor caso
    respuestas[0] = promedy;

    // Caso promedio
    promedy = 0;
    for (int a = 0; a < iteraciones; ++a) {
        int minValor = 1;
        int maxValor = n;
        // se genera el vector de parametros aleatorios
        vector<int> exampleVector = generarVectorAleatorio(n, minValor, maxValor);
        // comenzamos a tomar el tiempo de ejecucion de este algortimo quicksort
        auto start = high_resolution_clock::now();
        quicksort(exampleVector, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // sumamo este valor para posteriormente calcular el promedio
        promedy += duration.count();
    }
    // establecemos a la poscion 1 del vector de resultados como el promedio de tiempo
    // de ejecucion del algortimo
    respuestas[1] = promedy / iteraciones;

    // Peor caso
    promedy = 0;
    for (int a = 0; a < 1; ++a) {
        // generamos un vector icremental
        vector<int> exampleVector = generarVectorIncremental(n);
        auto start = high_resolution_clock::now();
        // comenzamos a tomar el tiempo de ejecucion de este algortimo quicksort
        quicksort(exampleVector, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // guardamos la duracion de la ejecucion en microsegundos
        promedy += duration.count();
    }
     // establecemos a la posicion 2 del vector de respuestas como la duracion en el peor caso
    respuestas[2] = promedy;
    //retornamos el vector de largo 3 que tiene el siguiente formato:
    //[tiempo_mejor_caso, tiempo_caso_promedio, tiempo_peor_caso]
    return respuestas;
}

int main() {
    //ingresamos el valor N de la matriz N x N
    int n;
    cout << "Choose your n: ";
    cin >> n;
    vector<int> VectorTest = CompleteTestCase(n, 10); // El segundo número es la cantidad de iteraciones del caso promedio
    //imprimimimos por pantalla el resultado de los tiempos t (microsegundos) de la matriz de ancho y largo N
    for (int j = 0; j < 3; j++) {
        cout << VectorTest[j] << " ";
    }
    cout << "\n";
    return 0;
}
