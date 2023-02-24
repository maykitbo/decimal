
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int res = 0;
    if (result == NULL) {
        res = 1;
    } else {
        int exp = s21_exp_to_int(value);
        int minus = s21_is_positiv(value);
        value.bits[3] = 0;
        for (int k = 0; k < exp; k++) {
            s21_div_help(&value, s21_decimal_int(10), result);
            value = *result;
        }
        if (!minus) {
            res = s21_add(value, s21_decimal_int(1), &value);
            s21_negate(value, &value);
        }
        *result = value;
    }
    return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int res = 0;
    if (result == NULL) {
        res = 1;
    } else {
        int exp = s21_exp_to_int(value);
        int minus = s21_is_positiv(value);
        value.bits[3] = 0;
        s21_decimal buff = s21_create_decimal();
        for (int k = 0; k < exp; k++) {
            s21_div_help(&value, s21_decimal_int(10), result);
            buff = value;
            value = *result;
        }
        if (!s21_is_less(buff, s21_decimal_int(5))) res = s21_add(value, s21_decimal_int(1), &value);
        if (!minus) s21_negate(value, &value);
        *result = value;
    }
    return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int res = 0;
    if (result == NULL) {
        res = 1;
    } else {
        int minus = s21_is_positiv(value), exp = s21_exp_to_int(value);
        value.bits[3] = 0;
        for (int k = 0; k < exp; k++) {
            s21_div_help(&value, s21_decimal_int(10), result);
            s21_decimal_copy(*result, &value);
        }
        if (!minus) s21_negate(value, &value);
        *result = value;
    }
    return res;
}

void s21_bank_round(s21_decimal *src) {
    int minus = 0;
    if (!s21_is_positiv(*src)) minus = 1;
    int exp = src->bits[3];
    s21_decimal buff = *src;
    s21_decimal mod_h = s21_create_decimal();
    s21_mod(*src, s21_decimal_int(100), &mod_h);
    s21_div_help(&buff, s21_decimal_int(10), src);
    int a = mod_h.bits[0];
    if (a % 10 > 5 || (a % 10 == 5 && (a / 10) % 2)) {
        s21_add(*src, s21_decimal_int(1), src);
    }
    if (minus) s21_negate(*src, src);
    src->bits[3] = exp;
}
