#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int
main(int argc, char *argv[]) //task2
{
    if(argc == 1){
        
        exit(1,"No policy value given.\n");
    }
    int res = set_policy((uint)atoi(argv[1]));
    if(res == 0){
        exit(0, "Successfully change policy value.\n");
    }

    exit(1,"Error, could not change policy value.\n");

}