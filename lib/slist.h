#ifndef KARVIG_INCLUDE_SLIST_H_
#define KARVIG_INCLUDE_SLIST_H_

#include "localmacros.h"

typedef int     (slist_compare_func_t)(const void *, const void *); 
typedef void *  (slist_node_free_func_t)(void *); 

/** \struct
 * The node of singly pointed list data structure.
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

/* The actual singly pointed list data structure */
typedef struct _slist_t {
    int size;       /* Size of the list*/
    struct _slist_node_t *head;

    /* User supplied callback for comparing slist's data. */
    slist_compare_func_t *slist_data_compare;

    /* User supplied callback which will be called right after data is removed. */
    slist_node_free_func_t *node_free_func;
}slist_t;

/* A simple cursor that can be used to iterate over the slist */
typedef struct _slist_cursor_t {
    slist_t *slist;
    slist_node_t *node;

}slist_cursor_t;

__BEGIN_DECLS

/* SList Operations */
int         slist_len(slist_t *slist);
void        slist_set_compare_function(slist_t **slist,
                                       slist_compare_func_t *compare_func);
void        slist_set_node_free_func(slist_t **slist, 
                                     slist_node_free_func_t *free_func);

slist_t *       slist_init(void);
int             slist_insert(slist_t **slist, void *data);
int             slist_insert_at_front(slist_t **slist, void *data);
int             slist_insert_after(slist_t **slist, void *existing_data,
                                   void *new_data);
void *          slist_delete(slist_t **slist);
void *          slist_delete_at_front(slist_t **slist);
void *          slist_delete_after(slist_t **slist, void *data);
void *          slist_get_node_data(slist_node_t *node);
slist_node_t *  slist_find_node(slist_t *slist, void *data);

/* Cursor Operations on SList*/
slist_cursor_t *    slist_cursor_init(slist_t **slist);
slist_cursor_t *    slist_cursor_next(slist_cursor_t *cursor);
int                 slist_cursor_is_finished(slist_cursor_t *cursor);
void *              slist_get_cursor_data(slist_cursor_t *cursor);

__END_DECLS

#endif
