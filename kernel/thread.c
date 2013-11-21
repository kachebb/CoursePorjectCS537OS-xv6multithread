#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"


int thread_create(void (*start_routine)(void*) , void *arg) {
  
  int ret;
  void * stack = malloc(PGSIZE);
  ret = clone(start_routine, arg, stack);
  return ret;
}
