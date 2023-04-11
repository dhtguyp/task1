#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "cfs_stat.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 
sys_memsize(void) //task2
{
  return myproc()->sz;

}

uint64
sys_set_ps_priority(void) //task5
{
  int n;
  argint(0, &n);
  if(n < 0 || n >= 11) // invalid ps priority value
    return -1;
  
  myproc()->ps_priority = n;
  return 0;
}

uint64
sys_set_cfs_priority(void) //task6
{
  int n;
  argint(0, &n);
  if(n < 0 || n >= 3) // invalid cfs priority value
    return -1;
  
  myproc()->cfs_priority = n;
  return 0;

}
uint64
sys_get_cfs_stat(void){
  struct proc * p = myproc();
  uint64 addr;
  argaddr(0, &addr);
  return copyout(p->pagetable, addr, (char *)&p->cfs_priority, (uint64)sizeof(struct cfs_stat));
}
