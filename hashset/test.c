#include <stdio.h>
#include "hashset.c"

int main () {

    Hashset* test = init_set(10);
    test = put(test, "hello", 5);
    test = put(test, "test", 10);
    test = put(test, "test2", 20);
    test = put(test, "hashset", 24);
    test = put(test, "birmingham", 71);
    test = put(test, "hell6", 6660);
    test = put(test, "frost", 430);
    test = put(test, "horoscope", 13);
    test = put(test, "greenthumb", 42);

    printf("Entries: %d\n" + size(test));
    
    debug(test);
    destroy(test);

    return 0;
}