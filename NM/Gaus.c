// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////
enum {
    ROW_MAX_LEN = 100,
    ROW_MAX_NUM = 100,
};
typedef struct row
{
    int32_t m;
    int32_t el[ROW_MAX_LEN];
} row_t;
typedef row_t *row_ptr;
typedef struct matrix{
    int32_t n, m;
    row_ptr row[ROW_MAX_NUM];
    row_ptr colum;  
} matrix_t;
typedef matrix_t *matrix_ptr;
////////////////////////////////////////////////////////////////////////
int32_t __row_new(row_ptr *row_new, int32_t m) {
    if (m >= ROW_MAX_LEN) {
        return 1;
    }
    (*row_new) = (row_t*) malloc(sizeof(row_t));
    if (!(*row_new)) {
        return 1;
    }
    (*row_new)->m = m;
    return 0;
}
int32_t __matrix_new(matrix_ptr *mat_new, int32_t n, int32_t m){
    if ((n >= ROW_MAX_NUM) || (m >= ROW_MAX_LEN)) {
        return 1;
    }
    (*mat_new) = (matrix_t*) malloc(sizeof(matrix_t));
    if (!(*mat_new)) {
        return 1;
    }
    (*mat_new)->n = n;
    (*mat_new)->m = m;
    for (int32_t i = 0; i < n; i++) {
        if (row_new(&((*mat_new)->row[i]), m)) {
            return 1;
        }
    }
    if (row_new(&((*mat_new)->colum), n)) {
            return 1;
        }
    return 0;
}
void __matrix_del(matrix_ptr matr) {
    for (int32_t i = 0; i < matr->n; i++) {
        free(matr->row[i]);
    }
    free(colum);
    free(matr);
}
/////////////////////////////////////////////////////////////////////////
int32_t el_func_gen(int32_t i, int32_t j){
    int32_t mid = (i + j) / 2;
    return mid;
}
int32_t el_func_gen_b(int32_t i) {
    int32_t mid = i;
    return mid;
}
int32_t matrix_gen(matrix_ptr matr, int32_t n, int32_t m){
    if (__matrix_new(&matr, n, m)) {
        __matrix_del(matr);
        return 1;
    }
    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            matr->row[i]->el[m] = el_func_gen(i, j);
        }
        matr->colum->el[i] = el_func_gen_b(i);
    }
    return 0;
}
int32_t matrix_input(matrix_ptr matr, int32_t n, int32_t m) {
    if (__matrix_new(&matr, n, m)) {
        __matrix_del(matr);
        return 1;
    }
    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            scanf("%d", &matr->row[i]->el[j]);
        }
        scanf("%d", &matr->colum->el[i]);
    }
    return 0;
}
void matrix_output(matrix_ptr matr, int32_t n, int32_t m) {
    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j <m; j++) {
            printf("%d ", matr->row[i]->el[j]);
        }
        printf("%d\n",matr->colum->el[i]);
    }
}
/////////////////////////////////////////////////////////////////////////
int main(void) {
    printf("%d\n",el_func_gen(1, 2));
    return 0;
}