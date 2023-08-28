#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(int argc, char* argv[]) {
    int num = 0;
    int rand_num = 0;
    // Verificar que se hayan ingresado 3 parametros y asignar valores 
    if (argc > 1) {
        num = atof(argv[1]);
    } else {
        printf("Please add a number!\n");
        return 1;
    }

    srand(time(NULL));

    // Generar archivo con data random 
    FILE* file = fopen("random_numbers.csv", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        rand_num = rand() % num;
        fprintf(file, "%d", rand_num);
        printf("rand_num: %d \n", rand_num);

        if (i < num - 1) {
            fprintf(file, ",");
        }
    }

    fclose(file);

    return 0;
}
