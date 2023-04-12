#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "user/user.h"
#include "kernel/cfs_stat.h"

void iterations(){
    for (int i = 0; i < 1000000; i++)
    {
        if(i % 100000 == 0 && i != 0)
            sleep(10);
    }
}

void statistics_print(){
    struct cfs_stat stats;
    get_cfs_stat(&stats);

    printf("Process ID:%d \nPriority:%d \nRuntime:%l \nSleeptime:%l \nRunnabletime:%l\n\n", getpid(), stats.priority,
                                                                            stats.runtime, stats.sleeptime,
                                                                            stats.retime);
}


int
main(int argc, char *argv[]) //task6, print order: p2 -> p1 -> pmain
{
    int p1, p2;

    if( (p1 = fork()) == 0){ 
        if( (p2 = fork()) == 0){ //child process two
            set_cfs_priority(0);
            iterations();
            statistics_print();
        }
        else{ //child process one, waits for process two to finish before printing statistics
            set_cfs_priority(1);
            iterations();
            wait(&p2,"");
            statistics_print();
        }
    }

    else{ //main process, waits for process one to finish before printing statistics
        set_cfs_priority(2);
        iterations();
        wait(&p1,"");
        statistics_print();
        printf("cfs done.\n");
    }

    exit(0, "");
}