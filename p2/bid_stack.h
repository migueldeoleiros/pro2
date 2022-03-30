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

bool push(tItemS item, tStack *stack);

void pop(tStack *stack);

tItemS peek(tStack stack);

bool isEmptyStack(tStack stack);

#endif
