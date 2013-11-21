/* clone and join syscalls */

#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE)
     stack = stack + (4096 - (uint)stack % PGSIZE);

   int arg = 42;
   int clone_pid = clone(worker, &arg, stack);
   assert(clone_pid > 0);
   printf(1," after clone pid: %d\n",clone_pid);
   void *join_stack;
   int join_pid = join(&join_stack);
   assert(join_pid == clone_pid);
   printf(1, "%p\n", stack);
   printf(1, "%p\n", join_stack);
   assert(stack == join_stack);
   printf(1,"global main:%d\n",global);
   assert(global == 2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   printf(1,"arg %d\n",arg);
   assert(arg == 42);
   printf(1,"global:%d\n",global);
   assert(global == 1);
   global++;
   exit();
}


/*

#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096

void tm(){
  int a = 3;
  printf(1,"%d",a);

}


void test(void *s){
  //char s = 's';
  printf(1, "testing function has been called CHAR %d\n",s);
  //exit();
  //  while(1);
}



int
main(int argc, char **argv)
{
  int i = testing(); 
  printf(1, "value from tesing:%d\n",i);
  void * st;
  int j = join(&st);
  printf(1, "value from join:%d\n",j);
  void (* foo)(void *);
  foo = &test;
  // char test = 'd';
  int test = 23;
  int * arg = &test;
  printf(1, "input char %d\n", *arg);
  void * stack = malloc(PGSIZE);
  int c = clone(foo, arg, stack);
  printf(1, "value from clone:%d\n", c);
  exit();
  //  return 1;
}
*/
