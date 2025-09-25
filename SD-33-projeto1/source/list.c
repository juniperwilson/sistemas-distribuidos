// This file was developed by June Wilson 61795
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "list-private.h"
#include "list-utils-private.h"
#include "data.h"

/**
 * @file list.h
 * @brief Interface para a estrutura da lista de automóveis.
 */

void freeTEST(void* ptr) {
    printf("FREEING %p\n", ptr);
    free(ptr);
}


/* Cria e inicializa uma nova lista de carros.
 * Retorna a lista ou NULL em caso de erro.
 */
struct list_t *list_create() {
    struct list_t* result = (struct list_t*) malloc(sizeof(struct list_t));
    if (result == NULL)
        return NULL;
    result->size = 0;
    result->head = (struct car_t*) malloc(sizeof(struct car_t));
    if (result->head == NULL) 
        return NULL;
    return result;
}

/* Elimina a lista, libertando toda a memória ocupada.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int list_destroy(struct list_t *list) { //função alterada por RIta e Filipa
    printf("GOT TO 1\n");
    if (list == NULL) {
        return -1;
    }
    if (list->size == 0) {
        free(list);
        return 0;
    }
    struct car_t* current = list->head;
    if (current == NULL)
        return -1;
    while (current != NULL) {
        struct car_t* temporary = current->next;
        if (current->data != NULL) { //destruir a data do carro caso não seja já null
            if (data_destroy(current->data) != 0)
                return -1;
        }
        free(current);
        current = temporary;
    }
    free(list); 
    return 0;
}

/* Adiciona um novo carro à lista.
 * O carro é inserido na última posição da lista.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int list_add(struct list_t *list, struct data_t *car) {
    if (list == NULL || car == NULL)
        return -1;
    struct car_t* node = (struct car_t*) malloc(sizeof(struct car_t));
    if (node == NULL) {
        return -1;
    }
    node->data = car;
    node->next = NULL;
    struct car_t* current = list->head;
    if (current == NULL) {
        free(node);
        return -1;
    }
    list->size++;
    while (current->next != NULL) { 
        current = current->next;
    }
    current->next = node;
    return 0;
}

/* Remove da lista o primeiro carro que corresponda ao modelo indicado.
 * Retorna 0 se encontrou e removeu, 1 se não encontrou, ou -1 em caso de erro.
 * DOESNT EVER RETURN -1
 */
int list_remove_by_model(struct list_t *list, const char *modelo) {
    if (list == NULL || modelo == NULL)
        return -1;
    struct car_t* current = list->head;
    if (current == NULL)
        return -1;
    while (current->next != NULL) {
        struct car_t* discard = current->next;
        if (strcmp(discard->data->modelo, modelo) == 0) {
            discard->next = current->next;
            free(discard);
            discard = NULL;
            list->size--;
            return 0;
        }
        current = current->next;
    }
    return 1;
}

/* Obtém o primeiro carro que corresponda à marca indicada.
 * Retorna ponteiro para os dados ou NULL se não encontrar ou em caso de erro.
 */
struct data_t *list_get_by_marca(struct list_t *list, enum marca_t marca) {
    if (list == NULL)
        return NULL;
    struct car_t* current = list->head;
    if (current == NULL)
        return NULL;
    while (current != NULL) {
        if (current->data->marca == marca) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

/* Obtém um array de ponteiros para carros de um determinado ano.
 * O último elemento do array é NULL.
 * Retorna o array ou NULL em caso de erro.
 */
struct data_t **list_get_by_year(struct list_t *list, int ano) {
    if (list == NULL)
        return NULL;
    struct data_t** cars = (struct data_t**) malloc(sizeof(struct data_t) * list->size + 1);
    if (cars == NULL)
        return NULL;

    struct car_t* current = list->head;
    int offset = 0;
    if (current == NULL)
        return NULL;
    while (current != NULL) {
        if (current->data->ano == ano) {
            cars[offset] = current->data;
            offset++;
        }
        current = current->next;
    }

    struct data_t** result = (struct data_t**) malloc(sizeof(struct data_t) * offset + 1);
    if (result == NULL) {
        return NULL;
    }
    int i;
    for (i = 0; i < offset; i++) {
        result[i] = cars[i];
    }
    free(cars);
    
    return result;
}

/* Ordena a lista de carros por ano de fabrico (crescente).
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int list_order_by_year(struct list_t *list) {
    return 0;
    if (list == NULL)
        return -1;

}

/* Retorna o número de carros na lista ou -1 em caso de erro.
 */
int list_size(struct list_t *list) {
    if (list == NULL)
        return -1;
    return list->size;
}

/* Constrói um array de strings com os modelos dos carros na lista.
 * O último elemento do array é NULL.
 * Retorna o array ou NULL em caso de erro.
 */
char **list_get_model_list(struct list_t *list) {
    if (list == NULL)
        return NULL;
    char** models = (char**) malloc(sizeof(char*) * list->size);
    if (models == NULL) {
        return NULL;
    }
    struct car_t* current = list->head;
    int size = 0;
    if (current == NULL)
        return NULL;
    while (current != NULL) {
        if (contains(models, current->data->modelo, size) == 0) {
            models[size] = current->data->modelo;
            size++;
        }
        current = current->next;
    }
    if (size == 0)
        return NULL;
    char** result = (char**) malloc(sizeof(char*) * size);
    if (result == NULL)
        return NULL;
    
    int i;
    for (i = 0; i < size; i++) {
        result[i] = models[i];
    }
    free(models);
    return result;
}

/* Liberta a memória ocupada pelo array de modelos.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int list_free_model_list(char **models) {
    if (models == NULL)
        return -1;
    int i = 0;
    char* current = models[0];
    while (current != NULL) {
        free(current);
        current = models[++i];
    }
    return 0;
}
