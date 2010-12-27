#ifndef KARVIG_INCLUDE_SLIST_H_
#define KARVIG_INCLUDE_SLIST_H_

#include "localmacros.h"

/* The node of singly pointed list data structure.
 * XXX Note that we current;y use a void* data type below. Although this is
 * present to allow generic data types to be used, it is recommended to not
 * mix data types while using the slist. slist should still work with a
 * mixture of data types but it is highly recommended not to do so for
 * clarity as well as to ensure less error prone programs.
 */
typedef struct _slist_node_t {
    struct _slist_node_t *next;
    void *data;
}slist_node_t;

/* The actual singly pointed list data structure*/
typedef struct _slist_t {
    int size;       /* Size of the list - Unused*/
    struct _slist_node_t *head;
}slist_t;

__BEGIN_DECLS

slist_t *   slist_init();
int         slist_insert(slist_t **slist, void *data);
int         slist_insert_at_front(slist_t **slist, void *data);
int         slist_delete(slist_t **slist);
int         slist_delete_at_front(slist_t **slist);
/*
extern int          slist_insert_at_end(slist_t **slist, void *data);
extern int          slist_delete_at_end(slist_t **slist, void *data);
extern int          slist_delete_in_front(slist_t **slist, void *data);
*/

__END_DECLS

#endif
