#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//Added for task2
int
main(int argc, char *argv[]){ 
    int memory;
    memory = memsize();
    printf("at the start the process hold %d bytes.\n", memory);

    int * ptr = malloc(20000);
    memory = memsize();
    printf("after malloc the process hold %d bytes.\n", memory);

    free(ptr);
    memory = memsize();
    printf("after free the process hold %d bytes.\n", memory);
    exit(0,"");
}