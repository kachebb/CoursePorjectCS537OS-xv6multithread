#ifndef _THREAD_H_
#define _THREAD_H_


typedef struct __lock_t{
  uint locked;
}lock_t;

typedef struct __cond_t{
  uint cond = 1;
}cond_t;

#endif
