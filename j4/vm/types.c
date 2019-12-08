#include "types.h"
#include "stack.h"
#include <string.h>

obj_t * C_lam(obj_t * recname, olist_t * binding, obj_t * expr) {
	assert(binding), assert(expr) ;
	ALLOC_OR_RETNULL(new, lam_t) ;	
	*new = LAM_INIT(recname, binding, expr) ;
	new->refcnt = 1 ;
	return (obj_t *)new ;
}

obj_t * C_lam_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, lam_t) ;	
	*new = LAM_INIT(C_obj_copy(((lam_t *)old)->recname),
			olist_init_copy(((lam_t *)old)->binding),
			C_obj_copy(((lam_t *)old)->expr)) ;
	new->refcnt = 1 ;
	return (obj_t *)new ;
}

obj_t * lam_inc_ref(obj_t * lam) {
	assert(lam) ;
	++((lam_t *)lam)->refcnt ;
	return lam ;
}

void lam_dec_ref(obj_t ** lam_ptr) {
	assert(lam_ptr) ;
	assert(obj_typeof(*lam_ptr) == T_LAM) ;
	if (--(*(lam_t **)lam_ptr)->refcnt <= 0) {
		D_lam(lam_ptr) ;
	}
}

olist_t * lam_get_binding(obj_t * lam) {
	assert(obj_typeof(lam) == T_LAM) ;
	return ((lam_t *)lam)->binding ;
}

obj_t * lam_get_expr(obj_t * lam) {
	assert(obj_typeof(lam) == T_LAM) ;
	return ((lam_t *)lam)->expr;
}

obj_t * lam_get_recname(obj_t * lam) {
	assert(obj_typeof(lam) == T_LAM) ;
	return ((lam_t *)lam)->recname ;
}
	
void D_lam(obj_t ** lam_ptr) {
	assert(lam_ptr) ;
	assert(*lam_ptr) ;
	D_OBJ(((lam_t *)*lam_ptr)->recname) ;
	olist_free(&((lam_t *)*lam_ptr)->binding) ;
	D_OBJ(((lam_t *)*lam_ptr)->expr) ;
	free(*lam_ptr) ;
	*lam_ptr = NULL ;
}

obj_t * C_ident(char * name) {
	assert(name) ;
	ALLOC_OR_RETNULL(new, ident_t) ;
	new->head = HEADER_INIT(T_IDENT, ident_t, ident_dec_ref, ident_inc_ref) ;
	new->length = sizeof(name) ;
	if (!(new->value = (char *)malloc(new->length * sizeof(char)))) {
		return NULL ;
	}
	strncpy(new->value, name, new->length) ;
	new->refcnt = 1 ;
	return (obj_t *) new ;
}

obj_t * ident_inc_ref(obj_t * ident) {
	assert(ident) ;
	++((ident_t *)ident)->refcnt ;
	return ident ;
}

void ident_dec_ref(obj_t ** ident_ptr) {
	assert(ident_ptr) ;
	assert(obj_typeof(*ident_ptr) == T_IDENT) ;
	if (--(*(ident_t **)ident_ptr)->refcnt <= 0) {
		D_ident(ident_ptr) ;
	}
}

void D_ident(obj_t ** ident_ptr) {
	assert(ident_ptr) ;
	assert(*ident_ptr) ;
	free(((ident_t *)*ident_ptr)->value) ;
	free(*ident_ptr) ;
	*ident_ptr = NULL ;
}

char * ident_get_name(obj_t * ident) {
	assert(obj_typeof(ident) == T_IDENT) ;
	return ((ident_t *)ident)->value ;
}

int ident_cmp(obj_t * first, obj_t * second) {
	return strcmp(ident_get_name(first), ident_get_name(second)) ;
}

obj_t * C_ptr(void * addr, size_t size) {
	ALLOC_OR_RETNULL(new, ptr_t) ;
	*new = PTR_INIT(addr, size) ;
	return (obj_t *)new ;
}

obj_t * C_ptr_copy(obj_t * old) {
	ALLOC_OR_RETNULL(new, ptr_t) ;
	*new = PTR_INIT(ptr_addr(old), ptr_size(old)) ;
	return (obj_t *)new ;
}

/* gotta take out the trash (collect the garbage) */
void D_ptr(obj_t ** ptr_ptr) {
	assert(ptr_ptr) ;
	assert(*ptr_ptr) ;
	free(*ptr_ptr) ;
	*ptr_ptr = NULL ;
}

void * ptr_addr(obj_t * ptr) {
	assert(obj_typeof(ptr) == T_PTR) ;
	return ((ptr_t *)ptr)->addr ;
}

size_t ptr_size(obj_t * ptr) {
	assert(obj_typeof(ptr) == T_PTR) ;
	return ((ptr_t *)ptr)->size ;
}


