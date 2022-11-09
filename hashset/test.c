#include <stdio.h>
#include "hashset.c"

int main () {

    Hashset* test = init_set(10);
    test = put(test, "hello", 5);
    test = put(test, "test", 10);
    test = put(test, "test2", 20);
    test = put(test, "hashset", 24);
    test = put(test, "birmingham", 69);
    test = put(test, "hell", 666);
    test = put(test, "weed", 420);
    test = put(test, "horoscope", 13);

    printf("Entries: %d\n" + size(test));
    
    debug(test);
    destroy(test);

    return 0;
}