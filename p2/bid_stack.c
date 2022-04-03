/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#include "bid_stack.h"

//crea una pila vacia
void createEmptyStack(tStack *stack) { stack->top = SNULL; }

//Si la pila no está llena introduce un elemento en la cima de esta
bool push(tItemS item, tStack *stack) {
    if (stack->top == SMAX - 1) { //si pila llena
        return false;
    } else { 
        stack->top++;
        stack->data[stack->top] = item;
    }
    return true;
}

//Elimina el elemento situado en la cima de la pila
void pop(tStack *stack) {
    stack->top--; 
}

//Selecciona el elemento situado en la cima de la pila sin eliminarlo
tItemS peek(tStack stack) {
    return stack.data[stack.top];
}

//Determina si una pila está vacía
bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}
