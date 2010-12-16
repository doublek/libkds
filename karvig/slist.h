#ifndef KARVIG_INCLUDE_SLIST_H_
#define KARVIG_INCLUDE_SLIST_H_

/* #include <inttype.h> */
#include "localmacros.h"

/* The node of singly pointed list data structure*/
struct slist_node_t {
    struct slist_node_t *next;
    void *data;         /* How to handle multiple data. Will a cast do? */
};

/* The actual singly pointed list data structure*/
struct slist_t {
    int size;       /* Size of the list - Unused*/
    struct slist_node_t *head;
};

__BEGIN_DECLS

struct slist_t *    slist_init();
int                 slist_insert(struct slist_t **slist, void *data);
int                 slist_delete(struct slist_t **slist);
void                print_list(struct slist_t *slist);
/*
extern int          slist_insert_at_end(slist_t **slist, void *data);
extern int          slist_insert_in_front(slist_t **slist, void *data);
extern int          slist_delete_at_end(slist_t **slist, void *data);
extern int          slist_delete_in_front(slist_t **slist, void *data);
*/

__END_DECLS

#endif
