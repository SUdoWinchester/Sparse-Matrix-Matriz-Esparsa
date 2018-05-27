#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

void main()
{
    sparse_matrix *a = new_sparce_matrix(3, 3);
    //set_value(matriz, value, i, j);
    set_value(a, 5, 0, 0);   
    set_value(a, 3, 0, 1);
    set_value(a, 6, 0, 2);
    set_value(a, 7, 1, 0);
    set_value(a, 4, 1, 1);
    set_value(a, 8, 1, 2);
    set_value(a, 9, 2, 0);
    set_value(a, 1, 2, 1);
    set_value(a, 2, 2, 2);
    printf("Matriz A:\n");
	print(a);

    printf("\n\n");

    sparse_matrix *b = new_sparce_matrix(3, 3);
    set_value(b, 1, 1, 1);
    set_value(b, 2, 1, 0);
    set_value(b, 3, 2, 2);
    set_value(b, 4, 0, 1);
    set_value(b, 5, 2, 0);
    set_value(b, 6, 0, 0);
    printf("Matriz B:\n");
    print(b);

	printf("\n\n");
	printf("A + B:\n\n");   
    sparse_matrix *c = add_sparse_matrix(a, b);
    print(c);

   	printf("\n\n");
   	printf("A * B:\n\n");
   	sparse_matrix *d = multiply_sparse_matrix(a, b);
   	print(d);
}
