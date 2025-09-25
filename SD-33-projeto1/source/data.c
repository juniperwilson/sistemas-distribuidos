
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


/* Função que cria um novo elemento de dados data_t.
 * Retorna a nova estrutura ou NULL em caso de erro.
 */
struct data_t *data_create(int ano, float preco, enum marca_t marca, const char *modelo, enum combustivel_t combustivel){
    if(ano < 1885){ //verifica se o ano é válido
        return NULL;
    }
    
    if(preco < 0){ //verifica se o preço é válido
        return NULL;
    }

    if(marca < MARCA_TOYOTA || marca > MARCA_MERCEDES){ //verifica se a marca é válida
        return NULL;
    }

    if(modelo == NULL){ //verifica se o modelo é válido
        return NULL;
    }
    
    if(combustivel < COMBUSTIVEL_GASOLINA || combustivel > COMBUSTIVEL_HIBRIDO){ //verifica se o combustível é válido
        return NULL;
    }
    
    struct data_t *data = malloc(sizeof(struct data_t)); //aloca memória para a struct
    if (data == NULL) { //verifica se a alocação foi bem sucedida
        return NULL;
    }
   
    data->ano = ano;
    data->preco = preco;
    data->marca = marca;
    data->modelo = malloc(strlen(modelo) + 1); //aloca memória para o modelo
    if (data->modelo == NULL) {
        free(data);
        return NULL;
    }
    strcpy(data->modelo, modelo);
    data->combustivel = combustivel;
    return data;
}

/* Função que elimina um bloco de dados, libertando toda a memória por ele ocupada.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int data_destroy(struct data_t *data){
     if (data == NULL) { //verifica se a struct é válida
        return -1;
    }
   
    free(data->modelo); //liberta a memória do modelo
    free(data); //liberta a memória da struct
    return 0;
}

/* Função que duplica uma estrutura data_t.
 * Retorna a nova estrutura ou NULL em caso de erro.
 */
struct data_t *data_dup(struct data_t *data){
    if (data == NULL) {
        return NULL;
    }
    struct data_t* data_dup = (struct data_t*)malloc(sizeof(struct data_t));
    if (data_dup == NULL) {
        return NULL; 
    }
    data_dup->ano = data->ano;
    data_dup->preco = data->preco;
    data_dup->marca = data->marca;
    data_dup->modelo = malloc(strlen(data->modelo) + 1);//aloca memória para o modelo da nova struct
    if (data_dup->modelo == NULL) {
        free(data_dup);
        return NULL; 
    }
    strcpy(data_dup->modelo, data->modelo);
    data_dup->combustivel = data->combustivel;
    return data_dup;
}

/* Função que substitui o conteúdo de um elemento de dados data_t.
 * Retorna 0 (OK) ou -1 em caso de erro.
 */
int data_replace(struct data_t *data, int ano, float preco, enum marca_t marca, const char *modelo, enum combustivel_t combustivel){
    if (data == NULL) {
        return -1;
    }

    if(ano < 1885){ //verifica se o ano é válido
        return -1;
    }
    
    if(preco < 0){ //verifica se o preço é válido
        return -1;
    }

    if(marca < MARCA_TOYOTA || marca > MARCA_MERCEDES){ //verifica se a marca é válida
        return -1;
    }

    if(modelo == NULL){ //verifica se o modelo é válido
        return -1;
    }
    
    if(combustivel < COMBUSTIVEL_GASOLINA || combustivel > COMBUSTIVEL_HIBRIDO){ //verifica se o combustível é válido
        return -1;
    }
    data->ano = ano;
    data->preco = preco;
    data->marca = marca;
    
    char *new_modelo = malloc(strlen(modelo) + 1); //aloca memória para o novo modelo
    if (new_modelo == NULL) {//verifica se a alocação foi bem sucedida
        return -1;
    }
    strcpy( new_modelo, modelo); //copia o novo modelo
    free(data->modelo); //liberta a memória do modelo antigo
    data->modelo = new_modelo;
    data->combustivel = combustivel;
    return 0;
}