


#include "mk_file.h"

/****************************************/
/*	compare two cycle shape		*/
/*					*/
/*	parameter : cycle shape,	*/
/*		  :  cycle shape	*/
/*	return    : 1 as TRUE,		*/
/*		  : 0 as False		*/
/****************************************/
int same_cycle_shape(int *cs_a, int *cs_b){
	for(int i = 0; i < n1; i++)
		if (*(cs_a + i) != *(cs_b + i))
			return 0;
	return 1;
}

/****************************************/
/*	write the row number of the 	*/
/*	 cycle shape of g^2 for the	*/
/*	 permutation g which has i-th	*/
/*	 row's cycle shape		*/
/*					*/
/*	parameter : cycle shape		*/
/*	return    : 1 as success,	*/
/*		  : 0 as failure	*/
/****************************************/
int write_split_sub(int *cs_a, int i_th,int j_th){
	FILE *fp;
//input
	read_cycle_shape(cs_a, i_th);
//output
	if ((fp = fopen("cycle_shape_tmp.txt", "a")) == NULL)
		return 0;

	for(int i =0; i < n2; i++)
		fprintf(fp, "%3d", *(cs_a +i));
	fprintf(fp, split_fmt, j_th);
	fprintf(fp, "\n");

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

	return 1;
}

int write_split(void){
	int cs_a[n2], cs_b[n1];

	for(int i = 0; i < TERMINAL; i++){
		if (!read_cycle_shape(cs_a, i))
			return 0;

		cal_split(cs_a, cs_b);

		for(int j = 0; j < TERMINAL; j++){
			if (!read_cycle_shape(cs_a, j))
				return 0;

			if (same_cycle_shape(cs_a, cs_b))
				if (write_split_sub(cs_a,i,j))
					break;
		}
	}
	remove(cycle_shape_f);
	rename("cycle_shape_tmp.txt", cycle_shape_f);
	return 1;
}

/****************************************/
/*	make the file cycle_shape_f	*/
/*	 if it does not exist		*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_file_cycle_shape(void){

	int cycle_shape[n1];

	FILE *fp;
	//whether there exisits such file, and if not then make it
	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		var_cal_cycle_shape(cycle_shape);

	return write_split();
}

/****************************************/
/*	make the file num_cc_f		*/
/*	 consisting of the number of	*/
/*	 conjugacy class of S_n		*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int write_num_cc(int sum){
	FILE *out;
	if ((out = fopen(num_cc_f, "a")) == NULL)
		return 0;

	fprintf(out, num_cc_fmt, sum);

	if (fclose(out) == EOF)
		exit(EXIT_FAILURE);

	return 1;
}

int mk_file_num_cc(void){
	FILE *fp;

	if ((fp = fopen(num_cc_f, "w")) == NULL)
		return 0;
	fprintf(fp, num_cc_fmt, 1);
	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

	if ((fp = fopen(cycle_shape_f, "r")) == NULL)
		return 0;

	int sum = 1, tmp;
	for(int i = 1; i < n_prime; i++){
		while (1){
			if (sum > TERMINAL){
				write_num_cc(sum-1);
				break;}

			fseek(fp, sum++*LINE_SIZE_CS + POS_FIX, SEEK_SET);
			fscanf(fp, "%3d", &tmp);

			if (tmp > i + 1){
				write_num_cc(sum-1);
				break;}
		}
	}

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

	return 1;
}

/****************************************/
/*	make the file ord_cc_f		*/
/*	 consisting of the order of	*/
/*	 each conjugacy class		*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/
int mk_file_ord_cc(void){
//initialize the file ord_cc_f
	FILE *fp;
	if ((fp = fopen(ord_cc_f, "w")) == NULL)
		return 0;

	fprintf(fp, " %ld\n", (long int)1);

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

//write the order of each conjugacy class
// of S_n with 1 < n <= n_prime
	for(int i = 1; i < n_prime; i++){
		if ((fp = fopen(ord_cc_f, "a")) == NULL)
			return 0;

		fprintf(fp, " %ld", (long int)1);
		for(int j = 1; j < *(num_cc + i); j++)
			fprintf(fp, " %ld", var_cal_ord_cc(j, i + 1));
	fprintf(fp, "\n");

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	}

	return 1;
}

/****************************************/
/*	make the file dim_f consisting	*/
/*	 of the dimensions of all	*/
/*	 irreducible character of S_n	*/
/*					*/
/*	parameter : void		*/
/*	return    : 1 as success	*/
/*		  : 0 as failure	*/
/****************************************/

int mk_file_dim(void){	//non-sorted
//initialize the file dim_f
	FILE *fp;
	if ((fp = fopen(dim_f, "w")) == NULL)
		return 0;

	fprintf(fp, " %d\n", 1);

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
//write
	for (int i = 1; i < n_prime; i++){
		if ((fp = fopen(dim_f, "a")) == NULL)
			return 0;

		fprintf(fp, " %d", 1);
		for(int j = 1; j < *(num_cc + i); j++)
			fprintf(fp, " %ld", var_cal_dim(j, i + 1));
	fprintf(fp, "\n");

	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);
	}
	return 1;
}

/*
int mk_file_dim(void){	//sorted with the ascending order
	mk_file_dim_sub();
	FILE *fp;
//initialize a file
	if ((fp = fopen("dim_tmp.txt", "w")) == NULL)
		return 0;
	fprintf(fp, " %d\n", 1);
	if (fclose(fp) == EOF)
		exit(EXIT_FAILURE);

//
	for (int i = 1; i < n_prime; i++){
		if ((fp = fopen("dim_tmp.txt", "a")) == NULL)
			return 0;
//read prev.file
		mk_array_dim_sub(i);
//sort with the ascending order
		cal_qsort(dim, *(num_cc + i), 1);
//write
		for(int j = 0; j < *(num_cc + i); j++)
			fprintf(fp, " %d", *(dim + j));
		fprintf(fp, "\n");

		if (fclose(fp) == EOF)
			exit(EXIT_FAILURE);
	}
//over write
	remove(dim_f);
	rename("dim_tmp.txt", dim_f);
	return 1;	
}
*/

void mk_file_ALL(void){
	mk_file_cycle_shape();
	mk_file_num_cc();

	mk_array_fact();
	mk_array_num_cc();

	mk_file_ord_cc();
	mk_file_dim();
}






