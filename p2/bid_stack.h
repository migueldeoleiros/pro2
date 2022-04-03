/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"

#define SNULL -1
#define SMAX 25 //máximo de 25 pujas

typedef struct ItemS{
    tUserId bidder;
    tProductPrice productPrice;
} tItemS;

typedef int tPosS;

typedef struct Stack {
    tItemS data[SMAX];
    tPosS top;
} tStack;

void createEmptyStack(tStack *stack);
/* Crea una pila vacia
* Entrada: Pila a inicializar
* Salida: Pila inicializada
* Postcondicion: La pila no tienen elementos
*/

bool push(tItemS item, tStack *stack);
/* Inserta un elemento en la cima de la pila. Devuelve un valor true si el elemento fue apilado; false en caso contrario.
* Entrada: El elemento a insertar y la pila 
* Salida: True en caso de que se pudiera insertar el elemento 
*         Falso en caso de que no se pudiera insertar el elemento
*/

void pop(tStack *stack);
/* Elimina de la pila el elemento situado en la cima.
* Entrada: Pila a procesar
* Salida: Pila con un elemento menos
* Precondicion: La pila no esta vacia
*/

tItemS peek(tStack stack);
/*Recupera el elemento de la cima de la pila sin eliminarlo.
* Entrada: Pila a procesar
* Salida: Elemento situado en la cima de la pila
* Precondicion: La pila no esta vacia
*/

bool isEmptyStack(tStack stack);
/* Determina si una pila está vacía o no.
* Entrada: Pila a procesar
* Salida: True si esta vacia 
*         False si contiene algun elemento
*/
#endif
