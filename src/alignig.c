
#include "s21_decimal.h"

static int s21_logic_equal_exp(int exp_1, int exp_2, s21_decimal *value_1, s21_decimal *value_2);

int s21_make_equal_exp(s21_decimal *result_1, s21_decimal *result_2) {
    int new_exp, minus_1 = 0, minus_2 = 0;
    if (!s21_is_positiv(*result_1)) minus_1 = 1;
    if (!s21_is_positiv(*result_2)) minus_2 = 1;
    int exp_1 = s21_exp_to_int(*result_1);
    int exp_2 = s21_exp_to_int(*result_2);
    result_1->bits[3] = 0;
    result_2->bits[3] = 0;
    if (exp_1 < exp_2) {
        new_exp = s21_logic_equal_exp(exp_1, exp_2, result_1, result_2);
    } else if (exp_2 < exp_1) {
        new_exp = s21_logic_equal_exp(exp_2, exp_1, result_2, result_1);
    } else {
        new_exp = exp_1;
    }
    s21_create_new_exp(result_1, new_exp);
    s21_create_new_exp(result_2, new_exp);
    if (minus_1) s21_negate(*result_1, result_1);
    if (minus_2) s21_negate(*result_2, result_2);
    return new_exp;
}

static int s21_logic_equal_exp(int exp_1, int exp_2, s21_decimal *value_1, s21_decimal *value_2) {
    while (exp_1 != exp_2 && exp_1 < 28) {
        s21_decimal buff = *value_1;
        if (s21_mul_10(value_1)) {
            *value_1 = buff;
            break;
        }
        exp_1++;
    }
    while (exp_1 != exp_2 && exp_2 > 0) {
        s21_bank_round(value_2);
        exp_2--;
    }
    return exp_1;
}
