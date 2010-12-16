#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "slist.h"

int main(int argc, char* argv[])
{
    struct slist_t *slist;
    slist = slist_init();

    if(slist == NULL)
        printf("Error occured during init\n");

    if (slist->head == NULL)
        printf("Head is initialized to NULL\n");

    slist_insert(&slist, (void *)"A");
    slist_insert(&slist, (void *)"B");
    slist_insert(&slist, (void *)"C");
    slist_insert(&slist, (void *)"D");
    slist_insert(&slist, (void *)"E");
    slist_insert(&slist, (void *)"F");
    slist_insert(&slist, (void *)"G");
    slist_insert(&slist, (void *)"H");
    slist_insert(&slist, (void *)"I");
    slist_insert(&slist, (void *)"J");
    slist_insert(&slist, (void *)"K");
    slist_insert(&slist, (void *)"L");
    slist_insert(&slist, (void *)"M");
    slist_insert(&slist, (void *)"N");
    slist_insert(&slist, (void *)"O");
    slist_insert(&slist, (void *)"P");
    slist_insert(&slist, (void *)"Q");
    slist_insert(&slist, (void *)"R");
    slist_insert(&slist, (void *)"S");
    slist_insert(&slist, (void *)"T");
    slist_insert(&slist, (void *)"U");
    slist_insert(&slist, (void *)"V");
    slist_insert(&slist, (void *)"W");
    slist_insert(&slist, (void *)"X");
    slist_insert(&slist, (void *)"Y");
    slist_insert(&slist, (void *)1);
    slist_insert(&slist, (void *)"Z");

    print_list(slist);
    slist_delete(&slist);
    print_list(slist);


    return 0;

}
