#ifndef MEM_H
#define MEM_H

#include "types.h"

int mem_system_init(void) ;

obj_t * mem_alloc_init(obj_t * obj) ;

obj_t * mem_deref(obj_t * ptr) ;

obj_t * mem_set(obj_t * ptr, obj_t * newval) ;

int mem_gc(void) ;

int mem_system_free(void) ;

#endif /* MEM_H */