# The

A implementation of deferreds (like the ones seen in Python's Twisted), but in plain C.

## Motivation

I was bored debugging a C application and started thinking if it would be possible for the Deferred concept to be implemented in plain C, as functions are first class.

## Limitation

This code is a mere toy. Maybe one day it turns a more complete library, maybe not. It's also far from complete. The code is valid C, though. 

There's heavy use of void pointers a.k.a `void *`, which means you have to know what are you doing or code will crash. I couldn't find anything better for the time being.

## Implementation

This implemetation differs from lots of others'. As a bare C approach, there's no main loop involved to dispatch calls.

By the way, deferreds are easy. They basically store one or more actions that are dependent upon previous action result in form of functions. When a deferred is resolved, it triggers a chain of actions that may or not result in a value.

To create a deferred use:

```
The * d = the_new ();
```

To attach a callback (first responder):

```
void * on_callback (void *) {
    printf("Hello world");
}

the_add_callback (d, on_callback);
```

To resolve the deferred:

```
the_resolve (d, NULL);
```

You will see the feedback:

```
Hello World!
```

To chain operations and pass values:

```
void * on_call_1 (void * result) {
    printf("Hello from first call, %s", result);
    return "David";
}

void * on_call_2 (void * result) {
    printf("Hello from second call, %s", result);
    return "Roger";
}

the_add_callback (d, on_call_1);
the_add_callback (d, on_call_2);

void * result = the_resolve ("Syd");

printf ("Hello from main code, %s", result);
```