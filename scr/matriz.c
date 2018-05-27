#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

sparse_matrix *new_sparce_matrix(int m, int n) {
    sparse_matrix *a = (sparse_matrix *)malloc(sizeof(sparse_matrix));
    a->m = m;
    a->n = n;
    a->first = (node *)malloc(sizeof(node));
    a->first->value = 0;
    a->first->i = -1;
    a->first->j = -1;
    a->first->right = a->first;
    a->first->down = a->first;
    return a;
}

node *create_node(int value, int i, int j) {
	node *new_node = (node*) malloc(sizeof(node));
	new_node->value = value;
	new_node->i = i;
	new_node->j = j;
	new_node->right = NULL;
	new_node->down = NULL;
	return new_node;
}

void print(sparse_matrix *a) {
    if (a == NULL)
        return;

    node *first = a->first;
    node *rnode = first, *dnode = first;

    for (int i = -1; i < a->m; ++i) {
        for (int j = -1; j < a->n; ++j) {
            if (dnode != NULL && rnode != NULL && dnode->i == i && rnode->j == j) {
                printf("(%-2d,%2d)=%-5d", i, j, rnode->value);
                rnode = rnode->right;
            }
            else {
               printf("(%-2d,%2d)=%-5d", i, j, i == -1 || j == -1 ? -1 : 0);
            }
        }
        printf("\n");
        if (dnode != NULL && dnode->i == i) {
            dnode = dnode->down;
            rnode = dnode;
        }
    }	
}

int existeI(sparse_matrix *a, int i) {
	node *auxd = a->first->down;
	while(auxd != a->first) {
		if(auxd->i == i) {
			return 1;
		} else {
			auxd = auxd->down;
		}
	}
	return 0;
}

int existeJ(sparse_matrix *a, int j) {
	node *auxr = a->first->right;
	while(auxr != a->first) {
		if(auxr->j == j) {
			return 1;
		} else {
			auxr = auxr->right;
		}
	}
	return 0;
}

void set_value(sparse_matrix *a, int value, int i, int j) {
	if(a == NULL || i > a->m - 1 || j > a->n - 1) return ;

	//Matriz Nula
	if(a->first->right == a->first) {
		node *elemento = create_node(value, i, j);
		node *noder = create_node(0, -1, j);
		node *noded = create_node(0, i, -1);

		a->first->right = noder;
		a->first->down = noded;

		noder->right = a->first;
		noded->down = a->first;

		noder->down = elemento;
		noded->right = elemento;

		elemento->right = noded;
		elemento->down = noder;

		return ;
	}

	//a coluna e a linha já existem :-)
	if(existeI(a, i) == 1 && existeJ(a, j) == 1) {
		node *auxr = a->first;
		node *auxd = a->first;

		while(auxr->j != j) {
			auxr = auxr->right;
			//ta na coluna desejada
		}

		while(auxr->down->i < i && auxr->down->i != -1) {
			auxr = auxr->down;
			//ta no node acima do desejado
		}

		if(auxr->down->i == i) {
			auxr->value = value;
			return ;
		}

		while(auxd->i != i) {
			auxd = auxd->down;
			//ta na linha desejada
		}

		while(auxd->right->j < j && auxd->right->j != -1) {
			auxd = auxd->right;
			//ta no node a esquerda do desejado
		}

		node *elemento = create_node(value, i, j);

		elemento->right = auxd->right;
		auxd->right = elemento;
		elemento->down = auxr->down;
		auxr->down = elemento;

		return ;
	}

	//a linha já existe, porém a coluna não :-/
	if(existeI(a, i) == 1) {
		node *aux = a->first;

		while(aux->right != a->first && aux->right->j < j)
			aux = aux->right;
			//possui node anterior a coluna desejada
		
		node *auxr = create_node(0, -1, j);
		//auxr é a coluna desejada
		auxr->right = aux->right;
		aux->right = auxr;
		auxr->down = auxr;

		aux = a->first;
		while(aux->i != i)
			aux = aux->down;
			//aux esta na linha desejada

		while(aux->right->j < j && aux->right->j != -1)
			aux = aux->right;
			//aux esta no node anterior ao desejado

		//auxr esta acima da posição
		//aux esta a esquerda da posição

		node *elemento = create_node(value, i, j);

		elemento->down = auxr->down;
		auxr->down = elemento;
		elemento->right = aux->right;
		aux->right = elemento;

		return ;
	}

	//a coluna já existe, porém a linha não :-/
	if(existeJ(a, j) == 1) {
		node *aux = a->first;
		while(aux->down != a->first && aux->down->i < i)
			aux = aux->down;
			//possui node anterior a linha desejada
		
		node *auxd = create_node(0, i, -1);
		//auxd é a linha desejada
		auxd->down = aux->down;
		aux->down = auxd;
		auxd->right = auxd;

		aux = a->first;
		while(aux->j != j)
			aux = aux->right;
			//aux esta na coluna desejada

		while(aux->down->j < j && aux->down->j != -1)
			aux = aux->down;
			//aux esta no node anterior ao desejado

		//auxd esta a esquerda da posição
		//aux esta acima da posição

		node *elemento = create_node(value, i, j);

		elemento->right = auxd->right;
		auxd->right = elemento;
		elemento->down = aux->down;
		aux->down = elemento;

		return ;
	}

	//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\

	//node de linha e coluna não existem >:(
	node *aux = a->first;

	//criar linha:
	while(aux->down->i < i && aux->down != a->first)
		aux = aux->down;

	node *auxd = create_node(0, i, -1);

	auxd->down = aux->down;
	aux->down = auxd;
	auxd->right = auxd;

	//criar coluna:
	aux = a->first;

	while(aux->right->j < j && aux->right != a->first)
		aux = aux->right;

	node *auxr = create_node(0, -1, j);

	auxr->right = aux->right;
	aux->right = auxr;
	auxr->down = auxr;

	//Criar node do elemento a ser insirido
	node *elemento = create_node(value, i, j);

	elemento->down = auxr->down;
	auxr->down = elemento;

	elemento->right = auxd->right;
	auxd->right = elemento;

	return ;
}

