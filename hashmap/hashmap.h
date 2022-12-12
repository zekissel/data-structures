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

typedef struct _HashMap {
    Item* items;
    size_t entries;
    size_t capacity;
} HashMap;


HashMap* init_set(size_t size);

void destroy(HashMap* h);


HashMap* put(HashMap* h, char* key, int value);

Chain* collide (Chain* node, char* key, int value);

int get(HashMap* h, char* key);

int get_chain (Chain* node, char* key);

int size (HashMap* h);


int hash_key(char* key);

void free_chain(Chain* node);

int max(int num1, int num2) {return num1 > num2 ? num1 : num2;}

void debug(HashMap* h);

void debug_tree(Chain* node);