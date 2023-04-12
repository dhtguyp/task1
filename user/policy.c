#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int
main(int argc, char *argv[]) //task2
{
    if(argc == 1){
        
        printf("No policy value given.\n");
        exit(1);
    }
    int res = set_policy((uint)atoi(argv[1]));
    if(res == 0){
        printf("Successfully change policy value.\n");
        exit(0);
    }

    printf("Error, could not change policy value.\n");
    exit(1);
}