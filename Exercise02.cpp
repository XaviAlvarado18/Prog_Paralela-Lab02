// Universidad del Valle de Guatemala
// Computación Paralela y Distribuida
// Javier Alvarado, Emilio Solano
// 02/09/2024

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <omp.h>

using namespace std;

void quickSort(int *array, int low, int high);

// Particionar el arreglo para QuickSort
int partition(int *array, int low, int high);

int main() {
    int N;
    cout << "Ingrese la cantidad de números aleatorios a generar: ";
    cin >> N;

    // Crear arreglo en memoria dinámica (Heap) usando new
    int *Array = new int[N];

    srand(time(0));

    ofstream outFile("numeros.csv");
    if (!outFile) {
        cerr << "Error al crear el archivo 'numeros.csv'" << endl;
        delete[] Array;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        Array[i] = rand() % 1000; // Rango de N = [0-999]
        outFile << Array[i];
        if (i < N - 1) outFile << ",";
    }
    outFile.close();

    ifstream inFile("numeros.csv");
    if (!inFile) {
        cerr << "Error al abrir el archivo 'numeros.csv'" << endl;
        delete[] Array;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        char comma; // Lectura de comas
        inFile >> Array[i];
        if (i < N - 1) inFile >> comma;
    }
    inFile.close();

    double startTime = omp_get_wtime();
    // Ordenar los números usando QuickSort en paralelo
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            quickSort(Array, 0, N - 1);
        }
    }
    double endTime = omp_get_wtime();
    double elapsed = endTime - startTime;
    cout << "Tiempo de ejecución de QuickSort en paralelo: " << elapsed << " segundos." << endl;

    // Escribir los números ordenados a un segundo archivo CSV
    ofstream sortedFile("numeros_ordenados.csv");
    if (!sortedFile) {
        cerr << "Error al crear el archivo 'numeros_ordenados.csv'" << endl;
        delete[] Array;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        sortedFile << Array[i];
        if (i < N - 1) sortedFile << ","; // Evitar coma después del último número
    }
    sortedFile.close();

    delete[] Array;

    cout << "Los números aleatorios han sido generados, ordenados y guardados en 'numeros_ordenados.csv'." << endl;
    return 0;
}

// Implementación de la función QuickSort
void quickSort(int *array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);

        // Paralelizar llamadas recursivas
        #pragma omp task
        quickSort(array, low, pivotIndex - 1);

        #pragma omp task
        quickSort(array, pivotIndex + 1, high);

        #pragma omp taskwait
    }
}

// Función para particionar el arreglo
int partition(int *array, int low, int high) {
    int pivot = array[high]; // Elegir el último elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}
