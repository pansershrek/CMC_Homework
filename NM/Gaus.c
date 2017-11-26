// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
////////////////////////////////////////////////////////////////////////
const long double EPS= 0.00001;
enum {
    ROW_MAX_LEN = 100,
    ROW_MAX_NUM = 100,
};
typedef struct row
{
    int32_t m;
    long double el[ROW_MAX_LEN];
} row_t;
typedef row_t *row_ptr;
typedef struct matrix{
    int32_t n, m, stat;
    row_ptr row[ROW_MAX_NUM]; 
    int32_t where[ROW_MAX_LEN];
    long double ans[ROW_MAX_LEN];
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
    n++;
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
    return 0;
}
void matrix_del(matrix_ptr matr) {
    if (!matr) {
        return;
    }
    for (int32_t i = 0; i < matr->n; i++) {
        free(matr->row[i]);
    }
    free(matr);
}
/////////////////////////////////////////////////////////////////////////
int32_t el_func_gen(long double i, long double j){
    long double mid = (i + j + 5) / 2;
    return mid;
}
int32_t matrix_gen(matrix_ptr matr){
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            matr->row[i]->el[j] = el_func_gen(i, j);
        }
    }
    return 0;
}
int32_t matrix_input(matrix_ptr matr) {
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            scanf("%Lf", &matr->row[i]->el[j]);
        }
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
            printf("%5.3Lf ", matr->row[i]->el[j]);
        }
        printf("\n");
    }
}
int32_t row_copy(row_ptr r_new, row_ptr r_old) {
    r_new->m = r_old->m;
    for (int32_t i = 0; i < r_new->m; i++) {
        r_new->el[i] = r_old->el[i];
    }
    return 0;
}
int32_t matrix_copy(matrix_ptr m_new, matrix_ptr m_old) {
    if (matrix_new(&m_new,m_old->n,m_old->m)) {
        matrix_del(m_new);
        return 1;
    }
    for (int32_t i = 0; i < m_new->n; i++) {
        row_copy(m_new->row[i],m_old->row[i]);
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////
void d_swap(long double *first, long double *second) {
    long double mid = *first;
    *first = *second;
    *second = mid;
}
int32_t row_swap(row_ptr first, row_ptr second) {
    if (first->m != second->m) {
        return 1;
    }
    for (int32_t i = 0; i < first->m; i++) {
        d_swap(&first->el[i],&second->el[i]);
    }
    return 0;
}
void gaus(matrix_ptr matr, int32_t flag, long double *det) {
    int32_t m = matr->m - 1;
    if (flag) {
        m++;
    }
    (*det) = 1;
    for (int32_t i = 0; i < matr->m; i++) {
        matr->where[i] = -1;
    }
    for (int32_t i = 0, j = 0; i < matr->n && j < m; j++) {
        int i1 = i;
        for (int mid = i1; mid < matr->n; mid++) {
            if (fabs(matr->row[mid]->el[j]) > EPS) {
                i1 = mid;
                break;
            }
        }
        if (fabs(matr->row[i1]->el[j]) < EPS) {
            continue;
        }
        row_swap(matr->row[i1],matr->row[i]);
        matr->where[j] = i; 
        if (i1 != i) {
            (*det) *= -1;
        }
        (*det) *= matr->row[i]->el[i];
        for (int mid = i + 1; mid < matr->n ; mid++) {
                long double c = matr->row[mid]->el[j] / matr->row[i]->el[j];
                for (int mid1 = j; mid1 < matr->m; mid1++) {
                    matr->row[mid]->el[mid1] -= matr->row[i]->el[mid1] * c;
            }
        }
        i++;
    }
}
void gaus_modify(matrix_ptr matr, int32_t flag, long double *det) {
    int32_t m = matr->m -1 ;
    if (flag) {
        m++;
    }
    (*det) = 1;
    for (int32_t i = 0; i < matr->m; i++) {
        matr->where[i] = -1;
    }
    for (int32_t i = 0, j = 0; i < matr->n && j < m; j++) {
        int i1 = i;
        for (int mid = i1; mid < matr->n; mid++) {
            if (fabs(matr->row[mid]->el[j]) > fabs(matr->row[i1]->el[j])) {
                i1 = mid;
            }
        }
        if (fabs(matr->row[i1]->el[j]) < EPS) {
            continue;
        }
        row_swap(matr->row[i1],matr->row[i]);
        matr->where[j] = i;
        if (i1 != i) {
            (*det) *= -1;
        }
        (*det) *= matr->row[i]->el[i];
        for (int mid = i + 1; mid < matr->n ; mid++) {
                long double c = matr->row[mid]->el[j] / matr->row[i]->el[j];
                for (int mid1 = j; mid1 < matr->m; mid1++) {
                    matr->row[mid]->el[mid1] -= matr->row[i]->el[mid1] * c;
            }
          }
        i++;
    }
}
void matrix_get_ans(matrix_ptr matr) {
    for (int i = 0; i < matr->m; i++) {
        if (matr->where[i] != -1) {
            matr->ans[i] = matr->row[matr->where[i]]->el[matr->m] / matr->row[matr->where[i]]->el[i];
        }
    }
    for (int i = 0; i < matr->n; i++) {
        long double sum = 0;
        for (int j = 0; j < matr->m; j++) {
            sum +=  matr->ans[j] * matr->row[i]->el[j];
        }
        if (fabs(sum - matr->row[i]->el[matr->m]) > EPS) {
            matr->stat = 0;
            return;
        }
    }
    for (int i = 0; i < matr->m; i++) {
        if (matr->where[i] == -1) {
            matr->stat = 2;
            return;
        }
    }
    matr->stat = 1;
    return; 
}
/////////////////////////////////////////////////////////////////////////
int main(void) {
    
    /*matrix_ptr matr = NULL;
    if (matrix_new(&matr,5,5)) {
        matrix_del(matr);
        return 0;
    }
    matr->n = 4;
    matr->m = 4;
    matrix_input(matr);
    printf("Matrix \n");
    matrix_output(matr);
    gaus(matr,0);
    printf("Matrix after\n");
    matrix_output(matr);
    matrix_del(matr);*/
    return 0;
}