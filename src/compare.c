#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2))
        s21_make_equal_exp(&value_1, &value_2);
    s21_minus_nul(&value_1);
    s21_minus_nul(&value_2);
    if ((s21_is_positiv(value_1) && !s21_is_positiv(value_2)) || s21_is_equal(value_1, value_2)) {
        res = 0;
    } else if (!s21_is_positiv(value_1) && s21_is_positiv(value_2)) {
        res = 1;
    } else {
        int minus = s21_is_positiv(value_1);
        value_1.bits[3] = 0;
        value_2.bits[3] = 0;
        for (int k = 0; k < 96; k++) {
            if (s21_get_bit(value_1.bits[k / 32], k % 32) < s21_get_bit(value_2.bits[k / 32], k % 32))
                res = 1;
            else if (s21_get_bit(value_1.bits[k / 32], k % 32) > s21_get_bit(value_2.bits[k / 32], k % 32))
                res = 0;
        }
        if (!minus) {
            if (res) {
                res = 0;
            } else {
                res = 1;
            }
        }
    }
    return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_less(value_1, value_2);
}


int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2))
        s21_make_equal_exp(&value_1, &value_2);
    int res = 1;
    s21_minus_nul(&value_1);
    s21_minus_nul(&value_2);
    if (s21_is_positiv(value_1) != s21_is_positiv(value_2)) {
        res = 0;
    } else {
        value_1.bits[3] = 0;
        value_2.bits[3] = 0;
        for (int k = 0; k < 96; k++) {
            if (s21_get_bit(value_1.bits[k / 32], k % 32) != s21_get_bit(value_2.bits[k / 32], k % 32)) {
                res = 0;
                break;
            }
        }
    }
    return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_equal(value_1, value_2);
}
