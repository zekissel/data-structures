#include "hashset.h"

Hashset* init_set (size_t size) {

    if ((long)size <= 0) return NULL;

    Hashset* h = (Hashset*)calloc(1, sizeof(Hashset));
    if (!h) return NULL;

    h->items = (Item*)calloc(size, sizeof(Item));
    if (!h->items) {
        free(h);
        return NULL;
    }

    h->entries = 0;
    h->capacity = size;

    return h;
}

Hashset* put (Hashset* h, char* key, int value) {
    
    int index = hash_key(key) % (int)h->capacity;
    Item* map = h->items;

    // change current key's value or chain key
    if (map[index].key) {
        
        int len = max(strlen(map[index].key), strlen(key));

        if (!strncmp(map[index].key, key, len)) {
            map[index].value = value;
        }
        else map[index].next = collide(map[index].next, key, value);
    }
    // add new key/value pair to array
    else {

        int span = strlen(key) + 1;
        map[index].key = (char*)malloc(span * sizeof(char));
        if (!map[index].key) return h;

        strncpy(map[index].key, key, span);
        map[index].key[span - 1] = '\0';

        map[index].value = value;
        map[index].next = NULL;
        //h->entries++;
    }
    return h;
}

Chain* collide (Chain* node, char* key, int value) {
    
    // allocate new node and key/value pair
    if (!node) {
        
        node = (Chain*)calloc(1, sizeof(Chain));
        if (!node) return NULL;

        int span = strlen(key) + 1;
        node->key = (char*)malloc(span * sizeof(char));
        if (!node->key) {
            free(node);
            return NULL;
        }
        
        strncpy(node->key, key, span);
        node->key[span - 1] = '\0';

        node->value = value;
        node->left = NULL; node->right = NULL;
    } 
    // compare keys and recurse to ordered nodes
    else {

        int len = max(strlen(node->key), strlen(key));
        if (strncmp(key, node->key, len) < 0) {

            node->left = collide(node->left, key, value);
        }
        else if (strncmp(key, node->key, len) > 0) {

            node->right = collide(node->right, key, value);
        }
        // if this node's key == key, change value
        else {
            node->value = value;
        }
        
    }
    return node;
}

int get (Hashset* h, char* key) {

    int index = hash_key(key) % (int)h->capacity;

    if (!h->items[index].key) return -1;

    // find matching key
    int len = max(strlen(h->items[index].key), strlen(key));
    if (!strncmp(h->items[index].key, key, len)) return h->items[index].value;

    else return get_chain(h->items[index].next, key);
}

// binary search chain
int get_chain (Chain* cur, char* key) {

    if (!cur) return -1;

    else {
        int len = max(strlen(cur->key), strlen(key));

        if (strncmp(key, cur->key, len) < 0) return get_chain(cur->left, key);
        if (strncmp(key, cur->key, len) > 0) return get_chain(cur->right, key);

        return cur->value;
    }
}

int size (Hashset* h) {
    if (!h) return -1;
    return (int)h->entries;
    // broken; the values at memory address allocated for entries is random
}

int hash_key (char* key) {

    int ind = 0;
    while (*key != '\0') {
        int factor = *key >> 4;
        ind += ((int)*key * factor);
        key++;
    }
    ind += (ind << 3);
    ind ^= (ind >> 5);
    ind += (ind << 11);
    return ind;
}

void destroy (Hashset* h) {
    if (h) {
        Item* tray = h->items;

        for (int i = 0; i < h->capacity; i++) {
            if (tray[i].key) {
                if (tray[i].next) free_chain(tray[i].next);
                free(tray[i].key);
            }
        }
        free(h->items);
        free(h);
    }
}

void free_chain (Chain* node) {

    if (node->left) free_chain(node->left);
    if (node->right) free_chain(node->right);

    free(node->key);
    free(node);
}

void debug (Hashset* h) {
    if (!h) return;

    Item* map = h->items;
    for (int i = 0; i < h->capacity; i++) {
        printf("set[%d] = {%s,%d} ", i, map[i].key, map[i].value);
        debug_tree(map[i].next);
        printf("\n");
    }
}

void debug_tree(Chain* node) {
    if (!node) return;

    printf(" = {%s,%d} ", node->key, node->value);
    debug_tree(node->left);
    debug_tree(node->right);
}