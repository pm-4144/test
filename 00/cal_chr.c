

#include "cal_chr.h"


int cal_chr_0(int *phi){	//chi_s
	int psi[term];
	cal_chr_3(psi);

	for(int i = 0; i < term; i++)
		*(phi + i) = (*(psi + i) * (*(psi + i)) + *(psi + *(split + i)))/2;

	return 1;
}

/****************************************/
/*	calculate some character which	*/
/*	 is known as irreducible one	*/
/*					*/
/* parameter	:			*/
/*	 void				*/
/* return	:			*/
/*	 1 as success			*/
/*	 0 as failure			*/
/****************************************/

int cal_chr_1(int *phi){	//trivial
	for(int i = 0; i < term; i++)
		*(phi + i) = 1;
	return 1;
}

int cal_chr_2(int *phi){	//sign
	for(int i = 0; i < term; i++)
		*(phi + i) = *(sgn + i);
	return 1;
}

int cal_chr_3(int *phi){	//fix - 1
	for(int i = 0; i < term; i++)
		*(phi + i) = *(fix + i);
	return 1;
}

int cal_chr_4(int *phi){	//chi_3 * sgn
	cal_chr_3(phi);
	for(int i = 0; i < term; i++)
		*(phi + i) *= *(sgn + i);
	return 1;
}

int cal_chr_5(int *phi){	//chi_a
	int psi[term];
	cal_chr_3(psi);

	for(int i = 0; i < term; i++)
		*(phi + i) = (*(psi + i) * (*(psi + i)) - *(psi + *(split + i)))/2;

	return 1;
}

int cal_chr_6(int *phi){	//chi_a * sgn
	cal_chr_5(phi);
	for(int i = 0; i < term; i++)
		*(phi + i) *= *(sgn + i);
	return 1;
}

int cal_chr_7(int *phi){	//chi_s - chi_1 - chi_3
	int psi[term];
	cal_chr_0(phi);
	cal_chr_3(psi);

	for(int i = 0; i < term; i++)
		*(phi + i) -= *(psi + i) + 1;

	return 1;
}

int cal_chr_8(int *phi){	//chi_7 * sgn
	cal_chr_7(phi);
	for(int i = 0; i < term; i++)
		*(phi + i) *= *(sgn + i);
	return 1;
}

void cal_chr_set(int i_th){

for(int i = 0; i < term; i++)
*(*(chi + i_th) + i) = *(chr + i);
}


/****************************************/
/*	Schur's orthogonality relations	*/
/*					*/
/* parameter	:			*/
/*  i_th as an i-th column (row) order	*/
/*  j_th as a j_th column (row) order	*/
/* return	:			*/
/*  1 as TRUE				*/
/*  0 as FALSE				*/
/****************************************/
int orth_col(int i_th, int j_th){
	long int sum = (long) 0;
	for (int i = 0; i < term; i++){
		sum += ((long) chi[i][i_th]) * ((long) chi[i][j_th]);
	}
	if (i_th == j_th){
		if ( sum == fact[n] / ord_cc[i_th]){
			return 1;
		}
	}else{
		if (sum == (long) 0){
			return 1;
		}
	}
	return 0;
}

int orth_row(int i_th, int j_th){
	long int sum = (long) 0;
	for (int i = 0; i < term; i++){
		sum += ord_cc[i] * ((long) chi[i_th][i]) * ((long) chi[j_th][i]);
	}

	if (i_th == j_th){
		if (sum == fact[n]){
			return 1;
		}
	}else{
		if (sum == (long) 0){
			return 1;
		}
	}
	return 0;
}

int orth_row1(int i_th, int j_th){
	long int sum = (long) 0;
	for (int i = 1; i < *row1; i++){
		sum += ord_cc[row1[i]] * ((long) chi[i_th][row1[i]]) * ((long) chi[j_th][row1[i]]);
	}
	if (i_th == j_th){
		if (i_th < term - 1){
			if (col[i_th + 1] == 0){	//pair
				if (sum == fact[n] / (long) 2){
					return 1;
				}
			}
		}
		if (sum == fact[n]){
			return 1;
		}
	}else{
		if (sum == (long) 0){
			return 1;
		}
	}
	return 0;
}

