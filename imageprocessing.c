#include "imageprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#define UPPERLIMIT 255
#define LOWERLIMIT 0

// TODO(tudor.robu) Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            int *aux = image[i][j];
            image[i][j] = image[i][M - 1 - j];
            image[i][M- 1 - j] = aux;
        }
    }
    return image;
}

// TODO(tudor.robu) Task 2
int ***rotate_left(int ***image, int N, int M) {
    int ***copyimage = malloc(N * sizeof(int **));;
    for (int i = 0; i < N; i++) {
        copyimage[i] = malloc (M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            copyimage[i][j] = malloc (3 * sizeof(int));
            for (int k = 0; k < 3; k++) {
                copyimage[i][j][k] = image[i][j][k];
            }
        }
    }
    image = realloc (image, M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        image[i] = realloc (image[i], N * sizeof(int *));
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            image[i][j] = copyimage[j][M - 1 - i];
        }
    }
    return image;
}

// TODO(tudor.robu) Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***copyimage = malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        copyimage[i] = malloc(w * sizeof(int *));
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            copyimage[i][j] = image[y+i][x+j];
        }
    }
    return copyimage;
}

// TODO(tudor.robu) Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int ***copyimage = malloc ((N + rows * 2) * sizeof(int **));;
    for (int i = 0; i < N + 2 * rows; i ++) {
        copyimage[i] = malloc ((M + cols * 2) * sizeof(int *));
        for (int j = 0; j < M + 2 * cols; j ++) {
            copyimage[i][j] = malloc (3 * sizeof(int));
            copyimage[i][j][0] = new_R;
            copyimage[i][j][1] = new_G;
            copyimage[i][j][2] = new_B;
        }
    }
    for (int i = 0; i < N + 2 * rows; i ++) {
        if (i >= rows && i < rows + N) {
            for (int j = 0; j < M + 2 * cols; j ++)
                if (j >= cols && j < cols + M) {
                        copyimage[i][j]= image[i - rows][j - cols];
                }
        }
    }
    return copyimage;
}

// TODO(tudor.robu) Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    for (int i = 0; i < N_dst; i++) {
        for (int j = 0; j < M_dst; j++) {
            if (i >= y && j >= x) {
                for (int k = 0; k < 3; k++) {
                    if (i - y >= N_src || j - x >= M_src) {
                        break;
                    }
                    image_dst[i][j][k] = image_src[i - y][j - x][k];
                }
            }
        }
    }
    return image_dst;
}

// TODO(tudor.robu) Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int ***copyimage = calloc(N + 2 * filter_size, sizeof(int **));;
    for (int i = 0; i < N + 2 * filter_size; i++) {
        copyimage[i] = calloc (M + 2 * filter_size, sizeof(int *));
        for (int j = 0; j < M + 2 * filter_size; j++) {
            copyimage[i][j] = calloc (3, sizeof(int));
            for (int k = 0; k < 3; k++) {
                if (i < N + filter_size && i >= filter_size && j < M + filter_size && j >=filter_size) {
                    copyimage[i][j][k] = image[i - filter_size][j - filter_size][k];
                }
            }
        }
    }
    for (int i = filter_size; i < N + filter_size; i++) {
        for (int j = filter_size; j < M + filter_size; j ++) {
            for (int r = 0; r < 3; r++) {
                float sum = 0;
                for (int k = 0; k < filter_size; k++) {
                    for (int t = 0; t < filter_size; t++) {
                        int size = filter_size / 2;
                        sum = sum + (float)(copyimage[i + k - size][j + t - size][r]) * filter[k][t];
                    }
                }
                if (sum < LOWERLIMIT) {
                    sum = LOWERLIMIT;
                }
                if (sum > UPPERLIMIT) {
                    sum = UPPERLIMIT;
                }
                image[i - filter_size][j - filter_size][r] = (int)sum;
            }
        }
    }
    for (int i = 0; i < N + 2 * filter_size; i++) {
        for (int j = 0; j < M + 2 * filter_size; j++) {
            free(copyimage[i][j]);
        }
        free(copyimage[i]);
    }
    free(copyimage);
    return image;
}
