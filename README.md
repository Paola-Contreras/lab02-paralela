# Laboratorio 2
Computación Paralela y Distribuida

---
## Integrantes
- Paola Contreras 20213
- Paola de León 20361

---

## How to run
```
gcc -o Generate_Data Generate_Data.c
./Generate_Data 150000
```
```
gcc -o secuencial secuencial.c
time ./secuencial
```
```
g++ -o paralela paralela.cpp -fopenmp
time ./paralela
```