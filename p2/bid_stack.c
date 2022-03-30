/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#include "bid_stack.h"

void createEmptyStack(tStack *stack) { stack->top = SNULL; }

bool push(tItemS item, tStack *stack) {
    if (stack->top == SMAX - 1) { //si pila llena
        return false;
    } else { 
        stack->top++;
        stack->data[stack->top] = item;
    }
    return true;
}

void pop(tStack *stack) {
    stack->top--; 
}

tItemS peek(tStack stack) {
    return stack.data[stack.top];
}

bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}
