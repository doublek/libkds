#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "slist.h"

void print_list(slist_t *slist)
{
    slist_node_t *current;
    char *data_to_print;
    int *int_data_to_print;
    int count = 0;
    
    printf("Printing List:\n");
    current = slist->head;
    while (current != NULL)
    {
        if (count != 0)
        {
            data_to_print = (char *)current->data;
            printf("S %s\n", (char *)data_to_print);
        }
        else
        {
            int_data_to_print = (int *)current->data;
            printf("N %d\n", *int_data_to_print);

        }
        current = current->next;
        ++count;
    }

}

int main(int argc, char* argv[])
{
    slist_t *slist;

    int num_data[] = {1, 2, 3, 4};
    char *text_data[5] = {"A", "B", "C", "D", "E"};

    char *data0, *data1, *data2;
    int *numeric_test_data;

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

    numeric_test_data = malloc(sizeof(num_data[0]));
    *numeric_test_data = num_data[0];
    slist_insert(&slist, (void *)numeric_test_data);

    print_list(slist);
    slist_delete(&slist);
    print_list(slist);


    return 0;

}
