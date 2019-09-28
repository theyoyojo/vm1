#include "../../lil_test/src/lil_test.h"
#include "olist.h"
#include "types.h"

#define ALLOC_OR_FAIL(id, type) type * id = (type *)malloc(sizeof(type)) ;\
					    ASSERT(id)

/* TEST_SET(list_basic, */

/* 	TEST_CASE(two_objects_append, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */

/* 		int a2 = *(int *)olist_get(list,0) ; */
/* 		int b2 = *(int *)olist_get(list,1) ; */
/* 		ASSERT(a2 == 1) ; */
/* 		ASSERT(b2 == 2) ; */

/* 		olist_free(&list) ; */


/* 	); */

/* 	TEST_CASE(two_objects_pop, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */

/* 		int * b2 = (int *)olist_pop(list) ; */
/* 		ASSERT(olist_length(list) == 1) ; */
/* 		int * a2 = (int *)olist_pop(list) ; */
/* 		ASSERT(*a2 == 1) ; */
/* 		ASSERT(*b2 == 2) ; */
/* 		free(a), free(b) ; */

/* 		ASSERT(olist_empty(list)) ; */

/* 		olist_free(&list) ; */


/* 	); */

/* 	TEST_CASE(two_objects_del_first, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */

/* 		olist_del(list,0) ; */
/* 		int * a2 = (int *)olist_pop(list) ; */
/* 		ASSERT(*a2 == 2) ; */
/* 		free(b) ; */

/* 		olist_free(&list) ; */

/* 	); */

/* 	TEST_CASE(two_objects_del_all, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */

/* 		olist_del_all(list) ; */
/* 		ASSERT(olist_empty(list)) ; */

/* 		olist_free(&list) ; */

/* 	); */

/* 	TEST_CASE(init_empty, */
/* 		olist_t * list = olist_init() ; */
/* 		ASSERT(olist_empty(list)) ; */
/* 		olist_free(&list) ; */
/* 	) ; */
	
/* 	TEST_CASE(five_objects_pop_third, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */
/* 		ALLOC_OR_FAIL(c, int) ; */
/* 		ALLOC_OR_FAIL(d, int) ; */
/* 		ALLOC_OR_FAIL(e, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		*c = 3 ; */
/* 		*d = 4 ; */
/* 		*e = 5 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */
/* 		olist_append(list, (void *)c) ; */
/* 		olist_append(list, (void *)d) ; */
/* 		olist_append(list, (void *)e) ; */

/* 		ASSERT(olist_length(list) == 5) ; */

/* 		int * a2 = (int *)olist_pop_index(list, 2) ; */
/* 		ASSERT(*a2 == 3) ; */
/* 		free(a2) ; */

/* 		olist_del_all(list) ; */

/* 		olist_free(&list) ; */

/* 	); */

/* 	TEST_CASE(for_each_in_five, */
/* 		ALLOC_OR_FAIL(a, int) ; */
/* 		ALLOC_OR_FAIL(b, int) ; */
/* 		ALLOC_OR_FAIL(c, int) ; */
/* 		ALLOC_OR_FAIL(d, int) ; */
/* 		ALLOC_OR_FAIL(e, int) ; */

/* 		*a = 1 ; */
/* 		*b = 2 ; */
/* 		*c = 3 ; */
/* 		*d = 4 ; */
/* 		*e = 5 ; */
/* 		olist_t * list = olist_init() ; */

/* 		olist_append(list, (void *)a); */
/* 		olist_append(list, (void *)b) ; */
/* 		olist_append(list, (void *)c) ; */
/* 		olist_append(list, (void *)d) ; */
/* 		olist_append(list, (void *)e) ; */

/* 		ASSERT(olist_length(list) == 5) ; */

/* 		for(size_t i = 0; i < olist_length(list); ++i) { */
/* 			/1* printf("list[%lu] = %d\n", i, *(int *)olist_get(list, i)) ; *1/ */
/* 			ASSERT(*(int *)olist_get(list, i) == i + 1) ; */
/* 		} */

/* 		olist_del(list, 4) ; */
/* 		olist_del(list, olist_length(list) - 1) ; */

/* 		for(size_t i = 0; i < olist_length(list); ++i) { */
/* 			/1* printf("list[%lu] = %d\n", i, *(int *)olist_get(list, i)) ; *1/ */
/* 			ASSERT(*(int *)olist_get(list, i) == i + 1) ; */
/* 		} */
		

/* 		olist_del_all(list) ; */

/* 		olist_free(&list) ; */

/* 	); */

/* ); */

TEST_SET(simple_exprs,
		TEST_CASE(simple_number,
			num_t * x = C_num(4) ;
			ASSERT(x->value == 4) ;
			D_num(&x) ;
		) ;
		TEST_CASE(simple_bool,
			bool_t * x = C_bool(true);
			ASSERT(x->value == true) ;
			D_bool(&x) ;
		) ;
		
		TEST_CASE(simple_prim,
			prim_t * x = C_prim(">=");
			ASSERT(x->value == PRIM_GTEQ) ;
			ASSERT(x->value != PRIM_LT) ;
			D_prim(&x) ;
		) ;
		TEST_CASE(simple_if,
			bool_t * x = C_bool(true);
			num_t * y = C_num(4);
			prim_t * z = C_prim("+");

			if_t * a = C_if(x,y,z) ;

			D_if(&a) ;
		) ;
		TEST_CASE(number_in_list,
			olist_t * list = olist_init() ;
			num_t * x = C_num(4) ;
			olist_append(list, x) ;
			olist_free(&list) ;
		) ;
		TEST_CASE(simple_app,	
			bool_t * x = C_bool(true);
			num_t * y = C_num(4);
			prim_t * z = C_prim("+");
			app_t * a = C_app(3, x,y,z) ;

			D_app(&a) ;
		) ;
) ;


TEST_MAIN();