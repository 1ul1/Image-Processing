#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
#define CHARACTERNUMBER 100
int main() {
    char *command = NULL;
    scanf("%s", command);
    while (1 > 0) {
        if (command[0] == 'e') {
            break;
        }
        if (command[0] == 'l') {
            int Lenght = 0, Height = 0;
            char *path = NULL;
            scanf("%d%d", &Lenght, &Height);
            scanf("%s", path);
            int ***matrix = (int ***)malloc(Lenght * sizeof(int **));
            for (int i = 0; i < Lenght; i++) {
                matrix[i] = (int **)malloc(Height * sizeof(int *));
                for (int j = 0; j < Height; j++) {
                    matrix[i][j] = (int *)malloc(3 * sizeof(int));
                }
            }
            read_from_bmp(matrix, Lenght, Height, path);
            for (int i = 0; i < Lenght; i++) {
                for (int j = 0; j < Height; j++) {
                    free(matrix[i][j]);
                }
                free(matrix[i]);
            }
            free(matrix);
        }
    }
    return 0;
}
