#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "slist.h"

void print_list_using_cursor(slist_t *slist)
{
    slist_cursor_t *cursor;

    cursor = slist_cursor_init(&slist);
    printf("Cursor Initialized\n");
    
    for(cursor=slist_cursor_init(&slist);
            !slist_cursor_is_finished(cursor);
            cursor=slist_cursor_next(cursor))
        printf("Data: %s\n", (char*)slist_get_cursor_data(cursor));

    /* Alternate more clear loop shown here as an example */
    /*while(!slist_cursor_is_finished(cursor))
    {
        printf("Data: %s\n", (char*)slist_get_cursor_data(cursor));
        cursor = slist_cursor_next(cursor);
    }*/

}

int compare_data(const void *data1, const void *data2)
{
    char *lhs = (char *)data1;
    char *rhs = (char *)data2;

    printf("Comparing LHS %s to RHS %s\n", lhs, rhs);
    return strcmp(lhs, rhs);
}

void * free_data(void *data)
{
    printf("%s: Called\n", __func__);
    return data;
}

int main(int argc, char* argv[])
{
    slist_t *slist;

    char *text_data[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

    char *data0, *data1, *data2, *data3 , *data4 , *data5 , *data6;

    slist_node_t *query_node;

    slist = slist_init();
    slist_set_compare_function(&slist, compare_data);
    slist_set_node_free_func(&slist, free_data);

    if(slist == NULL)
        printf("Error occured during init\n");

    if (slist->head == NULL)
        printf("Head is initialized to NULL\n");


    data0 = malloc(sizeof(text_data[0]));
    strncpy(data0, text_data[0], strlen(text_data[0]));
    slist_insert(&slist, (void *)data0);

    data1 = malloc(sizeof(text_data[1]));
    strncpy(data1, text_data[1], strlen(text_data[1]));
    slist_insert(&slist, (void *)data1);

    data2 = malloc(sizeof(text_data[2]));
    strncpy(data2, text_data[2], strlen(text_data[2]));
    slist_insert(&slist, (void *)data2);

    data3 = malloc(sizeof(text_data[3]));
    strncpy(data3, text_data[3], strlen(text_data[3]));
    slist_insert(&slist, (void *)data3);

    data5 = malloc(sizeof(text_data[5]));
    strncpy(data5, text_data[5], strlen(text_data[5]));
    slist_insert(&slist, (void *)data5);

    printf("Size of list: %d\n", slist_len(slist));

    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);

    query_node = slist_find_node(slist, "C");
    if(query_node)
        printf("Found data\n");
    else
        printf("Data not found\n");

    /*Insert After */
    printf("**************************\n");
    printf("Insert after...\n");
    data4 = malloc(sizeof(text_data[4]));
    strncpy(data4, text_data[4], strlen(text_data[4]));
    slist_insert_after(&slist, (void*)data5, (void *)data4);

    /* Full list */
    printf("**************************\n");
    printf("Full list\n");
    printf("Size of list: %d\n", slist_len(slist));
    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);

    /* Delete head */
    printf("**************************\n");
    printf("Delete\n");
    free(slist_delete(&slist));
    printf("Size of list: %d\n", slist_len(slist));
    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);

    /* Delete after */
    printf("**************************\n");
    printf("Delete after...\n");
    free(slist_delete_after(&slist, (void *)data2));
    printf("Size of list: %d\n", slist_len(slist));
    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);
    return 0;

}
