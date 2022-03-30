#include <stdio.h>
#include <string.h>

#include "types.h"
#include "product_list.h"


void print_list(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s price %.2f", item.productId, item.productPrice);
            pos = next(pos, list);
        }
    }
    printf(" )\n");
}

int main() {
    tList list;
    tPosL pos;
    tItemL item1, item2;

    /* init */
    item1.productCategory = book;
    strcpy(item1.seller, "user1");
    item1.bidCounter = 0;


    /* create */
    createEmptyList(&list);
    print_list(list);


    /* insert */
    strcpy(item1.productId, "p3");
    item1.productPrice = 30;
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.productId, "p1");
    item1.productPrice = 10;
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.productId, "p5");
    item1.productPrice = 50;
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.productId, "p2");
    item1.productPrice = 20;
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.productId, "p4");
    item1.productPrice = 40;
    insertItem(item1, &list);
    print_list(list);


    /* find */
    pos = findItem("p33", list);
    if (pos == LNULL) {
        printf("p33 Not found\n");
    }

    pos = findItem("p1", list);
    item2 = getItem(pos, list);
    printf("%s %.2f\n", item2.productId, item2.productPrice);

    pos = findItem("p5", list);
    item2 = getItem(pos, list);
    printf("%s %.2f\n", item2.productId, item2.productPrice);

    pos = findItem("p3", list);
    item2 = getItem(pos, list);
    printf("%s %.2f\n", item2.productId, item2.productPrice);


    /* update */
    item2.productPrice = 300;
    updateItem(item2, pos, &list);
    item2 = getItem(pos, list);
    printf("%s %.2f\n", item2.productId, item2.productPrice);
    print_list(list);


    /* remove */
    deleteAtPosition(next(first(list),list), &list);  //remove p2
    print_list(list);

    deleteAtPosition(previous(last(list),list), &list);  //remove p4
    print_list(list);

    deleteAtPosition(first(list),&list);  //remove p1
    print_list(list);

    deleteAtPosition(last(list),&list);  //remove p5
    print_list(list);

    deleteAtPosition(first(list),&list);  //remove p3
    print_list(list);


    /* insert */
    insertItem(item1, &list);
    print_list(list);

    return 0;

}

