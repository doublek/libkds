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
 * Create a new slist-node. To create a empty node just call this
 * function with NULL data.  * On success returns a newly created 
 * node else returns NULL.
 *
 */
slist_node_t * slist_create_node(void *data)
{
    slist_node_t* node;

    node = (slist_node_t *)malloc(sizeof(slist_node_t));

    if (node == NULL)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

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
    slist->size = 0;

    return slist;
}

/*
 * slist_len() - Get the number of nodes in the slist.
 *
 */
int slist_len(slist_t *slist)
{
    if (slist == NULL)
        return EINVAL;

    return slist->size;

}

/*
 * slist_set_compare_function() - Register a comparison function.
 *
 * Used to register a user defined comparison function that will be used for
 * comparison operations on slist's data. 
 * The registered function MUST exhibit the following behavior:
 *  1. Return 0 for equal data.
 *  2. Return -1 for LHS less than RHS.
 *  3. Return 1 for LHS greater than RHS.
 *  4. Any other return value will be considered as a failure.
 *
 */
void slist_set_compare_function(slist_t **slist,
                                slist_compare_func_t *compare_func)
{
    printf("Set Compare Function successfully\n");
    (*slist)->slist_data_compare = compare_func;
}

/*
 * slist_insert_first_node() - Insert first node into a slist.
 *
 */
int slist_insert_first_node(slist_t **slist, void *data)
{
    slist_node_t *new_node = slist_create_node(data);

    if (new_node == NULL)
        return ENOMEM;

    printf("Creating first element in the list with data %s\n",
            (char *)data);

    /* 
     * slist_create_node already did the necessary work of creating
     * a node for us. All we need to do at this point is to point head
     * at the right plae.
     */
    (*slist)->head = new_node;
    (*slist)->size = 1;
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
    slist_node_t *new_node = slist_create_node(data);

    if (new_node == NULL)
        return ENOMEM;

    /* Inserting the first element */
    if ((*slist)->head == NULL)
    {
        return slist_insert_first_node(slist, data);
    }

    printf("Inserting %s in the list\n", (char *)data);
    /*
     * Node creating already taken care of by slist_create_node().
     * We just update the next pointer here.
     */
    new_node->next = (*slist)->head;
    (*slist)->head = new_node;
    (*slist)->size++;
    return 0;

}

/*
 * slist_insert_after() - Insert new node after data.
 *
 * Inserts a new node in the slist after the specified data.
 * This function depends on the existence of a slist_compare_data function
 * provided when creating a slist i.e, slist_find_node() should be able to
 * find the node.
 *
 */
int slist_insert_after(slist_t **slist, void *existing_data, void *new_data)
{

    slist_node_t *new_node;
    slist_node_t *current_node;
    slist_cursor_t *cursor;

    new_node = slist_create_node(new_data);
    if (new_node == NULL)
        return ENOMEM;

    current_node = slist_find_node(*slist, existing_data);

    if (current_node == NULL)
        return -1; /* Data not found */

    new_node->next = current_node->next;
    current_node->next = new_node;

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
    (*slist)->size--;

    /* TODO Add a user-defined funtion pointer */
    free(node_to_delete);
    return 0;
    
}

/*
 * slist_get_node_data() - Get the data of the current node
 *
 * Returns the data that is stored in node. Returns NULL on error.
 *
 */
void * slist_get_node_data(slist_node_t *node)
{
    if (node ==NULL)
        return NULL;

    return node->data;
}

/*
 * slist_find_node() - Find a node in the given slist.
 *
 * Return original node if the node is found else returns NULL.
 * The data contained in the node can be accessed by calling
 * slist_get_node_data().
 */
slist_node_t * slist_find_node(slist_t *slist, void *data)
{
    slist_node_t *node;
    slist_cursor_t *cursor;

    node = slist_create_node(data);

    if (node == NULL)
        return NULL;

    for(cursor=slist_cursor_init(&slist); !slist_cursor_is_finished(cursor);
            cursor=slist_cursor_next(cursor))
    {
        if((slist->slist_data_compare)(node->data, slist_get_cursor_data(cursor)) == 0)
        {
            free(node);
            return cursor->node;
        }
    }

    /* Node not found*/
    return NULL;
}


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
 * slist_cursor_next() - Advance cursor to next slist element.
 *
 * Returns a cursor to the next slist element.
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
 *
 * Returns the data that is stored in cursor. Returns NULL on error.
 */
void * slist_get_cursor_data(slist_cursor_t *cursor)
{
    return slist_get_node_data(cursor->node);
}

/*
 * End Cursor Implementation.
 */
