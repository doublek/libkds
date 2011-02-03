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

int main(int argc, char* argv[])
{
    slist_t *slist;

    char *text_data[5] = {"A", "B", "C", "D", "E"};

    char *data0, *data1, *data2, *data3;

    slist = slist_init();

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

    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);
    slist_delete(&slist);
    printf("Printing using cursor...\n");
    print_list_using_cursor(slist);


    return 0;

}
