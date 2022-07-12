#include "cal.h"

/****************************************/
/*	read the file cycle_shape_f	*/
/*	 and scan i-th row for all i	*/
/*	 with 0 <= i < TERMINAL		*/
/*					*/
/*	parameter : cycle shape, i_th	*/
/*	return    : 1 as success,	*/
/*		  : 0 as failure	*/
/****************************************/
int read_cycle_shape_sub(int *cycle_shape, int i_th, int m){
	FILE *fp;
	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		return 0;

	fseek(fp, i_th*LINE_SIZE_CS, SEEK_SET);
	for(int i = 0; i < m; i++)
		fscanf(fp, "%3d", cycle_shape + i);

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

	return 1;
}

int read_cycle_shape(int *cycle_shape, int i_th){
	return read_cycle_shape_sub(cycle_shape, i_th, n2);
}

/****************************************/
/*	calculate the hook length	*/
/*	 of a young tabular		*/
/*					*/
/*	parameter : young tabular	*/
/*	return    : hook length		*/
/****************************************/
long int cal_hook(int *young_tabular, int m){
    long int ret = 1;
    for( int i = 0; i < m;i++ ){
        for( int j = 0; j < *(young_tabular + i); j++ ){
            int ret_sub = *(young_tabular + i) - j;
            for( int k = i + 1; j < *(young_tabular + k); k++ )
                ret_sub++;
            ret *= ret_sub;
        }
    }
    return ret;
}

/****************************************/
/*	calculate the dimension		*/
/*	 of the character corresponding */
/*	 to young tabular		*/
/*					*/
/*	parameter : young tabular	*/
/*	return    : dimension		*/
/****************************************/
long int cal_dim(int *young_tabular, int m){
	return  *(fact + m) / cal_hook(young_tabular, m);
}

long int var_cal_dim(int i_th, int m){
	int cs[n_prime];
	for(int i=0;i<m;i++)cs[i]=0;	//initialize

	read_cycle_shape_sub(cs, i_th, n1);	//read cycle shape corr. to y.tabular -> cs
	cal_young_tabular_sub(cs, m);		//mk y.tabular -> cs

	return cal_dim(cs, m);
}

/****************************************/
/*	make an integer array as young	*/
/*	 tabular from a cycle shape	*/
/*					*/
/*	parameter : cycle_shape		*/
/*	retuen    : void		*/
/****************************************/
void cal_young_tabular_sub(int *cycle_shape, int m){
	int sum = 0;
	for(int i = 0; i < n1; i++)
		sum += *(cycle_shape + i);

	if(sum == m) return;
	for(int i = 0;; i++){
		if(sum == m)return;
		if(*(cycle_shape + i) == 0){
			*(cycle_shape + i) = 1;
			sum++;
		}
	}
}
void cal_young_tabular(int *cycle_shape){
	cal_young_tabular_sub(cycle_shape, n);
}

/****************************************/
/*	calculate the order of		*/
/*	 a conjugacy class of S_n	*/
/*	 corresponding to cycle_shape	*/
/*					*/
/*	parameter : cycle_shape		*/
/*	return    : order of cc		*/
/****************************************/
long int ncr(int a, int b){	//combination aCb
	if( a*b == 0)
		return 1;
	return *(fact + a) / *(fact + b) / *(fact + a - b);
}

long int cal_ord_cc_sub(int *cs, int m){
	long int ret = 1;
	int n_init = m;

	int *cs_sub;
	if ((cs_sub = MALLOC_ARRAY(m, int)) == NULL)
		return 0;

//make array as the cycle type
	for(int i = 1; i < m; i++){
		*(cs_sub + i) = 0;
		for(int j = 0; j < n1; j++){
			if (*(cs + j) == 0) break;
			if (*(cs + j) == i + 1)
				*(cs_sub + i) += 1;
		}
	}
//calculate the order
	for(int i = 0; i < n1; i++){
		if (*(cs + i) == 0) break;
		ret *= ncr(n_init, *(cs + i));
		n_init -= *(cs + i);
	}

	for(int i = 1; i < m; i++){
		for(int j = 0; j < *(cs_sub + i); j++)
			ret *= *(fact + i);
		if (i < n1)
			ret /= *(fact + *(cs_sub + i));
	}
//return
	free(cs_sub);
	return ret;
}

long int cal_ord_cc(int *cs){
	return cal_ord_cc_sub(cs, n);
}

long int var_cal_ord_cc(int i_th, int m){
	int cs[n1];

//read i-th cycle shape
	read_cycle_shape(cs, i_th);
//return the order
	return cal_ord_cc_sub(cs, m);
}


/****************************************/
/*	qsort for int array		*/
/*					*/
/*	parameter :			*/
/*	 array,		array to sort	*/
/*	 array_size,	array size	*/
/*	 order,		-1 as dsc order	*/
/*			 1 as asc order	*/
/*	return    : void		*/
/****************************************/
int descending_order(const void * comp1, const void * comp2){
	if (*(int *)comp1 > *(int *)comp2){
		return -1;}
	else if (*(int *)comp1 < *(int *)comp2){
		return  1;}
	else{	return  0;}
}

int ascending_order(const void * comp1, const void * comp2){
	if (*(int *)comp1 > *(int *)comp2){
		return  1;}
	else if (*(int *)comp1 < *(int *)comp2){
		return -1;}
	else{   return  0;}
}

void cal_qsort(int *array, int range_size,int order){
switch(order){
case -1	:
	qsort(array, range_size, sizeof(int), descending_order);
	break;
default	:
case 1	:
	qsort(array, range_size, sizeof(int), ascending_order);
}}