obj_t * C_abort(obj_t * expr) {
	ALLOC_OR_RETNULL(new, abort_t) ;
	*new = ABORT_INIT(expr) ;
	return (obj_t *)new ;
}

obj_t * C_abort_copy(obj_t * old) {
	ALLOC_OR_RETNULL(new, abort_t) ;
	*new = ABORT_INIT(C_obj_copy(abort_expr(old))) ;
	return (obj_t *)new ;
}
void D_abort(obj_t ** abort_ptr) {
	assert(abort_ptr) ;
	assert(*abort_ptr) ;
	D_OBJ(((abort_t *)*abort_ptr)->expr) ;
	free(*abort_ptr) ;
	*abort_ptr = NULL ;
}

obj_t * abort_expr(obj_t * abort) {
	assert(obj_typeof(abort) == T_ABORT) ;
	return ((abort_t *)abort)->expr ;
}

obj_t * C_app(size_t count, ...) {
	ALLOC_OR_RETNULL(new, app_t) ;

	va_list arglist ;
	
	new->head = HEADER_INIT(T_APP, app_t,  D_app, C_app_copy) ;
	new->expr_list = olist_init() ;
	va_start(arglist, count) ;
	for (size_t i = 0; i < count; ++i) {
		olist_append(&new->expr_list, va_arg(arglist, obj_t *)) ;
	}
	va_end(arglist) ;

	return (obj_t *)new ;
}

/* construct an app from an expr list */
obj_t * C_app_list(olist_t * expr_list) {
	ALLOC_OR_RETNULL(new, app_t) ;
	new->head = HEADER_INIT(T_APP, app_t, D_app, C_app_copy) ;
	new->expr_list = expr_list ;
	return (obj_t *)new ;
}

obj_t * C_app_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, app_t) ;

	new->head = HEADER_INIT(T_APP, app_t, D_app, C_app_copy) ;
	
	new->expr_list = olist_init_copy(((app_t *)old)->expr_list) ;

	return (obj_t *)new ;
}

void D_app(obj_t ** app_ptr) {
	assert(app_ptr) ;
	olist_free(&(*(app_t **)app_ptr)->expr_list) ;
	free(*app_ptr) ;
	*app_ptr = NULL ;
}

obj_t * app_copy_first(obj_t * app) {
	assert(obj_typeof(app) == T_APP) ;
	return C_obj_copy(olist_get(((app_t *)app)->expr_list, 0)) ;
}

olist_t * app_get_expr_list(obj_t * app) {
	assert(obj_typeof(app) == T_APP) ;
	return ((app_t *)app)->expr_list ;
}


obj_t * C_if(obj_t * e_pred, obj_t * e_true, obj_t * e_false) {
	ALLOC_OR_RETNULL(new, if_t) ;
	*new = IF_INIT(e_pred, e_true, e_false) ;
	return (obj_t *)new ;
}

obj_t * C_if_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, if_t) ;
	*new = IF_INIT(
		C_obj_copy(((if_t *)old)->expr_pred),
		C_obj_copy(((if_t *)old)->expr_true),
		C_obj_copy(((if_t *)old)->expr_false)) ;
	return (obj_t *)new ;
}

void D_if(obj_t ** if_ptr) {
	if_t * ifexpr = *(if_t **)if_ptr ;
	D_OBJ(ifexpr->expr_pred) ;
	D_OBJ(ifexpr->expr_true) ;
	D_OBJ(ifexpr->expr_false) ;
	free(ifexpr) ;
	*if_ptr = NULL ;
}

obj_t * if_get_pred(obj_t * ifexpr) {
	assert(obj_typeof(ifexpr) == T_IF) ;
	return ((if_t *)ifexpr)->expr_pred ;
}

obj_t * if_get_true(obj_t * ifexpr) {
	assert(obj_typeof(ifexpr) == T_IF) ;
	return ((if_t *)ifexpr)->expr_true ;
}

obj_t * if_get_false(obj_t * ifexpr) {
	assert(obj_typeof(ifexpr) == T_IF) ;
	return ((if_t *)ifexpr)->expr_false ;
}

obj_t * if_copy_pred(obj_t * ifexpr) {
	assert(obj_typeof(ifexpr) == T_IF) ;
	return C_obj_copy(((if_t *)ifexpr)->expr_pred) ;
}

obj_t * C_pair(obj_t * first, obj_t * second) {
	ALLOC_OR_RETNULL(new, pair_t) ;
	*new = PAIR_INIT(first, second) ;
	return (obj_t *)new ;
}

obj_t * C_pair_copy(obj_t * old) {
	ALLOC_OR_RETNULL(new, pair_t) ;
	*new = PAIR_INIT(C_obj_copy(pair_first(old)), C_obj_copy(pair_second(old))) ;
	return (obj_t *)new ;
}

