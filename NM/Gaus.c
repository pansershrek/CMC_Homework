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
int32_t row_new(row_ptr *row_new, int32_t m) {
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
int32_t matrix_new(matrix_ptr *mat_new, int32_t n, int32_t m){
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
void matrix_del(matrix_ptr matr) {
    if (!matr) {
        return;
    }
    for (int32_t i = 0; i < matr->n; i++) {
        free(matr->row[i]);
    }
    free(matr->colum);
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
int32_t matrix_gen(matrix_ptr matr){
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            matr->row[i]->el[j] = el_func_gen(i, j);
        }
        matr->colum->el[i] = el_func_gen_b(i);
    }
    return 0;
}
int32_t matrix_input(matrix_ptr matr) {
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            scanf("%d", &matr->row[i]->el[j]);
        }
        scanf("%d", &matr->colum->el[i]);
    }
    return 0;
}
void matrix_output(matrix_ptr matr) {
    if (!matr) {
        return;
    }
    printf("print \n");
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            printf("%d ", matr->row[i]->el[j]);
        }
        printf("%d\n",matr->colum->el[i]);
    }
}
/////////////////////////////////////////////////////////////////////////
void int_swap(int32_t *first, int32_t *second) {
    int32_t mid = *first;
    *first = *second;
    *second = mid;
}
int32_t row_swap(row_ptr first, row_ptr second) {
    if (first->m != second->m) {
        return 1;
    }
    for (int32_t i = 0; i < first->m; i++) {
        int_swap(&first->el[i],&second->el[i]);
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////
int main(void) {
    
    matrix_ptr matr = NULL;
    if (matrix_new(&matr,5,5)) {
        matrix_del(matr);
        return 0;
    }
    printf("%d\n",matrix_gen(matr));
    matrix_output(matr);
    matrix_del(matr);
    return 0;
}