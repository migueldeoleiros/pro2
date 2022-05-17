/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: 27 / 04 / 2022
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

char *bidsToString(tItemL item);
/* Crea un string con información del número de pujas de un item
 *Entrada: item a porcesar
 *Salida: cadena de carácteres con el número de pujas y la mayor,
 *        en caso de no existir pujas ". No bids"
 */

float increment(tItemL item);
/* calcula el incremento de precio de un item con su mayor puja
 *Entrada: item a calcular
 *Salida: porcentaje de incremento 
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
/*Imprime un listado de los productos actuales y sus datos
 *Entrada: list lista con los datos
 *Salida: Si el listado se ha mostrado se retorna 0
 *        si hay error (la lista no existe/está vacía) se retorna 1.
 *Precondición: La lista está inicializada.
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
 *Precondición: La lista está inicializada.
 *Poscondición: Si la puja es válida se añade a la pila del producto
 *              y actualiza el contador de pujas.
 */

int delete(char *productId, tList *list);
/*Da de baja un producto (lo borra)
 *Entrada: productId ID del producto a borrar
 *         list lista donde se encuentra el producto a borrar
 *Salida: Se borra el elemento si existe y se retorna 0
 *        si no se retorna 1.
 *Precondición: La lista está inicializada.
 *Poscondición: Se elimina la pila de pujas asociada.
 */

int award(char *productId, tList *list);
/*Se asigna el ganador de una puja
 *Entrada: productId ID del producto
 *         list lista donde se encuentra el producto
 *Salida: Si se ha mostrado el ganador de la puja se retorna 0
 *        si no (no existe el producto o no hay pujas) se retorna 1.
 *Precondición: La lista está inicializada.
 */

int withdraw(char *productId, char *userId, tList *list);
/*La máxima puja actual del producto es retirada
 *Entrada: productId ID del producto 
 *         userId ID del pujador
 *         list lista que contiene el producto
 *Salida: Se modifica el producto y se retorna 0
 *        si hay error (no exite el producto, no hay pujas o userID
 *        no corresponde) se retorna 1.
 *Precondición: La lista está inicializada.
 *Poscondición: Si no hay error se decrementa el contador de pujas.
 */

int removeEmpty(tList *list);
/*Muestra y elimina los productos sin pujas 
 *Entrada: list lista con los datos
 *Salida: Si se elimina algun producto retorna 0
 *        si hay error (no existen productos sin pujas) se retorna 1.
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

char *bidsToString(tItemL item){

    if(!item.bidCounter)
        return ". No bids";

    char * out = (char*)malloc(8 * sizeof(char));
    sprintf(out," bids %d top bidder %s", item.bidCounter,
                                          peek(item.bidStack).bidder);
    return out;
}

float increment(tItemL item){
    float difference = peek(item.bidStack).productPrice - item.productPrice;
    return (difference / item.productPrice) * 100;
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
    return 1;
}

int stats(tList list) {
    tPosL pos;
    tItemL item, mostInc;
    int nBooks, nPaintings;
    float booksPrice, paintingsPrice;

    float inc=0, maxInc=0, nbids=0;
    tItemS topBid;

    if(!isEmptyList(list)){
        nBooks=0; nPaintings=0;
        booksPrice=0; paintingsPrice=0;

        //recorre la lista
        for(pos = first(list); pos != LNULL; pos = next(pos, list)){
            item = getItem(pos, list);

            printf("Product %s seller %s category %s price %.2f%s\n",
                   item.productId, item.seller, categoryToString(item.productCategory),
                   item.productPrice, bidsToString(item));

            //suma a la categoría adecuada
            if(item.productCategory == book){
                nBooks++;
                booksPrice += item.productPrice;
            }else{
                nPaintings++;
                paintingsPrice += item.productPrice;
            }

            maxInc = inc; //El anteriro inc es en nuevo maxInc
            if(!isEmptyStack(item.bidStack)){
                inc = increment(item); //calculamos nuevo inc
                nbids++;
            }

            if(inc > maxInc) mostInc = item; //Si el nuevo inc es mayor asignamos mostInc
            else inc = maxInc; //descartamos valor como nuevo maxInc 
        }

        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", nBooks, booksPrice,
               nBooks > 0 ? booksPrice/nBooks : 0);//evitar division entre 0
        printf("Painting  %8d %8.2f %8.2f\n", nPaintings, paintingsPrice,
               nPaintings > 0 ? paintingsPrice/nPaintings : 0);//evitar division entre 0
        
        if(nbids != 0){ //Solo hay TopBid si encontramos algun bidStack no vacío
            topBid = peek(mostInc.bidStack);
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   mostInc.productId, mostInc.seller, categoryToString(mostInc.productCategory),
                   mostInc.productPrice, topBid.bidder, topBid.productPrice, increment(mostInc) );
        }else
            printf("Top bid not possible\n");

        return 0;
    }
    return 1;
}

int bid(char *productId, char *userId, char *price, tList *list) {
    tItemL item;
    tItemS itemStack;
    tPosL pos;
    float nprice;
    nprice = atof(price);

    /*Uso multimples return para evitar que se ejecute código innecesario
      una vez que se incumpla una condición el sistema retorna el error 
     */

    //existe el producto
    if((pos = findItem(productId, *list)) == LNULL) return 1;
    else item = getItem(pos, *list);

    //el usuario no es el vendedor
    if(strcmp(item.seller, userId) == 0) return 1;

    //el precio de la puja es superior al precio del producto o la puja anterior 
    if((nprice <= item.productPrice) || 
       (nprice <= peek(item.bidStack).productPrice)) return 1;
    else itemStack.productPrice = nprice;

    if(strcpy(itemStack.bidder, userId) == 0) return 1;

    if(!push(itemStack, &item.bidStack)) return 1;
    item.bidCounter ++;

    updateItem(item, pos, list);
    printf("* Bid: product %s bidder %s category %s price %s bids %d\n",
            item.productId, userId, categoryToString(item.productCategory),
            price, item.bidCounter);
    return 0;
}

