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
    printf("Hello from first call, %s\n", result);
    return (void *) "David";
}

void * on_call_2 (void * result) {
    printf("Hello from second call, %s\n", result);
    return (void *) "Roger";
}

the_add_callback (d, on_call_1);
the_add_callback (d, on_call_2);

void * result = the_resolve (d, (void *) "Syd");

printf ("Hello from main code, %s\n", result);
```

Oh, and don't forget to free things!

```
free (d);
```

## License

The MIT License (MIT)

Copyright (c) 2015 Derek Willian Stavis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

