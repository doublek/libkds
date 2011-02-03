#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "slist.h"

/*
 * This is what I intend to do!
 *
 *   NULL
 *    ^
 *    |
 *   head
 *
 * +-----+
 * |     |
 * |     |
 * |     |
 * +-----+
 *    ^
 *    |
 *   head
 * +-----+   +-----+
 * |     |   |     |
 * |     |-->|     |
 * |     |   |     |
 * +-----+   +-----+
 *    ^
 *    |
 *   head
 *
 */

/*
 * slist_create_node() - Create a new slist_node_t.
 *
struct slist_node_t slist_create_node(void)
{

    return NULL;
}
 */

/*
 * slist_init() - Initialize a singly linked list.
 *
 */
slist_t * slist_init(void)
{
   slist_t *slist;

    slist = malloc(sizeof(slist_t));

    if(slist == NULL)
        return NULL;

    slist->head = NULL;

    return slist;
}

/*
 * slist_insert_first_node() - Insert first node into a slist.
 *
 */
int slist_insert_first_node(slist_t **slist, void *data)
{
    slist_node_t *new_node;
    new_node = malloc(sizeof(slist_node_t));

    if (new_node == NULL)
        return ENOMEM;

    printf("Creating first element in the list with data %s\n",
            (char *)data);
    new_node->data = data;
    new_node->next = NULL;
    (*slist)->head = new_node;
    return 0;

}

/*
 * slist_insert() - Default insert operation.
 *
 * Inserts data at front. A simple wrapper that just calls
 * slist_insert_at_front().
 */
int slist_insert(slist_t **slist, void *data)
{
    return slist_insert_at_front(slist, data);
}

/*
 * slist_insert_at_front() - Default insert operation.
 *
 * Inserts data at the front of the list.
 */
int slist_insert_at_front(slist_t **slist, void *data)
{
    slist_node_t *new_node;
    new_node = malloc(sizeof(slist_node_t));

    if (new_node == NULL)
        return ENOMEM;

    /* Inserting the first element */
    if ((*slist)->head == NULL)
    {
        return slist_insert_first_node(slist, data);
    }

    printf("Inserting %s in the list\n", (char *)data);
    new_node->data = data;
    new_node->next = (*slist)->head;
    (*slist)->head = new_node;
    return 0;

}

/*
 * slist_delete() - Default delete operation.
 *
 * Deletes a node from the list. This is just a simple wrapper around the 
 * slist_delete_at_front() method.
 */
int slist_delete(slist_t **slist)
{
    return slist_delete_at_front(slist);
}

/*
 * slist_remove_at_front() - Remove from head entry.
 *
 */
int slist_delete_at_front(slist_t **slist)
{
    slist_node_t *node_to_delete;
    
    if ((*slist)->head == NULL)
    {
        printf("List empty. No operation performed\n");
        return EPERM;
    }

    node_to_delete = (*slist)->head;
    (*slist)->head = (*slist)->head->next;

    free(node_to_delete);
    return 0;
    
}

/* Data Access */

/*
 * slist_get_data() - Get the data of the current node
 *
 *
 */
void * slist_get_node_data(slist_node_t *node)
{
    if (node ==NULL)
        return EINVAL;

    return node->data;
}
/* End Data Access*/

/*
 * Begin Cursor Implementation.
 */

/*
 * slist_cursor_init() - Get a cursor iterator.
 *
 * Returns a cursor capable of iterating through the slist.
 * The initialized cursor will point to the first node of the slist.
 *
 */
slist_cursor_t * slist_cursor_init(slist_t **slist)
{
    slist_cursor_t *cursor;
    cursor = (slist_cursor_t *)malloc(sizeof(slist_cursor_t));
    cursor->slist = *slist;
    cursor->node = (*slist)->head;
    return cursor;
}

/*
 * slist_cursor_next
 */
slist_cursor_t * slist_cursor_next(slist_cursor_t *cursor)
{
    cursor->node = cursor->node->next;
    return cursor;
}

/*
 * slist_cursor_is_finished - Test if we are done interating over our slist.
 *
 * Returns 1 if iteration is over else returns 0.
 */
int slist_cursor_is_finished(slist_cursor_t *cursor)
{
    return cursor->node == NULL ? 1 : 0;
}

/*
 * slist_get_data_from_cursor() - Get data for the node currently pointed by the
 * cursor.
 */
void * slist_get_cursor_data(slist_cursor_t *cursor)
{
    return slist_get_node_data(cursor->node);
}

/*
 * End Cursor Implementation.
 */
