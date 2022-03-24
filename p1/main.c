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

void new(char *productId, char *userId, char *productCategory,
         char *productPrice, tList *list);
/*Da de alta un nuevo producto
 *Entrada: productId ID del producto a añadir
 *         userId ID del vendedor
 *         productCategory categoria del producto
 *         productPrice precio del producto
 *         list lista a la que añadir el producto
 *Salida: Se añade el elemento con los parametros dados a la lista
 *        y se notifica de ello o se notifica de un error.
 */

void stats(tList list);
/*Imprime un Listado de los productos actuales y sus datos
 *Entrada: list lista con los datos
 *Salida: Se imprime un listado con los productos y datos.
 */

void bid(char *productId, char *userId, char *productPrice, tList *list);
/* Puja por un determinado producto
 *Entrada: productId ID del producto a pujar
 *         userId ID del pujador
 *         productPrice nuevo precio del producto
 *         list lista que contiene el producto
 *Salida: Se modifica el producto y se notifica de ello o se
 *        notifica de un error.
 */

void delete(char *productId, tList *list);
/*Da de baja un producto (lo borra)
 *Entrada: productId ID del producto a borrar
 *         list lista donde se encuentra el producto a borrar
 *Salida: Se borra el elemento si existe, y se notifica de ello
 *        o se notifica de un error.
 */

char *categoryToString(tProductCategory category);
/* Pasa a tipo char* un tProductCategory
 *Entrada: category la categoría a transformar
 *Salida: char* con la equivalencia
 */


void new(char *productId, char *userId, char *productCategory,
         char *productPrice, tList *list) {

    tItemL item;

    strcpy(item.seller, userId);

    strcpy(item.productId, productId);
    
    if(strcmp(productCategory, "book") == 0)
        item.productCategory = book;
    else
        item.productCategory = painting;
        
    item.productPrice = atof(productPrice);

    item.bidCounter = 0;

    if(findItem(productId, *list) == LNULL && insertItem(item, LNULL, list)){
        printf("* New: product %s seller %s category %s price %s\n",
               productId, userId, productCategory, productPrice);
    }else 
        printf("+ Error: New not possible\n");
    
}

char *categoryToString(tProductCategory category){

    if(category == book)
        return "book";
    else
        return "painting";
}

void stats(tList list) {
    tPosL pos;
    tItemL item;
    int nBooks=0, nPaintings=0;
    float booksPrice=0, paintingsPrice=0;

    if(!isEmptyList(list)){
        nBooks=0; nPaintings=0;
        booksPrice=0; paintingsPrice=0;

        for(pos = first(list); pos != LNULL; pos = next(pos, list)){
            item = getItem(pos, list);

            printf("Product %s seller %s category %s price %.2f bids %d\n",
                   item.productId, item.seller, categoryToString(item.productCategory),
                   item.productPrice, item.bidCounter);

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
               nBooks > 0 ? booksPrice/nBooks : 0);
        printf("Painting  %8d %8.2f %8.2f\n", nPaintings, paintingsPrice,
               nPaintings > 0 ? paintingsPrice/nPaintings : 0);
        
    }else{
        printf("+ Error: Stats not posible\n");
    }
    
}

void bid(char *productId, char *userId, char *productPrice, tList *list) {
    
    tItemL item;
    tPosL pos;
    bool data = true; //será true si se cumplen las condiciones de puja

    if((pos = findItem(productId, *list)) == LNULL) data = false;
    else item = getItem(pos, *list);

    if(strcmp(item.seller, userId) == 0) data = false;

    if(item.productPrice >= atof(productPrice)) data = false;
    else item.productPrice = atof(productPrice);

    item.bidCounter ++;

    if(data){
        updateItem(item, pos, list);
        printf("* Bid: product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, categoryToString(item.productCategory)
               , item.productPrice, item.bidCounter);
    }else 
        printf("+ Error: Bid not possible\n");
}

void delete(char *productId, tList *list) {

    tItemL item;
    tPosL pos;
    
    if((pos = findItem(productId, *list)) != LNULL){
        item = getItem(pos, *list);
        deleteAtPosition(pos, list);

        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, categoryToString(item.productCategory)
               , item.productPrice, item.bidCounter);
    }else 
        printf("+ Error: Delete not possible\n");
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
