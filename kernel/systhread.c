#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int sys_thread_create(void)
{
  void *arg;
  typedef  void (*fcn)(void*);
 
  // char *buffer;//
  char *temp1, *temp2, *temp3;
  if(argptr(0, &temp1, sizeof(fcn)) < 0 )
    return -1;
  fcn t = (fcn) temp1;
  
  if(argptr(1, &temp2, sizeof(char*))< 0)
    return -1;
  arg = (int*) temp2;
  return thread_create(t, arg);

}
