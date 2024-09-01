// Universidad del Valle de Guatemala
// Computación Paralela y Distribuida
// Javier Alvarado, Emilio Solano
// 02/09/2024

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Para la función std::swap en QuickSort

using namespace std;

// Prototipo de la función de QuickSort
void quickSort(int *array, int low, int high);

// Función para particionar el arreglo para QuickSort
int partition(int *array, int low, int high);

int main() {
    int N;
    cout << "Ingrese la cantidad de números aleatorios a generar: ";
    cin >> N;

    // Crear arreglo en memoria dinámica (Heap) usando new
    int *Array = new int[N];

    // Inicializar el generador de números aleatorios
    srand(time(0));

    // Generar N números aleatorios y escribirlos a un archivo CSV
    ofstream outFile("numeros.csv");
    if (!outFile) {
        cerr << "Error al crear el archivo 'numeros.csv'" << endl;
        delete[] Array;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        Array[i] = rand() % 1000; // Números aleatorios entre 0 y 999
        outFile << Array[i];
        if (i < N - 1) outFile << ","; // Evitar coma después del último número
    }
    outFile.close();

    // Leer números desde el archivo CSV y almacenarlos en el arreglo
    ifstream inFile("numeros.csv");
    if (!inFile) {
        cerr << "Error al abrir el archivo 'numeros.csv'" << endl;
        delete[] Array;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        char comma; // Para leer las comas
        inFile >> Array[i];
        if (i < N - 1) inFile >> comma;
    }
    inFile.close();

    // Ordenar los números usando QuickSort
    quickSort(Array, 0, N - 1);

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

    // Liberar la memoria reservada
    delete[] Array;

    cout << "Los números aleatorios han sido generados, ordenados y guardados en 'numeros_ordenados.csv'." << endl;
    return 0;
}

// Implementación de la función QuickSort
void quickSort(int *array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
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
