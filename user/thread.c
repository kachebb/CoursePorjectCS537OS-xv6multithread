#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "thread.h"

int thread_create(void (*start_routine)(void*) , void *arg) {
  int ret;
  void * stack = malloc(4096);
  ret = clone(start_routine, arg, stack);
  return ret;
}
int thread_join() {
  int ret;
  void *join_stack;
  ret = join(&join_stack);
  free(join_stack);
  return ret;
}


void lock_init(lock_t *lk){
  lk->locked = 0;
}

void lock_acquire(lock_t * lk){
  while(xchg(&lk->locked, 1) == 1)
    ;
}

void lock_release(lock_t *lk){
  xchg(&lk->locked, 0);
}

void cv_wait(cond_t *cv, lock_t *lk){ 
  while(xchg(&cv->cond,0) == 0){
    printf(1, "in cv_wait goling to sleep\n");
     lock_release(lk);
     t_sleep();
  }
  printf(1,"in cv after sleep\n");
  lock_acquire(lk);
}

void cv_signal(cond_t *cv){
  t_wakeup();
  xchg(&cv->cond, 1);
}