void clear_sparce_matrix(sparse_matrix *a) {
	if (a == NULL)
        return;

    node *first = a->first;
    node *rnode = first, *dnode = first;

    for (int i = -1; i < a->m; ++i) {
        for (int j = -1; j < a->n; ++j) {
            if (dnode != NULL && rnode != NULL && dnode->i == i && rnode->j == j) {
                rnode->value = 0;
                rnode = rnode->right;
            }
        }
        if (dnode != NULL && dnode->i == i) {
            dnode = dnode->down;
            rnode = dnode;
        }
    }	
}

int get_value(sparse_matrix *a, int i, int j) {
	if(a == NULL || i > a->m-1 || j > a->n-1) return ;

	if(existeI(a, i) == 1) {
		node *aux = a->first;

		while(aux->i != i) {
			aux = aux->down;
		}
		while(aux->right->j < j && aux->right->j != -1) {
			aux = aux->right;
		}

		if(aux->right->j == j)
			return aux->right->value;
		else
			return 0;
	} else {
		return 0;
	}
}

sparse_matrix *add_sparse_matrix(sparse_matrix *a, sparse_matrix *b) {
	if(a == NULL || b == NULL)
		return 0;

	if(a->m != b->m || a->n != b->n) {
		printf("IMPOSSIVEL\n");
		return 0;
	}

	sparse_matrix *soma = new_sparce_matrix(a->m, a->n);

	for(int i = 0; i < a->m; i++) {
		for(int j = 0; j < a->n; j++) {
			set_value(soma, (get_value(a, i, j) + get_value(b, i, j)), i, j);
		}
	}

	return soma;
}

sparse_matrix *multiply_sparse_matrix(sparse_matrix *a, sparse_matrix *b) {
	if(a == NULL || b == NULL)
		return 0;

	if(a->n != b->m) {
		printf("IMPOSSIVEL\n");
		return 0;
	}

	sparse_matrix *mult = new_sparce_matrix(a->m, b->n);
	int soma, x = mult->m;

	for(int i = 0; i < x; i++) {
		for(int j = 0; j < x; j++) {
			soma = 0;
			for(int k = 0; k < x; k++) {
				soma += get_value(a, i, k) * get_value(b, k, j);
			}
			set_value(mult, soma, i, j);
		}
	}

	return mult;
}