void D_pair(obj_t ** pair_ptr) {
	assert(pair_ptr) ;
	assert(*pair_ptr) ;
	D_OBJ(((pair_t *)*pair_ptr)->first) ;
	D_OBJ(((pair_t *)*pair_ptr)->second) ;
	free(*pair_ptr) ;
	*pair_ptr = NULL ;
}

obj_t * pair_first(obj_t * pair) {
	assert(obj_typeof(pair) == T_PAIR) ;
	return ((pair_t *)pair)->first ;
}

obj_t * pair_second(obj_t * pair) {
	assert(obj_typeof(pair) == T_PAIR) ;
	return ((pair_t *)pair)->second ;
}

void pair_overwrite_first(obj_t * pair, obj_t * new) {
	assert(obj_typeof(pair) == T_PAIR) ;
	((pair_t *)pair)->first = new ;

}
void pair_overwrite_second(obj_t * pair, obj_t * new) {
	assert(obj_typeof(pair) == T_PAIR) ;
	((pair_t *)pair)->second = new ;
}

char * prim_syms[] = {
	[PRIM_INVALID]	= "[?]",
	[PRIM_PLUS]	= "+",
	[PRIM_MULT]	= "*",
	[PRIM_DIV]	= "/",
	[PRIM_SUB]	= "-",
	[PRIM_LTEQ]	= "<=",
	[PRIM_LT]	= "<",
	[PRIM_EQ]	= "=",
	[PRIM_GT]	= ">",
	[PRIM_GTEQ]	= ">=",
	[PRIM_PAIR]	= "pair",
	[PRIM_FST]	= "fst",
	[PRIM_SND]	= "snd",
	[PRIM_BOX]	= "box",
	[PRIM_UNBOX]	= "unbox",
	[PRIM_SETBOX]	= "set-box!",
	[PRIM_PRINT]	= "print",
};

#define PRIM_SYMS_LENGTH sizeof(prim_syms)/8

prim_val_t prim_stov(char * prim) {
	size_t i ;
	for (i = 0; i < PRIM_SYMS_LENGTH; ++i) {
		if (strcmp(prim, prim_syms[i]) == 0) {
			return (prim_val_t)i ;
		}
	}
	return PRIM_INVALID ;
}

char * prim_vtos(prim_val_t prim_val) {
	return prim_syms[prim_val] ;
}

obj_t * C_prim(char * prim) {
	ALLOC_OR_RETNULL(new, prim_t) ;
	*new = PRIM_INIT(prim) ;
	return (obj_t *)new ;
}

obj_t * C_prim_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, prim_t) ;
	*new = PRIM_INIT(prim_vtos(((prim_t *)old)->value)) ;
	return (obj_t *)new ;
}

prim_val_t prim_get_val(obj_t * prim) {
	assert(obj_typeof(prim) == T_PRIM) ;
	return ((prim_t *)prim)->value ;
}

void D_prim(obj_t ** prim_ptr) {
	free(*prim_ptr) ;
	*prim_ptr = NULL ;
}

obj_t * C_bool(bool value) {
	ALLOC_OR_RETNULL(new, bool_t) ;
	*new = BOOL_INIT(value) ;
	return (obj_t *)new ;
}

void D_bool(obj_t ** bool_ptr) {
	free(*bool_ptr) ;
	*bool_ptr = NULL ;
}

obj_t * C_bool_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, bool_t) ;
	*new = BOOL_INIT(((bool_t *)old)->value);
	return (obj_t *)new ;
}

obj_t * C_num(double value) {
	ALLOC_OR_RETNULL(new, num_t) ;
	*new = NUM_INIT(value) ;
	return (obj_t *)new;
}

obj_t * C_num_copy(obj_t * old) {
	assert(old) ;
	ALLOC_OR_RETNULL(new, num_t) ;
	*new = NUM_INIT(((num_t *)old)->value);
	return (obj_t *)new ;
}

void D_num(obj_t ** num_ptr) {
	free(*num_ptr) ;
	*num_ptr = NULL ;
}

obj_t * C_str(char * str) {
	ALLOC_OR_RETNULL(new, str_t) ;
	new->head = HEADER_INIT(T_STR, str_t, D_str, C_str_copy) ;
	new->size = strlen(str) ;
	if (!(new->value = (char *)malloc(new->size + 1))) {
		return NULL ;
	}
	strncpy(new->value, str, new->size) ;
	new->value[new->size] = '\0' ;
	return (obj_t *)new ;
}

