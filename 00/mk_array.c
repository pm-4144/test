
#include "mk_array.h"

void mk_array_fact(void){
	*fact = 1;
	for(int i = 1; i <= n_prime; i++ )
	        *(fact + i) = i*(*(fact + i - 1));
}

/****************************************/
/*	make the array num_cc		*/
/*	 consisting of the number of	*/
/*	 conjugacy classes of S_n	*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_num_cc(void){
//read num_cc_f
	FILE *fp;
	if ((fp = fopen(num_cc_f, "r")) == NULL)
		return 0;

	for(int i = 0; i < n_prime; i++)
		fscanf(fp, num_cc_fmt, num_cc + i);

	if (fclose(fp) == EOF) 
		exit(EXIT_FAILURE);
	return 1;
}
/****************************************/
/*	make the array ord_cc		*/
/*	 consisting of the order of	*/
/*	 each conjugacy class of S_n	*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_ord_cc(void){
	FILE *fp;
	if ((fp = fopen(ord_cc_f, "r")) == NULL)
		return 0;

//read the positions of each line head
	long offset[64]; char buff[1024];
	for (int i = 0 ; !feof(fp) && i < 64; i++ ){
		*(offset + i) = ftell( fp );
		fgets( buff, sizeof(buff), fp );
	}
//read a line
	fseek(fp, *(offset + n-1), SEEK_SET);
	for(int i = 0; i < *(num_cc + n-1); i++)
		fscanf(fp, " %ld", ord_cc + i);

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	return 1;
}

/****************************************/
/*	make the array split		*/
/*	 consisting of the order of	*/
/*	 the row which has a cycle	*/
/*	 shape of g^2 for a permutaion	*/
/*	 g which has the cycle shape	*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_split(void){
//open
	FILE *fp;
	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		return 0;
//read
	for(int i = 0; i < *(num_cc + n-1); i++){
		fseek(fp, i*LINE_SIZE_CS + POS_SPLIT, SEEK_SET);
		fscanf(fp, split_fmt, split + i);
	}
//close
	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	return 1;
}

/****************************************/
/*	make the array as a character	*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_chr(void){
return 0;
}
/****************************************/
/*	make the array sgn, which is a	*/
/*	 sign function as a class func-	*/
/*	 tion				*/
/*					*/
/*	parameter : sgn			*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_sgn(void){
//open
	FILE *fp;
	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		return 0;
//read
	for(int i = 0; i < *(num_cc + n-1); i++){
		fseek(fp, i*LINE_SIZE_CS + POS_SIGN, SEEK_SET);
		fscanf(fp, "%3d", sgn + i);
	}
//close
	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	return 1;
}

/****************************************/
/*	make the array fix, whose entry	*/
/*	 is the number of elements fix-	*/
/*	 ed by the permutation in the	*/
/*	 conjugacy class		*/
/*					*/
/*	parameter : fix			*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_fix(void){
//open
	FILE *fp;
	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		return 0;
//read
	for(int i = 0; i < *(num_cc + n-1); i++){
		fseek(fp, i*LINE_SIZE_CS + POS_FIX, SEEK_SET);
		fscanf(fp, "%3d", fix + i);
		*(fix + i) = n - *(fix + i) - 1;
	}
//close
	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	return 1;
}

/****************************************/
/*	make the array dim		*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_dim_sub(int m){
	FILE *fp;
	if ((fp = fopen(dim_f, "r")) == NULL)
		return 0;

//read the position of each line head
	long offset[64]; char buff[1024];
	for (int i = 0 ; !feof(fp) && i < 64; i++ ){
		*(offset + i) = ftell( fp );
		fgets( buff, sizeof(buff), fp );
	}

	fseek(fp, *(offset + m - 1), SEEK_SET);
	for(int i = 0; i < *(num_cc + m - 1); i++)
		fscanf(fp, "%d", dim + i);

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

	cal_qsort(dim, *(num_cc + m - 1), 1);
	return 1;
}

int mk_array_dim(void){
	if (n < 6) return 1;
	return mk_array_dim_sub(n);
}

int re_array_dim(void){
	if (n < 6) return 1;

	int dim_sub[8];
	for(int i = 0; i < 8; i++)
		*(dim_sub + i) = *(*(chi + i) + 0);

	for(int i = 0; i < 8; i++){
		if (*(dim + i) == *(dim_sub + i))
			continue;

		for(int j = i;; j++)
			if (*(dim + j) == *(dim_sub + i)){
				*(dim + j) = *(dim + i);
				*(dim + i) = *(dim_sub + i);
				break;
			}
	}

	for( int i = 8; i < term; i++)
		*(*(chi + i) + 0) = *(dim + i);

	return 1;
}
/****************************************/
/*					*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_array_col_range(void){
	for(int i = 0; i < term; i++){
		*(col_range + i) = *(fact + n) / *(ord_cc + i);
		for(int j = 0; j < 8; j++)
			*(col_range + i) -= (long) *(*(chi + j) + i) * *(*(chi + j) + i);
//	*(col_range + i) = SQRT(*(col_range + i));
	}

	return 1;
}

void mk_array_probe_range(void){
	int j = 1;
// row1
	for (int i = 0; i < term; i++)
		if (*(sgn + i) == 1) 
			*(row1 + j++) = i;
	*row1 = j; j = 1;
// row2
	for (int i = 0; i < term; i++)
		 if (*(sgn + i) == -1)
			*(row2 + j++) = i;
	*row2 = j;
//col
	for (int i = 0; i < term; i++)
		for (int j = i; j < term; j++)
			if ( dim[i] == dim[j]){
				if ((j - i) % 2 == 0)
					col[j] = j;
			}else{
				i = j - 1; break;}
/*
	cal_qsort(col, term, 1);
	for (int i = 0;; i++)
		if (col[i] > 0) {j = i; break;}
	*col = term - j;
	for (int i = 0; i < *col; i++)
		col[i + 2] = col[j + i];
	*col += 2;
	for (int i = *col; i < term; i++)
		col[i] = 0;
*/
}



void MALLOC_ALL(void){
PP_MALLOC(chi, term, int);

if ((ord_cc = MALLOC_ARRAY(term, long int)) == NULL)exit(EXIT_FAILURE);
if ((col_range = MALLOC_ARRAY(term, long int)) == NULL)exit(EXIT_FAILURE);

if ((split = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((dim = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((chr = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((sgn = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((fix = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((row1 = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((row2 = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
if ((col = MALLOC_ARRAY(term, int)) == NULL)exit(EXIT_FAILURE);
}

void FREE_ALL(void){
PP_FREE(chi, term);

free(ord_cc);
free(col_range);
free(split);
free(dim);
free(chr);
free(sgn);
free(fix);
free(row1);
free(row2);
free(col);
}

void mk_array_ALL(void){

MALLOC_ALL();
mk_array_ord_cc();
mk_array_split();

//make array as character of representation
//mk_array_chr();
mk_array_sgn();
mk_array_fix();

mk_array_dim();
//mk_array_col_range();
mk_array_probe_range();
}