/****************************************/
/*	for an arbitary permutation g,	*/
/*	calculate cycle_shape of g^2	*/
/*					*/
/*	parameter : cycle_shape of g,	*/
/*	          :  cycle_shape of g^2	*/
/*	return    : void		*/
/****************************************/
void cal_split(int *cycle_shape, int *split){
	int j = 0;
	for(int i = 0; i < n1; i++){
		if(*(cycle_shape + i) == 0) break;
		if(*(cycle_shape + i) == 2){
			*(split + j++) = 0;}
		else if(*(cycle_shape + i) % 2 == 0){
			*(split + j++) = *(cycle_shape + i) / 2;
			*(split + j++) = *(cycle_shape + i) / 2;}
		else{	*(split + j++) = *(cycle_shape + i);}

	}
	for(int i = j; i < n1; i++)
		*(split + i) = 0;

	cal_qsort(split, n1, -1);
}

/****************************************/
/*	calculate the sign of		*/
/*	 an arbitary permutaion		*/
/*	 which has the cycle shape	*/
/*					*/
/*	parameter : cycle shape		*/
/*	return    : -1 for odd perm.	*/
/*		  :  1 for even perm.	*/
/****************************************/
int cal_sign(int *cycle_shape){
	int prod = 1;
	for(int i = n1 - 1;; i--){
		if(*(cycle_shape + i) == 0) return prod;
		prod *= *(cycle_shape + i) % 2 * 2 - 1;
	}
	return prod;
}

/****************************************/
/*	sum of all component of		*/
/*	 cycle shape up to i-th one	*/
/*					*/
/*	parameter : cycle shape, order	*/
/*	return    : 1 as TRUE		*/
/*		  : 0 as FALSE		*/
/****************************************/
int no_greater_n_sub(int *cycle_shape, int i_th){
	int sum = 0;
	for(int j = 0; j < i_th; j++)
		sum += *(cycle_shape + j);
	if( sum <= n_prime ) return 1;
	return 0;
}

int no_greater_m_sub(int *cycle_shape, int i_th, int m){
	int sum = 0;
	for(int j = 0; j < i_th; j++)
		sum += *(cycle_shape + j);
	if( sum <= m ) return 1;
	return 0;
}

int equal_to_m_sub(int *cycle_shape, int i_th, int m){
	int sum = 0;
	for(int j = 0; j < i_th; j++)
		sum += *(cycle_shape + j);
	if( sum == m ) return 1;
	return 0;
}

/****************************************/
/*	sum of all component of		*/
/*	cycle shape			*/
/*					*/
/*	parameter : cycle shape		*/
/*	return	  : 1 as TRUE		*/
/*		  : 0 as FALSE		*/
/****************************************/
int no_greater_n(int *cycle_shape){
	return no_greater_n_sub(cycle_shape, n1);
}

int equal_to_m(int *cycle_shape, int m){
	return equal_to_m_sub(cycle_shape, n1, m);
}

/****************************************/
/*	calculate all cycle shape of	*/
/*	symmetric group of dimension n	*/
/*					*/
/*	parameter : cycle shape		*/
/*	return    : void		*/
/****************************************/
void cal_cycle_shape_sub(int *cycle_shape, int i_th, int initial){
	if(i_th < n1){
		for( int i = initial; i <= (int)n_prime / (n1 - i_th); i++ ){
			if( i == 1 ) continue;
			if( !no_greater_n_sub(cycle_shape, i_th) ) break;
			*(cycle_shape + i_th) = i;
			cal_cycle_shape_sub(cycle_shape, i_th + 1, i);
		}
	}else{
		if( no_greater_n(cycle_shape) ){

		FILE *fp = fopen(cycle_shape_f, "a");
		 if (fp == NULL) exit( EXIT_FAILURE );

			int sum = 0;
			for(int j = n1; j > 0; j--){
				sum += *(cycle_shape + j - 1);
				if (fprintf(fp, "%3d", *(cycle_shape + j - 1)) < 0)
					break;
			}
			fprintf(fp, "%3d\n", cal_sign(cycle_shape));
			if( fclose( fp ) == EOF ) exit( EXIT_FAILURE );
		}
	}
}

void cal_cycle_shape(int *cycle_shape){
	cal_cycle_shape_sub(cycle_shape, 0, 0);
	return;
}

/****************************************/
/*	calculate all cycle shape of	*/
/*	 symmetric group of dimension n	*/
/*	 with increasing its length	*/
/*					*/
/*	parameter : cycle shape		*/
/*	return    : void		*/
/****************************************/
void var_cal_cycle_shape_sub(int *cycle_shape, int i_th, int initial,int m){
	if(i_th < n1){
		for(int i = initial; i <= (int)n_prime / (n1 - i_th); i++){
			if (i == 1) continue;
			if (!no_greater_m_sub(cycle_shape, i_th, m)) break;
			*(cycle_shape + i_th) = i;
			var_cal_cycle_shape_sub(cycle_shape, i_th + 1, i, m);
		}
	}else{
		if( equal_to_m(cycle_shape,m) ){

			FILE *fp = fopen(cycle_shape_f, "a");
			 if (fp == NULL) exit( EXIT_FAILURE );

			for(int j = n1; j > 0; j--)
				fprintf(fp, "%3d", *(cycle_shape + j - 1));
			fprintf(fp, "%3d%3d", cal_sign(cycle_shape), m);
			fprintf(fp, split_fmt, 0);
			fprintf(fp, "\n");

			if (fclose(fp) == EOF)
				exit( EXIT_FAILURE );
		}
	}
}

void var_cal_cycle_shape(int *cycle_shape){
	for(int m = 0; m <= n_prime; m++)
		var_cal_cycle_shape_sub(cycle_shape,0,0,m);
}
