/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: 04 / 03 / 2022
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
 *Entrada: lista a inicializar
 *Salida: lista inicializada
 *Poscondición: La lista queda iniciada y no contiene elementos.
 */
void createEmptyList (tList*);

/*Determina si la lista está vacía.
 *Entrada: lista a comprobar
 *Salida: booleano con el resultado de la comprobación 
 */
bool isEmptyList(tList);

/*Devuelve la posición del primer elemento de la lista
 *Entrada: lista a porcesar
 *Salida: Posición del primer elemento de la lista 
 *Precondición: La lista no está vacía
 */
tPosL first(tList);

/*Devuelve la posición del último elemento de la lista
 *Entrada: lista a porcesar
 *Salida: Posición del primer último de la lista 
 *Precondición: La lista no está vacía
 */
tPosL last(tList);

/*Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 *Entrada: lista a porcesar
 *         posición del elemento previo al que se quiere
 *Salida: Posición del siguiente elemento al indicado en la lista 
 *Precondición: La posición indicada es una posición válida en la lista
 */
tPosL next(tPosL, tList);

/*Devuelve la posición en la lista del elemento previo al de la posición indicada (o LNULL si la posición no tiene anterior).
 *Entrada: lista a porcesar
 *         posición del elemento siguiente al que se quiere
 *Salida: Posición del previo elemento al indicado en la lista 
 *Precondición: La posición indicada es una posición válida en la lista
 */
tPosL previous(tPosL, tList);

/*Inserta un elemento en la lista antes de la posición indicada.
  Si la posición es LNULL, entonces se añade al final. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 *Entrada: lista a porcesar
 *         posición del elemento a insertar o LNULL  
 *         nuevo elemento a insertar 
 *Salida: verificación de que la inserción funcionara
 *Precondición: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 *Poscondición: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haver variado.
 */
bool insertItem(tItemL, tPosL, tList*);

/*Elimina de la lista el elemento que ocupa la posición indicada.
 *Entrada: lista a porcesar
 *         posición del elemento a eliminar 
 *Salida: lista modificada 
 *Precondición: La posición indicada es una posición válida en la lista.
 *Poscondición: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado
 */
void deleteAtPosition(tPosL, tList*);

/*Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 *Entrada: lista a porcesar
 *         posición del elemento a obtener 
 *Salida: elemento en la posición dada
 *Precondición: La posición indicada es una posición válida en la lista.
 */
tItemL getItem(tPosL, tList);

/*Modifica el contenido del elemento situado en la posición indicada.
 *Entrada: lista a porcesar
 *         posición del elemento a actualizar 
 *         nuevo elemento 
 *Salida: lista actualizada
 *Precondición: La posición indicada es una posición válida en la lista.
 *Poscondición: El orden de los elementos de la lista no se ve modificado.
 */
void updateItem(tItemL, tPosL, tList*);

/*Devuelve la posición del primer elemento de la lista cuyo identificador de producto se corresponda con el indicado
  (o LNULL si no existe tal elemento)
 *Entrada: lista a porcesar
 *         identificador a buscar
 *Salida: posición del elemento que coincide con el identificador 
 */
tPosL findItem(tProductId, tList);

#endif
