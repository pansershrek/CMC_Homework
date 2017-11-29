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
    int32_t n, m, stat, rem;
    row_ptr row[ROW_MAX_NUM]; 
    row_ptr obr[ROW_MAX_NUM];
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
int32_t row_new_obr(row_ptr *row_new, int32_t m, int32_t i) {
    if (m >= ROW_MAX_LEN) {
        return 1;
    }
    (*row_new) = (row_t*) malloc(sizeof(row_t));
    if (!(*row_new)) {
        return 1;
    }
    (*row_new)->m = m;
    (*row_new)->el[i] = 1;
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
        if (row_new_obr(&((*mat_new)->obr[i]), m, i)) {
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
int32_t row_copy(row_ptr r_new, row_ptr r_old) {
    r_new->m = r_old->m;
    for (int32_t i = 0; i < r_new->m; i++) {
        r_new->el[i] = r_old->el[i];
    }
    return 0;
}
matrix_ptr matrix_copy(matrix_ptr m_old) {
    matrix_ptr m_new;
    matrix_new(&m_new,m_old->n,m_old->m);
    for (int32_t i = 0; i < m_new->n; i++) {
        row_copy(m_new->row[i],m_old->row[i]);
    }
    return m_new;
}
int32_t matrix_input(matrix_ptr matr) {
    printf("Enter the affiliated matrix\n");
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
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m; j++) {
            printf("%5.3Lf ", matr->row[i]->el[j]);
        }
        printf("\n");
    }
}
void matrix_obr_output(matrix_ptr matr) {
    if (!matr) {
        return;
    }
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m - 1; j++) {
            printf("%5.3Lf ", matr->obr[i]->el[j]);
        }
        printf("\n");
    }
}

void matrix_output_ans(matrix_ptr matr) {
    if (!matr) {
        return;
    }
    if (matr->stat == 0) {
        printf("No ans\n");
        return;
    } else if (matr->stat == 2) {
        printf("Inf ans\n");
        return;
    }
    printf("There is an ans\n");
    for (int32_t i = 0; i < matr->m -1; i++) {
        printf("%5.3Lf ",matr->ans[i]);
    }
    printf("\n");
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
void gaus(matrix_ptr matr, int32_t flag, long double *det_out) {
    if (!matr) {
        return;
    }
    int32_t m = matr->m - 1;
    if (flag) {
        m++;
    }
    long double det = 1;
    for (int32_t i = 0; i < m; i++) {
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
        if (i1 != i) {
            det *= -1;
        }
        det *= matr->row[i]->el[i];
        if (fabs(matr->row[i1]->el[j]) < EPS) {
            continue;
        }
        row_swap(matr->row[i1],matr->row[i]);
        matr->where[j] = i; 
        
        for (int mid = 0; mid < matr->n ; mid++) {
                if (mid == i) {
                    continue;
                }
                long double c = matr->row[mid]->el[j] / matr->row[i]->el[j];
                for (int mid1 = j; mid1 < matr->m; mid1++) {
                    matr->row[mid]->el[mid1] -= matr->row[i]->el[mid1] * c;
                }
                for (int mid1 = 0; mid1 < matr->m - 1; mid1++) {
                    matr->obr[mid]->el[mid1] -= matr->obr[i]->el[mid1] * c;
                }
        }
        i++;
    }
    if (det_out) {
        *det_out = det;
    }
    matr->rem = 1;
}
void gaus_modify(matrix_ptr matr, int32_t flag, long double *det_out) {
    if (!matr) {
        return ;
    }
    int32_t m = matr->m -1 ;
    if (flag) {
        m++;
    }
    long double det = 1;
    for (int32_t i = 0; i < m; i++) {
        matr->where[i] = -1;
    }
    for (int32_t i = 0, j = 0; i < matr->n && j < m; j++) {
        int i1 = i;
        for (int mid = i1; mid < matr->n; mid++) {
            if (fabs(matr->row[mid]->el[j]) > fabs(matr->row[i1]->el[j])) {
                i1 = mid;
            }
        }
        if (i1 != i) {
            det *= -1;
        }
        det *= matr->row[i]->el[i];
        if (fabs(matr->row[i1]->el[j]) < EPS) {
            continue;
        }
        row_swap(matr->row[i1],matr->row[i]);
        matr->where[j] = i;
        
        for (int mid = 0; mid < matr->n ; mid++) {
                if (mid == i) {
                    continue;
                }
                long double c = matr->row[mid]->el[j] / matr->row[i]->el[j];
                for (int mid1 = j; mid1 < matr->m; mid1++) {
                    matr->row[mid]->el[mid1] -= matr->row[i]->el[mid1] * c;
                }
                for (int mid1 = 0; mid1 < matr->m - 1; mid1++) {
                    matr->obr[mid]->el[mid1] -= matr->obr[i]->el[mid1] * c;
                }
        }
        i++;
    }
    if (det_out) {
        *det_out = det;
    }
    matr->rem = 1;
}
void matrix_get_ans(matrix_ptr matr) {
    if (!matr->rem) {
        return;
    }
    for (int i = 0; i < matr->m - 1; i++) {
        if (matr->where[i] != -1) {
            matr->ans[i] = matr->row[matr->where[i]]->el[matr->m - 1] / matr->row[matr->where[i]]->el[i];
        }
    }
    for (int i = 0; i < matr->n; i++) {
        long double sum = 0;
        for (int j = 0; j < matr->m - 1; j++) {
            sum +=  matr->ans[j] * matr->row[i]->el[j];
        }
        if (fabs(sum - matr->row[i]->el[matr->m - 1]) > EPS) {
            matr->stat = 0;
            return;
        }
    }
    for (int i = 0; i < matr->m - 1; i++) {
        if (matr->where[i] == -1) {
            matr->stat = 2;
            return;
        }
    }
    matr->stat = 1;
    return; 
}
int matrix_obr(matrix_ptr matr) {
    if (!matr || (matr->stat != 1)) {
        return 1;
    }
    for (int32_t i = 0; i < matr->n; i++) {
        for (int32_t j = 0; j < matr->m - 1; j++) {
            matr->obr[i]->el[j] /= matr->row[i]->el[i];
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////
int main(void) {
    matrix_ptr matr = NULL, matr1 = NULL;
    int n, type;
    long double det;
    printf("Enter the type of input (1 <=> from input | 2 <=> gen by formula)\n");
    scanf("%d",&type);
    if (type == 1) {
        printf("Enter the dimension of matrix\n");
        scanf("%d",&n);
        matrix_new(&matr,n,n + 1);
        matrix_input(matr);
    } else {
        printf("Enter the dimension of matrix\n");
        scanf("%d",&n);
        matrix_new(&matr,n,n + 1);
        matrix_gen(matr);
    }
    matr1 = matrix_copy(matr);
    printf("Solve by modify Gause method\n");
    gaus_modify(matr1, 0, NULL);
    matrix_get_ans(matr1);
    matrix_output_ans(matr1);
    printf("Solve by Gause method\n");
    matr1 = matrix_copy(matr);
    gaus(matr1, 0, &det);
    matrix_get_ans(matr1);
    matrix_output_ans(matr1);
    if (matr1->stat == 1) {
        printf("The det of matrix is %5.3Lf\n", det);
    }
    if (!matrix_obr(matr1)) {
        printf("The reverse matrix is \n");
        matrix_obr_output(matr1);
    }
    return 0;
}