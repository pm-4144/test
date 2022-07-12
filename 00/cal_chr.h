#ifndef CAL_CHR_H
#define CAL_CHR_H

#include "common.h"

int cal_chr_0(int *phi);	//chi_s
int cal_chr_1(int *phi);	//trivial
int cal_chr_2(int *phi);	//sign
int cal_chr_3(int *phi);	//fix - 1
int cal_chr_4(int *phi);	//chi_3 * sgn
int cal_chr_5(int *phi);	//chi_a
int cal_chr_6(int *phi);	//chi_a * sgn
int cal_chr_7(int *phi);	//chi_s - chi_1 - chi_3
int cal_chr_8(int *phi);	//chi_7 * sgn

void cal_chr_set(int i_th);

void cal_chr_row(int i_th, int j_th);
void cal_chr_col(int i_th, int j_th, long int init);

void cal_chr_init(int i_th);

void cal_chr_ALL(void);




#endif
