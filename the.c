#import <stdio.h>
#import <stdlib.h>
#import <stdbool.h>
#import <errno.h>

#define THE_MAGIC 0xDEDEDE

#define debug if (0) printf
//#define debug printf

typedef void * (* TheCallback)(void *);

struct the {
    int magic;
    int depth;
    TheCallback callbacks[50]; // maximum callbacks
} the_t;

typedef struct the The;

void * the_resolve (The *, void *);

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
    The * the = (The *) d;
    
    return d ? (((The *) the)->magic == THE_MAGIC) : false;

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
};

void *
on_deferred_callback1 (void * results) {
    (void) results;

    debug ("The: On deferred callback 1\n");
    return NULL;
}

void *
on_deferred_callback2 (void * results) {
    (void) results;

    debug ("The: On deferred callback 2\n");
    return (void *) "UHAUHAUHAU";
}

void *
on_callback_deferred_1 (void * results) {
    printf("on_callback_deferred_1 = %s\n", results);

    The * d = the_new ();

    the_add_callback (d, on_deferred_callback1);

    return d;
}

void *
on_callback_deferred_2 (void * results) {
    printf("on_callback_deferred_2 = %s\n", results);

    The * d = the_new ();

    the_add_callback (d, on_deferred_callback2);

    return d;
}

void *
on_callback_1 (void * results) {
    printf("on_callback_1 = %s\n", results);

    return (void *) "on_callback_1";
}

void *
on_callback_2 (void * results) {

    printf("on_callback_2 = %s\n", results);

    return (void *) "on_callback_2";
}


int
main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    void * result;
    The *d = the_new();

    the_add_callback (d, on_callback_1);
    the_add_callback (d, on_callback_2);
    the_add_callback (d, on_callback_deferred_1);
    the_add_callback (d, on_callback_deferred_2);

    result = the_resolve (d, (void *) "resolve");

    printf ("final value -> %s\n", result);

    exit (0);

}