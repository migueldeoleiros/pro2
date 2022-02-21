/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / 2022
 */

#include "static_list.h"
#include "string.h"
#include "types.h"
#include <stdbool.h>


//crear una lista vacía
void createEmptyList(tList* list) {

    list->lastPos = LNULL;
}

//determina si una lista está vacía
bool isEmptyList(tList list) {  

    return list.lastPos==LNULL;
}

//posición del primer elemento de la lista
tPosL first(tList list) {

    return 0;
}

//posición del último elemento de la lista
tPosL last(tList list) {

    return list.lastPos;
}

//posición del siguiente elemento en la lista
tPosL next(tPosL pos, tList list) { 

    if(pos==list.lastPos) return LNULL; //Si última posición
    else return ++pos;
}

//posición del previo elemento en la lista
tPosL previous(tPosL pos, tList list) { 

    if(pos == 0) return LNULL; //Si la posición es la primero no hay previo
    else return --pos;
}

//insertar un nuevo elemento en la lista
bool insertItem(tItemL item, tPosL pos, tList* list) { 

    if(list->lastPos==MAX-1) return false; //Si la lista está llena
    else {
        list->lastPos++;
        if (pos==LNULL){ //Si se inserta al final
            list->data[list->lastPos] = item;
        }else {
            for(tPosL i = list->lastPos; i >=pos+1; i--) {
                list->data[i] = list->data[i - 1];
            }
            list->data[pos] = item;
        }
        return true;
    }
}

//borrar el elemento de la lista en una posición dada
void deleteAtPosition(tPosL pos, tList* list) { 

    list->lastPos--;
    for(tPosL i=pos;i <=list->lastPos; i++) {
        list->data[i] = list->data[i + 1];
    }
}

//obtener un elemento de una posición dada de la lista
tItemL getItem(tPosL pos, tList list) { 

    return list.data[pos];
}

//modifica valor de un item en la lista
void updateItem(tItemL item, tPosL pos, tList* list) { 

    list->data[pos]=item;
}

//obtener la posicion de un elemento en la lista
tPosL findItem(tProductId productId, tList list) { 

    if(isEmptyList(list)) return LNULL; //Si la lista está vacía
    else {
        for(tPosL pos = first(list); pos <= list.lastPos; pos++) {
            if(strcmp(list.data[pos].productId, productId) == 0) { //Si se encuentra
                return pos;
            }
        }
        return LNULL; //Si no se encuentra
    }
}

