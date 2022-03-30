#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "types.h"
#include "bid_stack.h"

void show_stack_state(tStack stack) {
    tItemS item;
    char output[128];

    bool empty = isEmptyStack(stack);
    printf("Empty stack: %s", empty?"yes":"no");
    if (!empty) {
        item = peek(stack);
        printf(", peek: %s %.2f", item.bidder, item.productPrice);
    }
    printf(".\n");

}

int main() {
    tStack stack;
    tItemS bid;

    /* create */
    createEmptyStack(&stack);
    show_stack_state(stack);


    /* push */
    printf("* Pushing some bids:\n");
    strcpy(bid.bidder, "user1");
    bid.productPrice = 10;
    push(bid, &stack);
    show_stack_state(stack);

    strcpy(bid.bidder, "user2");
    bid.productPrice = 20;
    push(bid, &stack);
    show_stack_state(stack);

    strcpy(bid.bidder, "user3");
    bid.productPrice = 30;
    push(bid, &stack);
    show_stack_state(stack);


    /* pop */
    printf("* Poping a bid:\n");
    pop(&stack);
    show_stack_state(stack);


    /* push again */
    printf("* Pushing a bid:\n");
    strcpy(bid.bidder, "user4");
    bid.productPrice = 40;
    push(bid, &stack);
    show_stack_state(stack);


    /* clear stack */
    printf("* Clearing stack:\n");
    while (!isEmptyStack(stack)) {
        pop(&stack);
        show_stack_state(stack);
    }


    /* push & pop again */
    printf("* Pushing and poping a bid:\n");
    strcpy(bid.bidder, "user5");
    bid.productPrice = 50;
    push(bid, &stack);
    show_stack_state(stack);

    pop(&stack);
    show_stack_state(stack);


}

