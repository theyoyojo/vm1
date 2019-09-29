#include "../../lil_test/src/lil_test.h"
#include "olist.h"
#include "types.h"
#include "delta.h"

#define ALLOC_OR_FAIL(id, type) type * id = (type *)malloc(sizeof(type)) ;\
					    ASSERT(id)

TEST_SET(simple_exprs,
		TEST_CASE(simple_number,
			obj_t * x = C_num(4) ;
			ASSERT(((num_t *)x)->value == 4) ;
			D_num(&x) ;
		) ;
		TEST_CASE(simple_bool,
			obj_t * x = C_bool(true);
			ASSERT(((bool_t *)x)->value == true) ;
			D_bool(&x) ;
		) ;
		
		TEST_CASE(simple_prim,
			obj_t * x = C_prim(">=");
			ASSERT(((prim_t *)x)->value == PRIM_GTEQ) ;
			ASSERT(((prim_t *)x)->value != PRIM_LT) ;
			D_prim(&x) ;
		) ;
		TEST_CASE(simple_if,
			obj_t * x = C_bool(true);
			obj_t * y = C_num(4);
			obj_t * z = C_prim("+");

			obj_t * a = C_if(x,y,z) ;

			D_if(&a) ;
		) ;
		TEST_CASE(number_in_list,
			olist_t * list = olist_init() ;
			obj_t * x = C_num(4) ;
			olist_append(list, x) ;
			olist_free(&list) ;
		) ;
		TEST_CASE(simple_app,	
			obj_t * x = C_bool(true);
			obj_t * y = C_num(4);
			obj_t * z = C_prim("+");
			obj_t * a = C_app(3, x,y,z) ;

			D_app(&a) ;
		) ;
		TEST_CASE(app_list,
			obj_t * x = C_bool(true);
			obj_t * y = C_num(4);
			obj_t * z = C_prim("+");
			obj_t * a = C_app(3, x,y,z) ;

			obj_t * p = C_bool(true);
			obj_t * q = C_num(4);
			obj_t * r = C_prim("+");
			obj_t * b = C_app(3, p,q,r) ;

			olist_t * list = olist_init() ;
			olist_append(list, a) ;
			olist_append(list, b) ;

			olist_free(&list) ;
		) ;
		TEST_CASE(olist_pop_empty_is_null,
			olist_t * list = olist_init() ;
			ASSERT(!olist_pop(list)) ;
			olist_free(&list) ;
		) ;
) ;

TEST_SET(deltas,
	TEST_CASE(plus,
		obj_t * op = C_prim("+") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((num_t *)c)->value == 11) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(mult,
		obj_t * op = C_prim("*") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((num_t *)c)->value == 28) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(div,
		obj_t * op = C_prim("/") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((num_t *)c)->value == 4.0/7) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(div_by_zero_retnull,
		obj_t * op = C_prim("/") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(0) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(!c)
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(sub,
		obj_t * op = C_prim("-") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((num_t *)c)->value == -3) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;

	TEST_CASE(gt,
		obj_t * op = C_prim(">") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((bool_t*)c)->value == false) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;

	TEST_CASE(gteq,
		obj_t * op = C_prim(">=") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		assert(((bool_t*)c)->value == false) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(eq,
		obj_t * op = C_prim("=") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((bool_t*)c)->value == false) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(lt,
		obj_t * op = C_prim("<") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((bool_t*)c)->value == true) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
	TEST_CASE(lteq,
		obj_t * op = C_prim("<=") ;
		obj_t * a = C_num(4) ;
		obj_t * b = C_num(7) ;
		obj_t * app = C_app(3, op, a, b) ;
		obj_t * c = delta(app) ;
		ASSERT(((bool_t*)c)->value == true) ;
		c->head.D_obj(&c) ;
		app->head.D_obj(&app) ;
	) ;
) ;

TEST_SET(copy,
	TEST_CASE(copy_number,
		obj_t * x = C_num(4) ;
		obj_t * y = C_num_copy(x) ;
		ASSERT(((num_t *)y)->value == 4) ;
		D_obj(x)(&x) ;
		D_obj(y)(&y) ;
	) ;
	TEST_CASE(copy_bool,
		obj_t * x = C_bool(false);
		obj_t * y = C_bool_copy(x) ;
		ASSERT(((bool_t *)y)->value == false) ;
		D_obj(x)(&x) ;
		D_obj(y)(&y) ;
	) ;
	
	TEST_CASE(copy_prim,
		obj_t * x = C_prim(">=");
		obj_t * y = C_obj_copy(x) ;
		ASSERT(((prim_t *)y)->value == PRIM_GTEQ) ;
		ASSERT(((prim_t *)y)->value != PRIM_LT) ;
		D_obj(x)(&x) ;
		D_obj(y)(&y) ;
	) ;
	TEST_CASE(copy_if,
		obj_t * x = C_bool(true);
		obj_t * y = C_num(4);
		obj_t * z = C_prim("+");

		obj_t * a = C_if(x,y,z) ;
		obj_t * b = C_obj_copy(a) ;

		ASSERT(((num_t *)((if_t *)b)->expr_true)->value == 4) ;

		D_obj(a)(&a) ;
		D_obj(b)(&b) ;
	) ;
	TEST_CASE(copy_app,	
		obj_t * x = C_bool(true);
		obj_t * y = C_num(4);
		obj_t * z = C_prim("+");
		obj_t * a = C_app(3, x,y,z) ;
		obj_t * b = C_obj_copy(a) ;

		ASSERT(((num_t *)olist_get(((app_t *)b)->expr_list,1))->value == 4) ;

		D_obj(a)(&a) ;
		D_obj(b)(&b) ;
	) ;
) ;


TEST_MAIN();
