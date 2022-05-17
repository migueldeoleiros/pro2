/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: 25 / 03 / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

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
 *Precondición: La lista está inicializada.
 *Poscondición: El contador de pujas de producto se inicializa a 0
 *              y se asocia una nueva pila de pujas vacía.
 */

int stats(tList list);
/*Imprime un Listado de los productos actuales y sus datos
 *Entrada: list lista con los datos
 *Salida: Se imprime un listado con los productos y datos y retorna 0
 *        si hay error (la lista no existe/está vacía) se retorna 1.
 *Precondición: La lista está inicializada.
 */

int bid(char *productId, char *userId, char *productPrice, tList *list);
/* Puja por un determinado producto
 *Entrada: productId ID del producto a pujar
 *         userId ID del pujador
 *         productPrice nuevo precio del producto
 *         list lista que contiene el producto
 *Salida: Se modifica el producto y se retorna 0
 *        si hay error (la puja no es valida) se retorna 1.
 *Precondición: La lista está inicializada.
 *Poscondición: Si la puja es válida se modifica el precio
 *              y actualiza el contador de pujas.
 */

int delete(char *productId, tList *list);
/*Da de baja un producto (lo borra)
 *Entrada: productId ID del producto a borrar
 *         list lista donde se encuentra el producto a borrar
 *Salida: Se borra el elemento si existe y se retorna 0
 *        si no se retorna 1.
 *Precondición: La lista está inicializada.
 */

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, char *param4, tList *list);
/*Dado un comando y sus parametros ejecuta la función adecuada 
 *Entrada: commandNumber el número del comando
 *         command el commando que se quiere ejecutar
 *         param.. los parametros del comando a ejecutar
 *         list la lista en la que se ejecuta el comando
 *Precondición: La lista está inicializada.
 *Poscondición: Se ejecuta el comando pedido.
 */

void readTasks(char *filename);
/*Lee cada linea de un archivo y ejecuta los comandos en ellas
 *Entrada: filename el nombre del archivo a leer
 *Poscondición: Se llama a processCommand para cada linea.
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

    if(findItem(productId, *list) == LNULL && item.productCategory != -1 &&
       insertItem(item, LNULL, list)){
        printf("* New: product %s seller %s category %s price %s\n",
               productId, userId, productCategory, productPrice);
        return 0; 
    }
    return 1;
    
}

int stats(tList list) {
    tPosL pos;
    tItemL item;
    int nBooks, nPaintings;
    float booksPrice, paintingsPrice;

    if(!isEmptyList(list)){
        nBooks=0; nPaintings=0;
        booksPrice=0; paintingsPrice=0;

        //recorre la lista
        for(pos = first(list); pos != LNULL; pos = next(pos, list)){
            item = getItem(pos, list);

            printf("Product %s seller %s category %s price %.2f bids %d\n",
                   item.productId, item.seller, categoryToString(item.productCategory),
                   item.productPrice, item.bidCounter);

            //suma a la categoría adecuada
            if(item.productCategory == book){
                nBooks++;
                booksPrice += item.productPrice;
            }else{
                nPaintings++;
                paintingsPrice += item.productPrice;
            }
        }

        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", nBooks, booksPrice,
               nBooks > 0 ? booksPrice/nBooks : 0);//evitar division entre 0
        printf("Painting  %8d %8.2f %8.2f\n", nPaintings, paintingsPrice,
               nPaintings > 0 ? paintingsPrice/nPaintings : 0);//evitar division entre 0
        return 0;
    }
    return 1;
}

int bid(char *productId, char *userId, char *productPrice, tList *list) {
    tItemL item;
    tPosL pos;
    float nprice;
    nprice = atof(productPrice);

    /*Uso multimples return para evitar que se ejecute código innecesario
      una vez que se incumpla una condición el sistema retorna el error 
     */

    //existe el producto
    if((pos = findItem(productId, *list)) == LNULL) return 1;
    else item = getItem(pos, *list);

    //el usuario no es el vendedor
    if(strcmp(item.seller, userId) == 0) return 1;

    //el precio de la puja es superior al precio del producto o la puja anterior 
    if(nprice <= item.productPrice) return 1;
    else item.productPrice = nprice;

    item.bidCounter ++;

    updateItem(item, pos, list);
    printf("* Bid: product %s seller %s category %s price %s bids %d\n",
            item.productId, item.seller, categoryToString(item.productCategory),
            productPrice, item.bidCounter);
    return 0;
}

int delete(char *productId, tList *list) {
    tItemL item;
    tPosL pos;
    
    if((pos = findItem(productId, *list)) != LNULL){
        item = getItem(pos, *list);
        deleteAtPosition(pos, list);

        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, categoryToString(item.productCategory),
               item.productPrice, item.bidCounter);
        return 0;
    } 
    return 1;
}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, char *param4, tList *list) {

    printf("********************\n");

    switch (command) {
        case 'N': {
            printf("%s %c: product %s seller %s category %s price %s\n",
                   commandNumber, command, param1, param2, param3, param4);
            if(new(param1, param2, param3, param4, list))
                printf("+ Error: New not possible\n");
            break;
        }
        case 'S': {
            printf("%s %c \n", commandNumber, command);
            if(stats(*list))
                printf("+ Error: Stats not possible\n");
            break;
        }
        case 'B': {
            printf("%s %c: product %s bidder %s price %s\n",
                   commandNumber, command, param1, param2, param3);
            if(bid(param1, param2, param3, list))
                printf("+ Error: Bid not possible\n");
            break;
        }
        case 'D': {
            printf("%s %c: product %s\n", commandNumber, command, param1);
            if(delete(param1, list))
                printf("+ Error: Delete not possible\n");
            break;
        }
        default: {
            break;
        }
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
