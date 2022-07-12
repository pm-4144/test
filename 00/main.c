#include "main.h"



int main(){




mk_file_ALL();
printf("mk_file : completed\n");

mk_array_ALL();
printf("mk_array : completed\n");
cal_chr_ALL();
printf("character table (n = %2d)\n", n);

re_array_dim();	//sort with an original order
if (n>5) mk_array_col_range();
//	for(int i = 1; i < *row1; i++)printf(" %3d", row1[i]);printf("\n");
//	for(int i = 1; i < *row1; i++)printf(" %3ld", col_range[row1[i]]);printf("\n");
//	for(int i = 1; i < *row2; i++)printf(" %3d", row2[i]);printf("\n");
//	for(int i = 1; i < *row2; i++)printf(" %3ld", col_range[row2[i]]);printf("\n");
//	for(int i = 0; i < *col ; i++)printf(" %3d", col[i] );printf("\n");printf("\n");
//	for(int i = 0; i < term ; i++)printf(" %3d", col[i] );printf("\n");printf("\n");

//	for(int i = 1; i < term; i++)
//		cal_chr_col(8, i, col_range[i]);

//	for(int i = 0; i < term; i++)printf("%6ld",*(col_range+i));printf("\n");

//	for(int i = 0; i < term; i++)printf("%6d",SQRT(*(col_range+i)));printf("\n");printf("\n");

/*
for(int i = 0; i < term; i++)printf("%6ld",*(ord_cc+i));printf("\n");
for(int i = 0; i < term; i++)printf("%6ld",fact[n] / ord_cc[i]);printf("\n");printf("\n");


for(int i = 0; i < term; i++){
for(int j = 0; j < term; j++)
printf("%6d", *(*(chi + i) + j));
printf("\n");}
printf("\n");
*/


if (n > 5){
	for( int i = 8; i < term; i++){
		if (col[i] > 0){
			cal_chr_row(i, 0);
			cal_chr_set(i);
			if (i < term - 1){
				if ( col[i + 1] == 0){
					for(int j = 0; j < term; j++){
						chr[j] *= sgn[j];
					}
					cal_chr_set(i + 1);
				}
			}
		}
	}
}

for(int i = 0; i < term; i++)printf("%6ld",*(ord_cc+i));printf("\n");
for(int i = 0; i < term; i++)printf("%6ld",fact[n] / ord_cc[i]);printf("\n");printf("\n");

for(int i = 0; i < term; i++){
for(int j = 0; j < term; j++)
printf("%6d", *(*(chi + i) + j));
printf("\n");}


FREE_ALL();

return 0;
}













