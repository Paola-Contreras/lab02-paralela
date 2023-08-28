#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <omp.h>

void quickSort(std::string *array, int left, int right);

int main() {
    std::ifstream inputFile("random_numbers.csv");
    if (!inputFile) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string line;
    std::string *csvData = nullptr; // Array
    int dataSize = 0;               // Tamaño del array

    // Leer archivo CSV
    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string field;

        // Separar por comas
        while (std::getline(ss, field, ',')) {

            // Añadir a array
            std::string *temp = new std::string[dataSize + 1];
            for (int i = 0; i < dataSize; ++i) {
                temp[i] = csvData[i];
            }

            temp[dataSize] = field;

            delete[] csvData;
            csvData = temp;
            dataSize++;
        }
    }

    inputFile.close();

     // Ordenar los datos usando QuickSort
    quickSort(csvData, 0, dataSize - 1);

    std::ofstream outputFile("data_ordenada.csv");
    if (!outputFile) {
        std::cerr << "No se pudo abrir el archivo de salida." << std::endl;
        return 1;
    }

    // Escribir en el archivo CSV
    for (int i = 0; i < dataSize; ++i) {
        outputFile << csvData[i];
        if (i < dataSize - 1) {
            outputFile << ",";
        }
    }

    outputFile.close();

    // Imprimir los datos guardados en el arreglo
    for (int i = 0; i < dataSize; ++i) {
        std::cout << csvData[i] << "\t";
    }
    std::cout << std::endl;


    // Liberar la memoria d
    delete[] csvData;

    return 0;
}

void quickSort(std::string *array, int left, int right) {
    int i = left, j = right;
    std::string pivot = array[(left + right) / 2];

    while (i <= j) {
        while (array[i] < pivot) {
            i++;
        }
        while (array[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (left < j) {
                quickSort(array, left, j);
            }
        }
        #pragma omp section
        {
            if (i < right) {
                quickSort(array, i, right);
            }
        }
    }
}
