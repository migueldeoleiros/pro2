/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: 04 / 03 / 2022
 */

#include "dynamic_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"
#include "types.h"

/*Determina si hay memoria suficiente para almacenar un elemento nuevo de la lista.
 *Entrada: Puntero a la posición a reservar
 *Salida: true en caso de que haya memoria, false en caso contrario.
 */
bool createNode(tPosL *pos) {
    *pos = malloc(sizeof(struct tNode));
    return *pos != LNULL;
}

//crear una lista vacía
void createEmptyList(tList* list) { 

    *list = LNULL;
}

//determina si una lista está vacía
bool isEmptyList(tList list) { 

    return list==LNULL;
}

//posición del primer elemento de la lista
tPosL first(tList list) {

    return list;
}

//posición del último elemento de la lista
tPosL last(tList list) {
    tPosL pos;

    for(pos = list; pos->next != LNULL; pos = pos->next);
    return pos;
}

//posición del siguiente elemento en la lista
tPosL next(tPosL pos, tList list) { 

    return pos->next;
}

//posición del previo elemento en la lista
tPosL previous(tPosL pos, tList list) { 
    tPosL i;

    if(pos == list) return LNULL; //si la posición es la primera no hay previo
    else {
        for(i=list;i->next != pos; i = i->next);
        return i;
    }
}

//insertar un nuevo elemento en la lista
bool insertItem(tItemL item, tPosL pos, tList* list) { 
    tPosL i,j;

    if(!createNode(&i)) return false;
    else {
        i->data = item;
        i->next = LNULL;
        if (isEmptyList(*list)) { //lista vacía
            *list = i;
        }else if(pos == LNULL) { //posicion final en lista no vacia
            for(j=*list; j->next != LNULL; j= j->next);
            j->next = i;
        }else if(pos == *list) { //insertar de primero
            i->next = pos;
            *list = i;
        }else { //caso general (insertar en medio)
            i->data = pos->data;
            pos->data = item;
            i->next = pos->next;
            pos->next = i;
        }
        return true;
    }
}

//borrar el elemento de la lista en una posición dada
void deleteAtPosition(tPosL pos, tList* list) { 
    tPosL i;

    if(pos == *list) { //si primera posición
        *list = (*list)->next;
    }else if(pos->next == LNULL) { //si última posición
        for (i = *list; i->next != pos; i = i->next);
        i->next = LNULL;
    }else {
        i = pos->next;
        pos->data = i->data;
        pos->next = i->next;
        pos = i;
    }
    free(pos); //liberar memoria
}

//obtener un elemento de una posición dada de la lista
tItemL getItem(tPosL pos, tList list) { 

    return pos->data;
}

//modifica valor de un item en la lista
void updateItem(tItemL item, tPosL pos, tList* list) { 

    pos->data = item;
}

//obtener la posicion de un elemento en la lista
tPosL findItem(tProductId productId, tList list) { 
    tPosL pos;

    if(isEmptyList(list)) return LNULL; //Si la lista está vacía
    else {
        for(pos = list; strcmp(pos->data.productId, productId) != 0 && pos->next != LNULL;
            pos = pos->next);
        if(strcmp(pos->data.productId, productId) != 0) pos = LNULL;
        return pos;
    }
}

