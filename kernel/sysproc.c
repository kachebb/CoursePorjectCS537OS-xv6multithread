#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//kaichen
int sys_testing()
{
  return testing();
}

int sys_clone(){
 
  int *stack;
  int *arg;
  typedef  void (*fcn)(void*);
  //  int *fcn;
 
  // char *buffer;//
  char *temp1, *temp2, *temp3;
  if(argptr(0, &temp1, sizeof(fcn)) < 0 )
    return -1;
  fcn t = (fcn) temp1;
  /*
  // memcpy(temp, buffer)
  t = (fcn)buffer;
  arg = (void *)(buffer + 4);
  stack = (void *)(buffer + 5);
  */
  
  if(argptr(1, &temp2, sizeof(char*))< 0)
    return -1;
  arg = (int*) temp2;
  // arg = temp1 + sizeof(fcn);
  if(argptr(2, &temp3, sizeof(char*))< 0)
    return -1;
  stack = (int*)temp3;
  // cprintf("1:%s,\n2:%s,\n3:%s,\n", *temp1, *temp2,*temp3);
  int ret = clone( t, arg, stack);
  return ret;
}

int sys_join(){
  char *temp;
  if(argptr(0, &temp, sizeof(char*))< 0)
    return -1;
  
  /*
  int i;
  int **st;
  if(argint(0, &i)<0)
    return -1;
  st = (int **)i;
  */
  return join((void **) temp);
}

int sys_t_sleep(void){
  acquire(&tickslock);
 
  sleep(&ticks, &tickslock);

  release(&tickslock);
  return 1;
}

int sys_t_wakeup(void){
  t_wakeup(&ticks);
  return 1;
}
