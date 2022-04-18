/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: 22 / 04 / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#include "product_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

char *categoryToString(tProductCategory category);
/* Pasa a tipo char* un tProductCategory
 *Entrada: category la categoría a transformar
 *Salida: char* con la equivalencia o NULL si no exites
 */

tProductCategory stringToCategory(char* category);
/* Pasa a tipo tProductCategory un char*
 *Entrada: category el string a transformar
 *Salida: tProductcategory con la equivalencia o -1 si no existe
 */

int new(char *productId, char *userId, char *productCategory,
         char *productPrice, tList *list);
/*Da de alta un nuevo producto
 *Entrada: productId ID del producto a añadir
 *         userId ID del vendedor
 *         productCategory categoria del producto
 *         productPrice precio del producto
 *         list lista a la que añadir el producto
 *Salida: Si no hay error se añade el elemento a la lista y retorna 0
 *        si no, se retorna 1.
 *Poscondición: El contador de pujas de producto se inicializa a 0
 *              y se asocia una nueva pila de pujas vacía.
 */

int stats(tList list);
/*Imprime un Listado de los productos actuales y sus datos
 *Entrada: list lista con los datos
 *Salida: Se imprime un listado con los productos y datos y retorna 0
 *        si hay error (la lista no existe/está vacía) se retorna 1.
 */

int bid(char *productId, char *userId, char *productPrice, tList *list);
/* Puja por un determinado producto, si la puja supera la más alta
 * actual se actualiza.
 *Entrada: productId ID del producto a pujar
 *         userId ID del pujador
 *         productPrice nuevo precio del producto
 *         list lista que contiene el producto
 *Salida: Se modifica el producto y se retorna 0
 *        si hay error (la puja no es válida) se retorna 1.
 *Poscondición: Si la puja es válida se añade a la pila del producto
 *              y actualiza el contador de pujas.
 */

int delete(char *productId, tList *list);
/*Da de baja un producto (lo borra)
 *Entrada: productId ID del producto a borrar
 *         list lista donde se encuentra el producto a borrar
 *Salida: Se borra el elemento si existe y se retorna 0
 *        si no se retorna 1.
 *Poscondición: Se elimina la pila de pujas asociada.
 */

int award(char *productId, tList *list);
/*Se asigna el ganador de una puja
 *Entrada: productId ID del producto
 *         list lista donde se encuentra el producto
 *Salida: Se imprime el ganador de la puja si existe y se retorna 0
 *        si no (no existe el producto o no hay pujas) se retorna 1.
 */

int withdraw(char *productId, char *userId, tList *list);
/*La máxima puja actual del producto es retirada
 *Entrada: productId ID del producto 
 *         userId ID del pujador
 *         list lista que contiene el producto
 *Salida: Se modifica el producto y se retorna 0
 *        si hay error (no exite el producto, no hay pujas o userID
 *        no corresponde) se retorna 1.
 *Poscondición: Si no hay error se decrementa el contador de pujas.
 */

int removeEmpty(tList list);
/*Elimina los productos sin pujas
 *Entrada: list lista con los datos
 *Salida: Se imprime un listado con los productos y datos borrados
 *        y retorna 0
 *        si hay error (no existen productos sin pujas) se retorna 1.
 */

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, char *param4, tList *list);
/*Dado un comando y sus parametros ejecuta la función adecuada 
 *Entrada: commandNumber el número del comando
 *         command el commando que se quiere ejecutar
 *         param.. los parametros del comando a ejecutar
 *         list la lista en la que se ejecuta el comando
 *Salida: se ejecuta el comando pedido.
 */

void readTasks(char *filename);
/*Lee cada linea de un archivo y ejecuta los comandos en ellas
 *Entrada: filename el nombre del archivo a leer
 *Salida: se llama a processCommand para cada linea.
 */


char *categoryToString(tProductCategory category){

    if(category == book)
        return "book";
    if(category == painting)
        return "painting";
    return NULL;
}

tProductCategory stringToCategory(char* category){

    if(strcmp(category, "book") == 0)
        return book;
    if(strcmp(category, "painting") == 0)
        return painting;
    return -1;
}

int new(char *productId, char *userId, char *productCategory,
         char *productPrice, tList *list) {

    tItemL item;

    strcpy(item.seller, userId);

    strcpy(item.productId, productId);
    
    //el output de stringtoCategory se comprueba abajo
    item.productCategory = stringToCategory(productCategory);
        
    item.productPrice = atof(productPrice);

    item.bidCounter = 0;

    createEmptyStack(&item.bidStack);

    if(findItem(productId, *list) == LNULL && item.productCategory != -1 &&
       insertItem(item, list)){
        printf("* New: product %s seller %s category %s price %s\n",
               productId, userId, productCategory, productPrice);
        return 0; 
    }
    printf("+ Error: New not possible\n");
    return 1;
    
}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, char *param4, tList *list) {

    printf("********************\n");

    switch (command) {
        case 'N': {
            printf("%s %c: product %s seller %s category %s price %s\n",
                   commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, list);
            break;
        }
        case 'S': {
            printf("%s %c \n", commandNumber, command);
            stats(*list);
            break;
        }
        case 'B': {
            printf("%s %c: product %s bidder %s price %s\n",
                   commandNumber, command, param1, param2, param3);
            bid(param1, param2, param3, list);
            break;
        }
        case 'D': {
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, list);
            break;
        }
        case 'A': {
            printf("%s %c: product %s\n", commandNumber, command, param1);
            award(param1, list);
            break;
        }
        case 'W': {
            printf("%s %c: product %s bidder %s\n",
                   commandNumber, command, param1, param2);
            withdraw(param1, param2, list);
            break;
        }
        case 'R': {
            printf("%s %c \n", commandNumber, command);
            removeEmpty(*list);
            break;
        }
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    //Crear lista
    tList list;
    createEmptyList(&list);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2,
                           param3, param4, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
