#import <stdio.h>
#import <stdlib.h>
#import <stdbool.h>
#import <errno.h>

#include "the.h"

void * on_call_1 (void * result) {
    printf("Hello from first call, %s\n", result);
    return (void *) "David";
}

void * on_call_2 (void * result) {
    printf("Hello from second call, %s\n", result);
    return (void *) "Roger";
}


int
main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    void * result;
    The *d = the_new();

    the_add_callback (d, on_call_1);
    the_add_callback (d, on_call_2);

    result = the_resolve (d, (void *) "Syd");

    printf ("Hello from main code, %s\n", result);

    exit (0);

}