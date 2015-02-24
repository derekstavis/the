#import <stdio.h>
#import <stdlib.h>
#import <stdbool.h>
#import <errno.h>

#import "the.h"

#define debug if (0) printf
//#define debug printf

struct the {
    int magic;
    int depth;
    TheCallback callbacks[50]; // maximum callbacks
} the_t;

The *
the_new () {
    The *d = (The *) malloc(sizeof (the_t));

    if (NULL != d) {
        d->magic = THE_MAGIC;
        debug ("The: New @ %lld\n", (uint64_t) d);
    }
    
    return d;
}

bool
the_is_deferred (void * d) {
    return d ? (((The *) d)->magic == THE_MAGIC) : false;
}

int
the_get_depth (The *d) {
    debug ("The: Get depth -> %d\n", d->depth);
    return d->depth;
}

TheCallback
the_get_callback (The *d, int i) {
    if (i >= 0 && i < d->depth) {
        debug ("The: Get callback (@ %lld, %d) -> @ %lld\n"
            , (uint64_t) d
            , i
            , (uint64_t) d->callbacks[i]);

        return (d->callbacks[i]);
    } else {
        debug ("The: No more callbacks\n");
    }

    return NULL;
}

The *
the_add_callback (The *d, TheCallback callback) {
    int depth = d->depth;
    
    d->callbacks[depth] = callback;

    d->depth++;

    return d;
}

void *
the_resolve (The *d, void * value) {
    TheCallback callback;
    void * result;
    int i = 0;
    
    for (; NULL != (callback = the_get_callback (d, i)); i++) {
        result = callback (value);

        while (the_is_deferred (result)) {
            debug ("The: Resolving nested deferred\n");
            result = (void *) the_resolve ((The *) result, value);
        }

        value = result;
         
    }

    return value;
}
