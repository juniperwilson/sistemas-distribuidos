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



/* Cria e inicializa uma nova lista de carros.
 * Retorna a lista ou NULL em caso de erro.
 */
struct list_t *list_create() {
    struct list_t* result = (struct list_t*) malloc(sizeof(struct list_t));
    if (result == NULL)
        return NULL;
    result->size = 0;
    result->head = NULL;
    return result;
}

/* Elimina a lista, libertando toda a memória ocupada.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int list_destroy(struct list_t *list) { 
    if (list == NULL)
        return -1;

    if (list->size == 0) {
        free(list);
        return 0;
    }

    struct car_t* current = list->head;
    while (current != NULL) {
        struct car_t* temporary = current->next;
        destroy_node(current);
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

    struct car_t* current = list->head;
    if (current == NULL) {
        list->head = (struct car_t*) malloc(sizeof(struct car_t));
        if (list->head == NULL) 
            return -1;
        list->head->data = car;
        list->head->next = NULL;
        list->size++;
        return 0;
    }

    struct car_t* node = (struct car_t*) malloc(sizeof(struct car_t));
    if (node == NULL) {
        return -1;
    }
    node->data = car;
    node->next = NULL;

    if (current->next == NULL) {
        current->next = node; 
        list->size++;
        return 0;
    }
    while (current->next != NULL) { 
        current = current->next;
    }
    current->next = node;
    list->size++;
    return 0;
}

/* Remove da lista o primeiro carro que corresponda ao modelo indicado.
 * Retorna 0 se encontrou e removeu, 1 se não encontrou, ou -1 em caso de erro.
 */
int list_remove_by_model(struct list_t *list, const char *modelo) {
    if (list == NULL || modelo == NULL)
        return -1;

    struct car_t* previous = list->head;
    if (previous == NULL)
        return -1;
   
    struct car_t* target = previous->next;
    int match = strcmp(previous->data->modelo, modelo);
    if (match == 0) {
        list->head = target;
        list->size--;
        destroy_node(previous);
        return 0;
    }

    while (target != NULL) {
        match = strcmp(target->data->modelo, modelo);
        if (match != 0) {
            previous = target;
            target = target->next;
            continue;
        }

        previous->next = target->next;
        list->size--;
        destroy_node(target);
        return 0;
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
    if (current == NULL)
        return NULL;
    int offset = 0;
    while (current != NULL) {
        if (current->data->ano == ano) {
            cars[offset] = current->data;
            offset++;
        }
        current = current->next;
    }

    struct data_t** result = (struct data_t**) malloc(sizeof(struct data_t) * offset + 1);
    if (result == NULL)
        return NULL;
    
    int i;
    for (i = 0; i < offset; i++) {
        result[i] = cars[i];
    }
    result[offset] = NULL;
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
    if (models == NULL)
        return NULL;
    
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
    free(models);
    return 0;
}

/* Function that checks if a string is present in an array of strings.
*  Returns 1 if array contains item, 0 if not, -1 if error.
*/
int contains(char** array, char* item, int size) {
    if (array == NULL || size < 0)
        return -1;
    if (size == 0) 
        return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(array[i], item) == 0)
            return 1;
    }
    return 0;
}

/* Function that splits a linked list roughly in half.
*  Returns linked list that is the second half or original list, or NULL if error.
*/
struct list_t* split(struct list_t* list) {
    if (list == NULL)
        return NULL;
    
    struct car_t* fast = list->head;
    struct car_t* slow = list->head;
    int counter = 1;
    while (fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
            counter++;
        }
    }
    struct list_t* result = (struct list_t*) malloc(sizeof(struct list_t));
    if (result == NULL)
        return NULL;

    struct car_t* head = slow->next;
    result->head = head;
    result->size = list->size - counter;
    list->size = counter;
    slow->next = NULL;
    return result;
}

/* Function that merges two linked lists that are each sorted.
*  Returns linked list, or NULL if error.
*/
struct list_t* merge(struct list_t* first, struct list_t* second) {
    if (first == NULL) return second;
    if (second == NULL) return first;

    struct list_t* result = (struct list_t*) malloc(sizeof(struct list_t));
    if (result == NULL)
        return NULL;

    while (first->size > 0 && second->size > 0) {
        struct list_t* smallest;
        if (first->head->data->ano <= second->head->data->ano) {
            smallest = first;
        } else {
            smallest = second;
        }            
        list_add(result, smallest->head->data);
        struct car_t* temp = smallest->head;
        smallest->head = smallest->head->next;
        smallest->size--;
        destroy_node(temp);        
    }
    struct list_t* rest;
    if (first->size > 0) {
        rest = first;
    } else if (second->size > 0) {
        rest = second;
    }

    while (rest->size > 0) {
        list_add(result, rest->head->data);
        struct car_t* temp = rest->head;
        rest->head = rest->head->next;
        rest->size--;
        destroy_node(temp);
    }

    list_destroy(first);
    list_destroy(second);

    return result;
}

/* Function that merge sorts a linked list.
*  Returns list ordered by year in ascending order, or NULL if error.
*/
struct list_t* mergesort(struct list_t* list) {
    if (list == NULL)
        return NULL;

    if (list->size <= 1)
        return list;

    struct list_t* second = split(list);

    list = mergesort(list);
    second = mergesort(second);

    return merge(list, second);
}

/* Function that destroys a single node.
*  Returns 0 or -1 if error.
*/
int destroy_node(struct car_t* node) {
    if (data_destroy(node->data) != 0)
            return -1;
        free(node);
    return 0;
}
