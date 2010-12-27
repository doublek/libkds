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

int slist_insert(slist_t **slist, void *data)
{
    slist_node_t *new_node;
    new_node = malloc(sizeof(slist_node_t));

    if (new_node == NULL)
        return ENOMEM;

    /* Inserting the first element */
    if ((*slist)->head == NULL)
    {
        printf("Creating first element in the list with data %s\n", (char *)data);
        new_node->data = data;
        new_node->next = NULL;
        (*slist)->head = new_node;
        return 0;
    }

    printf("Inserting %s in the list\n", (char *)data);
    new_node->data = data;
    new_node->next = (*slist)->head;
    (*slist)->head = new_node;
    return 0;

}

/*
 * slist_remove() - Remove from head entry.
 *
 */
int slist_delete(slist_t **slist)
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
