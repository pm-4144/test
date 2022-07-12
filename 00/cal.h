#ifndef CAL_H
#define CAL_H

#include "common.h"

int read_cycle_shape(int *cycle_shape, int i_th);

long int cal_hook(int *young_tabular, int m);

long int cal_dim(int *young_tabular, int m);
long int var_cal_dim(int i_th, int m);

long int cal_ord_cc(int *cycle_shape);
long int var_cal_ord_cc(int i_th, int m);

void cal_young_tabular(int *young_tabular);
void cal_young_tabular_sub(int *young_tabular, int m);

void cal_qsort(int *array, int range_size,int order);
void cal_split(int *cycle_shape, int *split);
void cal_cycle_shape(int *cycle_shape);
void var_cal_cycle_shape(int *cycle_shape);

#endif