int orth_row2(int i_th, int j_th){
	long int sum = (long) 0;
	for (int i = 1; i < *row2; i++){
		sum += ord_cc[row2[i]] * ((long) chi[i_th][row2[i]]) * ((long) chi[j_th][row2[i]]);
	}
	if (i_th == j_th){ 
		if (i_th < term - 1){
			 if (col[i_th + 1] == 0){        //pair 
				if (sum == fact[n] / (long) 2){
					return 1;
				}
			}
		}
		if (sum == 0){
			return 1;
		}
	}else{
		if (sum == (long) 0){
			return 1;
		}
	}
	return 0;
}
/****************************************/
/*	calculate some row and some 	*/
/*	 column of the character table	*/
/*					*/
/* parameter	:			*/
/*  i_th as an i-th row order		*/
/*  j_th as a j_th column order		*/
/****************************************/
void cal_chr_row1(int i_th, int j_th){
if (flag == 0){
	if (j_th < *row1){
		if (i_th < term - 1){
			if (col[i_th + 1] == 0){
				for (int i = -SQRT(col_range[row1[j_th]] / 2); i <= SQRT(col_range[row1[j_th]] / 2); i ++){
					chi[i_th][row1[j_th]] = i;
					chi[i_th + 1][row1[j_th]] = i;
					cal_chr_row1(i_th, j_th + 1);
				}
			}else{
				for (int i = -SQRT(col_range[row1[j_th]]); i <= SQRT(col_range[row1[j_th]]); i ++){
					chi[i_th][row1[j_th]] = i;
					cal_chr_row1(i_th, j_th + 1);
				}
			}
		}else{
			for (int i = -SQRT(col_range[row1[j_th]]); i <= SQRT(col_range[row1[j_th]]); i ++){
				chi[i_th][row1[j_th]] = i;
				cal_chr_row1(i_th, j_th + 1);
			}
		}
	}else{
		flag = 1;
		flag *= orth_row1(i_th, i_th);
		for (int i = 0; i < 4; i++){
			flag *= orth_row1(i_th, 2*i);
		}
if (flag) {
	for (int i = 0; i<term; i++) {
//		printf("%3d",(
		chr[i] += chi[i_th][i];
//		));
	} 
//	printf("\n");
}
//printf(" (flag = %d)\n",flag);
	}
}}

void cal_chr_row2(int i_th, int j_th){
if (flag == 0){
	if (j_th < *row2){
		if (i_th < term - 1){
			if (col[i_th + 1] == 0){
				for (int i = -SQRT(col_range[row2[j_th]] / 2); i <= SQRT(col_range[row2[j_th]] / 2); i ++){
					chi[i_th][row2[j_th]] = i;
					chi[i_th + 1][row2[j_th]] = i * sgn[row2[j_th]];
					cal_chr_row2(i_th, j_th + 1);
				}
			}else{
				for (int i = -SQRT(col_range[row2[j_th]]); i <= SQRT(col_range[row2[j_th]]); i ++){
					chi[i_th][row2[j_th]] = i;
					cal_chr_row2(i_th, j_th + 1);
				}
			}
		}else{
			for (int i = -SQRT(col_range[row2[j_th]]); i <= SQRT(col_range[row2[j_th]]); i ++){
				chi[i_th][row2[j_th]] = i;
				cal_chr_row2(i_th, j_th + 1);
			}
		}
	}else{
		flag = 1;
		flag *= orth_row2(i_th, i_th);
		for (int i = 0; i < 4; i++)
			flag *= orth_row2(i_th, 2*i);
if (flag) {
	for (int i = 1; i<term; i++){
//		printf("%3d",(
		chr[i] += chi[i_th][i];
//		));
	}
//	printf("\n");
}

//printf(" (flag = %d)\n",flag);
	}
}}

void cal_chr_row(int i_th, int j_th){
	cal_chr_init(i_th);
	for(int j = 0; j < term; j++)chr[j]=0;
	flag = 0;
	cal_chr_row1(i_th, 2);

	cal_chr_init(i_th);
	flag = 0;
	cal_chr_row2(i_th, 1);
}

void cal_chr_col_sub(int i_th, int j_th, long int init){
if (flag == 0){
	if (i_th < term){
		if (i_th < term -1){
			if (col[i_th + 1] == 0){
				for (int i = -SQRT(init / 2); i <= SQRT(init / 2); i++){
					chi[i_th][j_th] = i;
					chi[i_th + 1][j_th] = i * sgn[j_th];
					cal_chr_col(i_th + 2, j_th, init - ((long) 2)*((long) i)*((long) i));
				}
			}else{
				for (int i = SQRT(init); i <= SQRT(init); i++){
					chi[i_th][j_th] = i;
					cal_chr_col(i_th + 1, j_th, init - ((long) i)*((long) i));
				}
			}
		}else{
			for (int i = SQRT(init); i <= SQRT(init); i++){
				chi[i_th][j_th] = i;
				cal_chr_col(i_th + 1, j_th, init - ((long) i)*((long) i));
			}
		}
	}else{
		flag = 1;
		flag *= orth_col(j_th, 0);
		flag *= orth_col(j_th, j_th);
//if (flag) {for (int i = 0; i<term; i++) {printf("%3d",chi[i][j_th]);} printf("\n");}
//printf(" (flag = %d)\n",flag);
	}
}}
void cal_chr_col(int i_th, int j_th, long int init){
//for(int i = 8; i < term; i++)for(int j = 1; j < term; j++)chi[i][j]=0;
	flag = 0;
	cal_chr_col_sub(i_th, j_th, init);
}

void cal_chr_init(int i_th){
	for(int i = i_th; i < term; i++){
		for(int j = 1; j < term; j++){
			chi[i][j]=0;
		}
	}
}

void cal_chr_ALL(void){
	switch (n){
	default	:
		cal_chr_6(chr); cal_chr_set(7);
	case 5	:
		cal_chr_5(chr); cal_chr_set(6);
		cal_chr_8(chr); cal_chr_set(5);
	case 4	:
		cal_chr_7(chr); cal_chr_set(4);
		cal_chr_4(chr); cal_chr_set(3);
	case 3	:
		cal_chr_3(chr); cal_chr_set(2);
	case 2	:
		cal_chr_2(chr); cal_chr_set(1);
	case 1	:
		cal_chr_1(chr); cal_chr_set(0);
	}
}







