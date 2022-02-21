/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / 2022
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

#define LNULL NULL

typedef struct tItemL *tNode;

struct tNode {
    tItemL data;
    struct tNode *next;
};

typedef struct tNode *tPosL;
typedef struct tNode *tList;


/*Crea una lista vacía
 *Poscondición: La lista queda iniciada y no contiene elementos.
 */
void createEmptyList (tList*);

/*Determina si la lista está vacía.
 *Preconcición: Que la lista exista.
 */
bool isEmptyList(tList);

/*Devuelve la posición del último elemento de la lista
 *Precondición: La lista no está vacía
 */
tPosL first(tList);

/*Devuelve la posición del primer elemento de la lista
 *Precondición: La lista no está vacía
 */
tPosL last(tList);

/*Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 *Precondición: La posición indicada es una posición válida en la lista
 */
tPosL next(tPosL, tList);

/*Devuelve la posición en la lista del elemento previo al de la posición indicada (o LNULL si la posición no tiene anterior).
 *Precondición: La posición indicada es una posición válida en la lista
 */
tPosL previous(tPosL, tList);

/*Inserta un elemento en la lista antes de la posición indicada.
  Si la posición es LNULL, entonces se añade al final. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 *Precondición: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 *Poscondición: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haver variado.
 */
bool insertItem(tItemL, tPosL, tList*);

/*Elimina de la lista el elemento que ocupa la posición indicada.
 *Precondición: La posición indicada es una posición válida en la lista.
 *Poscondición: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado
 */
void deleteAtPosition(tPosL, tList*);

/*Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 *Precondición: La posición inndicada es una posición válida en la lista.
 */
tItemL getItem(tPosL, tList);

/*Modifica el contenido del elemento situado en la posición indicada.
 *Precondición: La posición indicada es una posición válida en la lista.
 *Poscondición: El orden de los elementos de la lista no se ve modificado.
 */
void updateItem(tItemL, tPosL, tList*);

/*Devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado
  (o LNULL si no existe tal elemento)
 *Preconcición: Que la lista exista.
 */
tPosL findItem(tProductId, tList);

#endif
