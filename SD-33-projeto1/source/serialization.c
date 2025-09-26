#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list-private.h"
#include "serialization.h"

/* Serializa um carro (data_t) para um buffer.
 * Retorna o tamanho do buffer ou -1 em caso de erro.
 */
int car_to_buffer(struct data_t *car, char **car_buf) {
    // TODO

    // Verificar se o carro não existe
    if (car == NULL) {
        return -1;
    }

    int bufferSize = sizeof(car->ano) + sizeof(car->preco) + sizeof(car->marca) + sizeof(car->combustivel) + sizeof(car->modelo) + 1;
    *car_buf = malloc(bufferSize + sizeof(int));
    int offset = 0; // Para colocar a informação a partir da posição certa da memória - deslocamento
    // Copiar os dados do carro individualmente para o buffer
    memcpy(car_buf, &bufferSize, sizeof(int));
    offset += sizeof(int);
    memcpy(car_buf + offset, &car->ano, sizeof(car->ano));
    offset += sizeof(car->ano);
    memcpy(car_buf + offset, &car->preco, sizeof(car->preco));
    offset += sizeof(car->preco);
    memcpy(car_buf + offset, &car->marca, sizeof(car->marca));
    offset += sizeof(car->marca);
    memcpy(car_buf + offset, &car->modelo, sizeof(car->modelo));
    offset += strlen(car->modelo)+1;
    memcpy(car_buf + offset, &car->combustivel, sizeof(car->combustivel));
    offset += sizeof(car->combustivel);
   
    return bufferSize;
}

/* Desserializa um buffer para um carro (data_t).
 * Retorna o ponteiro para data_t ou NULL em caso de erro.
 */
struct data_t *buffer_to_car(char *car_buf){
    //TODO

   
    
    
    // Verificar situação de erro
    if (car_buf != NULL) {
        int offset = 0;

        int bufferSize;
        memcpy(&bufferSize, car_buf, sizeof(int));
        offset += sizeof(int);
        
        // Obter os dados do carro do buffer
        int ano;
        memcpy(&ano,car_buf + offset, sizeof(int));
        offset += sizeof(int);

        float preco;
        memcpy(&preco,car_buf + offset, sizeof(float));
        offset += sizeof(float);

        enum marca_t marca;
        memcpy(&marca,car_buf + offset, sizeof(enum marca_t));
        offset += sizeof(marca);

        char *modelo;
        memcpy(&modelo,car_buf + offset, bufferSize - offset - sizeof(enum combustivel_t)); // i think it makes sense
        offset += strlen(modelo)+1;

        enum combustivel_t combustivel;
        memcpy(&combustivel,car_buf + offset, sizeof(enum combustivel_t));
        
        // Criar um novo carro
        struct data_t *carro = data_create(ano, preco, marca, modelo, combustivel);

        if (carro == NULL) {
            return NULL;
        }

        return carro;
    }
    free(car_buf);
    return NULL;
}

/* Serializa uma lista de carros para um buffer.
 * Retorna o tamanho do buffer ou -1 em caso de erro.
 */
int car_list_to_buffer(struct list_t *list, char **list_buf){
    //TODO
    /**
     * iterar sobre cada nó da lista, começando pela cabeça
     * em cada nó, chamar a função para serializar com o no e o buffer da lista
     * no final do for, verificar tamanho do buffer e fazer return
     * Nota: é preciso alocar memória???
     */

    //not sure if it's correct
    int bufferSize = 0;
    struct car_t* current = list->head;
    if (current && list) {
        while (current) {
            int i = car_to_buffer(current->data, list_buf + bufferSize);
            if (i >= 0) {
                bufferSize += i;
            }
            current = current->next;
        }
        return bufferSize;
    }
     //NOTA: for em vez de while para usar o tamanho da lista, maybe
    return -1;
    /*  for (int i = 0; i < size; i++) {
        if (current) {
            car_to_buffer(current, list_buf);
        }
        current = current->next;
    }*/
}

/* Desserializa um buffer para uma lista de carros.
 * Retorna ponteiro para list_t ou NULL em caso de erro.
 */
struct list_t *buffer_to_car_list(char *list_buf){
    //TODO
    // perceber como mexer no buffer -> como tirar e colocar info no buffer
    //int bufferSize = 0;
    //int listSize = 0;
    struct list_t* list = list_create();
    struct car_t* current = malloc(sizeof(struct car_t));

    if (list_buf && list) {

        while (list_buf) {
            current->data = buffer_to_car(list_buf); 
            int i = list_add(list, current->data);
            if (i != 0) {
                return NULL;
            }        
        }

        return list;
    }
    free(current);
    return NULL;
}
