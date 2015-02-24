#define THE_MAGIC 0xDEDEDE

typedef struct the The;

typedef void * (* TheCallback)(void *);

The * the_new ();
The * the_add_callback (The *d, TheCallback callback);
void * the_resolve (The *d, void * value);
bool the_is_deferred (void * d);
int the_get_depth (The *d);