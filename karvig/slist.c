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