obj_t * C_str_copy(obj_t * old) {
	ALLOC_OR_RETNULL(new, str_t) ;
	new->head = HEADER_INIT(T_STR, str_t, D_str, C_str_copy) ;
	new->size = str_size(old) ;
	if (!(new->value = (char *)malloc(new->size + 1))) {
		return NULL ;
	}
	strncpy(new->value, str_get(old), new->size) ;
	new->value[new->size] = '\0' ;
	return (obj_t *)new ;

}
void D_str(obj_t ** str_ptr) {
	assert(str_ptr) ;
	assert(*str_ptr) ;
	free(((str_t *)*str_ptr)->value) ;
	free(*str_ptr) ;
	*str_ptr = NULL ;
}

char * str_get(obj_t * str) {
	assert(obj_typeof(str) == T_STR) ;
	return ((str_t *)str)->value ;
}

size_t str_size(obj_t *str) {
	assert(obj_typeof(str) == T_STR) ;
	return ((str_t *)str)->size ;
}

static int _unit_refcnt = 0 ;
static obj_t * _unit_ptr = NULL ;

obj_t * _unit_inc(void) {
	if (_unit_refcnt <= 0) {
		if (!(_unit_ptr = (obj_t *)malloc(sizeof(obj_t)))) {
			return NULL ;
		}

		*_unit_ptr = (obj_t) {
			.head = HEADER_INIT(T_UNIT, obj_t, D_unit, C_unit_copy)
		} ;
		_unit_refcnt = 1 ;
	} else {
		++_unit_refcnt ;
	}

	return _unit_ptr ;
}

void _unit_dec(void) {
	if (--_unit_refcnt <= 0) {
		free(_unit_ptr) ;
		_unit_ptr = NULL ;
	}
}

obj_t * C_unit() {
	return _unit_inc() ;
}

obj_t * C_unit_copy(obj_t * old) {
	(void)old ;
	return _unit_inc() ;
}

void D_unit(obj_t ** unit_ptr) {
	(void)unit_ptr ;
	_unit_dec() ;
}


void value_print(obj_t * value) {
	assert(obj_isvalue(value)) ;

	switch (obj_typeof(value)) {
	case T_NUM:
		printf("%g", ((num_t *)value)->value) ;
		break ;
	case T_BOOL:
		printf("%s", ((bool_t *)value)->value ? "True" : "False") ;
		break ;
	case T_PRIM:
		printf("%s", prim_vtos(((prim_t *)value)->value)) ;
		break ;
	case T_LAM:
		printf("LAM[$(") ;
		for (size_t i = 0; i < olist_length(lam_get_binding(value)); ++i) { expr_print(olist_get(lam_get_binding(value),i)) ;
			if (i != olist_length(lam_get_binding(value)) - 1) {
				printf(", ") ;
			}
		}
		printf(") ") ;
		expr_print(lam_get_expr(value)) ;
		printf("]") ;
		break ;
	case T_CLO:
		printf("CLO{$(") ;
		for (size_t i = 0; i < olist_length(lam_get_binding(clo_get_lam(value))); ++i) {
			expr_print(olist_get(lam_get_binding(clo_get_lam(value)),i)) ;
			if (i != olist_length(lam_get_binding(clo_get_lam(value))) - 1) {
				printf(", ") ;
			}
		}
		printf(") ") ;
		expr_print(lam_get_expr(clo_get_lam(value))) ;
		printf("}") ;
		break ;
	case T_PAIR:
		printf("<") ;
		expr_print(pair_first(value)) ;
		printf(", ") ;
		expr_print(pair_second(value)) ;
		printf(">") ;
		break ;
	case T_UNIT:
		printf("{#UNIT#}") ;
		break ;
	case T_PTR:
		printf("PTR/%zu[%p]", ptr_size(value), ptr_addr(value)) ;
		break ;
	case T_STR:
		printf("\"%s\"", str_get(value)) ;
		break ;
	default:
		printf("SOMETHING WENT terribly WRONG IN value_print()") ;
	}
}
void expr_print(obj_t * expr) {
	if (obj_isvalue(expr)) {
		value_print(expr) ;
		return ;
	}
	switch (obj_typeof(expr)) {
	case T_APP:
		printf("App[") ;
		for (size_t i = 0; i < olist_length(app_get_expr_list(expr)); ++i) {
			expr_print(olist_get(app_get_expr_list(expr), i)) ;
			putchar(' ') ;
		}
		printf("]") ;
		break ;
	case T_IF:
		printf("If[") ;
		expr_print(if_get_pred(expr)) ;
		putchar(' ') ;
		expr_print(if_get_true(expr)) ;
		putchar(' ') ;
		expr_print(if_get_false(expr)) ;
		printf("]") ;
		break ;
	case T_IDENT:
		printf("%s", ((ident_t *)expr)->value) ;
		break ;
	case T_ABORT:
		printf("ABORT[") ;
		expr_print(abort_expr(expr)) ;
		printf("]") ;
		break ;
	default:
		printf("SOMETHING WENT terribly WRONG IN expr_print()") ;
	}
}
