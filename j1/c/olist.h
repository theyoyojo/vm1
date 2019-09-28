#ifndef OLIST_H
#define OLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _obj obj_t ;

typedef struct _olist_node {
	obj_t * obj ;
	struct _olist_node * next ;
} olist_node_t ;

#define OLIST_NODE_INIT (olist_node_t) { \
			.obj = NULL, \
			.next = NULL }

typedef struct _olist {
	olist_node_t * head ;
	size_t length_cache ;
	bool cache_valid ;
} olist_t ;

#define OLIST_INIT (olist_t) { \
			.head = NULL, \
			.length_cache = 0, \
			/* empty list has known zero length, we can cache */ \
			.cache_valid = 1 }


/* Can fail */
olist_t * olist_init(void) ;

bool olist_empty(olist_t * list) ;

/* Can fail */
bool olist_append(olist_t * list, obj_t * new) ;

/* Can fail */
bool olist_insert(olist_t * list, obj_t * new, size_t index) ;

obj_t * olist_pop_index(olist_t * list, size_t index) ;

/* pop end */
obj_t * olist_pop(olist_t * list) ;

void olist_del(olist_t * list, size_t index) ; 

void olist_del_all(olist_t * list) ;

obj_t * olist_get(olist_t * list, size_t index) ;

size_t olist_length(olist_t * list) ;

void olist_free(olist_t ** list_ptr) ;

#endif /* OLIST_H */