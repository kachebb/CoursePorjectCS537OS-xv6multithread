#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096


void test(){
  printf(1, "testing function has been called\n");
  // exit();
}



int
main(int argc, char **argv)
{
  int i = testing(); 
  printf(1, "value from tesing:%d\n",i);
  int j = join();
  printf(1, "value from join:%d\n",j);
  void (* foo)();
  foo = test;
  void * arg = NULL;
  void * stack = malloc(PGSIZE);
  int c = clone(foo, arg, stack );
  printf(1, "value from clone:%d\n", c);
  // exit();
  return 1;
}
