#ifndef MK_ARRAY_H
#define MK_ARRAY_H

#include "cal_chr.h"
#include "cal.h"

void mk_array_fact(void);
int mk_array_num_cc(void);

int mk_array_ord_cc(void);
int mk_array_split(void);

//make array as character of representation
int mk_array_char(void);
int mk_array_sgn(void);
int mk_array_fix(void);

//
int mk_array_dim_sub(int m);
int mk_array_dim(void);
int re_array_dim(void);
int mk_array_col_range(void);
void mk_array_search_range(void);


void MALLOC_ALL(void);
void FREE_ALL(void);
void mk_array_ALL(void);


#endif
