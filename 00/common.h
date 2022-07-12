#ifndef COMMON_H
#define COMMON_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<math.h>

#define n 4



#if n <= 8
#	define n_prime 8
#	define TERMINAL 22
#	define cycle_shape_f "cycle_shape_8.txt"
#	define split_fmt "%3d"
#	define SPLIT_SIZE 4
#elif n <= 16
#	define n_prime 16
#	define TERMINAL 231
#	define cycle_shape_f "cycle_shape_16.txt"
#	define split_fmt "%4d"
#	define SPLIT_SIZE 5
#elif n <= 32
#	define n_prime 32
#	define TERMINAL 8349
#	define cycle_shape_f "cycle_shape_32.txt"
#	define split_fmt "%5d"
#	define SPLIT_SIZE 6
#elif n <= 64
#	define n_prime 64
#	define TERMINAL 1741630
#	define cycle_shape_f "cycle_shape_64.txt"
#	define split_fmt "%8d"
#	define SPLIT_SIZE 9
#endif

#define POS_SIGN	(3*n_prime/2)
#define POS_FIX		(POS_SIGN + 3)
#define POS_SPLIT	(POS_SIGN + 6)
#define LINE_SIZE_CS	(POS_SPLIT + SPLIT_SIZE)

#define n1 (n_prime/2)
#define n2 (n_prime/2 + 2)

#define num_cc_f 	"num_cc.txt"
#define num_cc_fmt 	"%7d\n"
#define ord_cc_f 	"ord_cc.txt"
#define dim_f 		"dim.txt"


#define MALLOC_ARRAY(number, type) \
	((type *)malloc((number) * sizeof(type)))
#define PP_MALLOC(pp, number, type) \
	do{\
	pp = MALLOC_ARRAY(number, type *);\
	for(int i = 0; i < number; i++)\
	        if ((*(pp + i) = MALLOC_ARRAY(number, type)) == NULL)\
	                exit( EXIT_FAILURE );\
	}while(0)
#define PP_FREE(pp,number) \
	do{\
	for(int i = 0; i < number; i++)\
		free(*(pp + i));\
	free(pp);}while(0)
#define SQRT(sq) ((int) sqrt((double) sq))


//declare factorial
long int fact[n_prime + 1];

//declare array
int num_cc[n_prime];

#define term (*(num_cc + n-1))

long int *ord_cc;
long int *col_range;

int *split;
int *dim;

//declare arrays as character of representation
int *chr;
int *sgn;
int *fix;

//declare a mat as a charcter table
int **chi;

int *row1;
int *row2;
int *col;


int flag;

#endif
