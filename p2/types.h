#ifndef PRO2_2022_P2_TYPES_H
#define PRO2_2022_P2_TYPES_H


#define NAME_LENGTH_LIMIT 10


typedef char tUserId[NAME_LENGTH_LIMIT];

typedef char tProductId[NAME_LENGTH_LIMIT];

typedef enum {book, painting} tProductCategory;

typedef float tProductPrice;

typedef int tBidCounter;


#endif //PRO2_2022_P2_TYPES_H
