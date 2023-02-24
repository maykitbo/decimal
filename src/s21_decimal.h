#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct {
    int bits[4];
} s21_decimal;

void s21_set_bit(int *x, int pos);
int s21_get_bit(int x, int pos);
void s21_invers_bit(int *x, int pos);
void s21_shift_right(s21_decimal *buff, int shift);
void s21_decimal_copy(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
void s21_bank_round(s21_decimal *src);

int s21_make_equal_exp(s21_decimal *result_1, s21_decimal *result_2);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void s21_div_help(s21_decimal *value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_10(s21_decimal *result);

int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_positiv(s21_decimal src);
void s21_minus_nul(s21_decimal *src);

s21_decimal s21_decimal_int(int num);
void s21_correct_exp(s21_decimal *src);
int s21_exp_to_int(s21_decimal dec);
void s21_create_new_exp(s21_decimal *src, int new_exp);
s21_decimal s21_create_decimal();
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // SRC_S21_DECIMAL_H_
