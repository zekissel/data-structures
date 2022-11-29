#include <stdlib.h>
#include <string.h>


typedef struct _Chain {
    char* key;
    int value;
    struct _Chain* left;
    struct _Chain* right;
} Chain;

typedef struct _Item {
    char* key;
    int value;
    struct _Chain* next;
} Item;

typedef struct _Hashset {
    Item* items;
    size_t entries;
    size_t capacity;
} Hashset;


Hashset* init_set(size_t size);

void destroy(Hashset* h);


Hashset* put(Hashset* h, char* key, int value);

Chain* collide (Chain* node, char* key, int value);

int get(Hashset* h, char* key);

int get_chain (Chain* node, char* key);

int size (Hashset* h);


int hash_key(char* key);

void free_chain(Chain* node);

int max(int num1, int num2) {return num1 > num2 ? num1 : num2;}

void debug(Hashset* h);

void debug_tree(Chain* node);