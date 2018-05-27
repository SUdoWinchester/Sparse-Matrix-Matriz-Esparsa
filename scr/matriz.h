#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Node
{
    int value, i, j;
    struct Node *right;
    struct Node *down;
} node;

typedef struct
{
    node *first;
    int m;
    int n;
} sparse_matrix;

sparse_matrix *new_sparce_matrix(int m, int n);
node *create_node(int x, int i, int j);
void set_value(sparse_matrix *a, int value, int i, int j);
void print(sparse_matrix *a);
int existeI(sparse_matrix *a, int i);
int existeJ(sparse_matrix *a, int j);
void clear_sparce_matrix(sparse_matrix *a);
int get_value(sparse_matrix *a, int i, int j);
sparse_matrix *add_sparse_matrix(sparse_matrix *a, sparse_matrix *b);
sparse_matrix *multiply_sparse_matrix(sparse_matrix *a, sparse_matrix *b);

#endif