int delete(char *productId, tList *list) {
    tItemL item;
    tPosL pos;
    
    if((pos = findItem(productId, *list)) != LNULL){
        item = getItem(pos, *list);

        //vacía la pila de pujas
        while(!isEmptyStack(item.bidStack)){
            pop(&item.bidStack);
        }

        deleteAtPosition(pos, list);

        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, categoryToString(item.productCategory),
               item.productPrice, item.bidCounter);
        return 0;
    } 
    return 1;
}

int award(char *productId, tList *list){
    tItemL item;
    tItemS itemStack;
    tPosL pos;

    if((pos = findItem(productId, *list)) != LNULL){
        item = getItem(pos,*list);
    
        //si no tiene pujas se sale con error
        if(isEmptyStack(item.bidStack)) return 1;
        itemStack = peek(item.bidStack);

        printf("* Award: product %s bidder %s category %s price %.2f\n",
               item.productId, itemStack.bidder, categoryToString(item.productCategory),
               itemStack.productPrice);

        //borramos el elemento
        while(!isEmptyStack(item.bidStack)){
            pop(&item.bidStack);
        }
        deleteAtPosition(pos, list);

        return 0;
    } 
    return 1;
}

int withdraw(char *productId, char *userId, tList *list){
    tItemL item;
    tItemS itemStack;
    tPosL pos;

    if((pos = findItem(productId, *list)) != LNULL){
        item = getItem(pos,*list);
    
        //si no tiene pujas se sale con error
        if(isEmptyStack(item.bidStack)) return 1;
        itemStack = peek(item.bidStack);

        //si no coincide el usuario se sale con error
        if(strcmp(itemStack.bidder,userId) != 0) return 1;

        printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n",
               item.productId, itemStack.bidder, categoryToString(item.productCategory),
               itemStack.productPrice, item.bidCounter);

        //actualizar el elemento
        item.bidCounter--;
        pop(&item.bidStack);
        updateItem(item,pos,list);

        return 0;
    } 
    return 1;
}

int removeEmpty(tList *list){
    tItemL item;
    tPosL pos;
    bool isRemoved=false;

    if(!isEmptyList(*list)){

        for(pos = first(*list); pos != LNULL; pos = next(pos, *list)){
            item = getItem(pos,*list);

            if(item.bidCounter == 0){
                printf("Removing product %s seller %s category %s price %.2f bids %d\n",
                    item.productId, item.seller, categoryToString(item.productCategory),
                    item.productPrice, item.bidCounter);

                deleteAtPosition(pos, list);

                isRemoved = true;
            }
        }
        if(isRemoved) return 0; //verificamos que por lo menos un elemento se borrara
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
        case 'A': {
            printf("%s %c: product %s\n", commandNumber, command, param1);
            if(award(param1, list))
                printf("+ Error: Award not possible\n");
            break;
        }
        case 'W': {
            printf("%s %c: product %s bidder %s\n",
                   commandNumber, command, param1, param2);
            if(withdraw(param1, param2, list))
                printf("+ Error: Withdraw not possible\n");
            break;
        }
        case 'R': {
            printf("%s %c \n", commandNumber, command);
            if(removeEmpty(list))
                printf("+ Error: Remove not possible\n");
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
