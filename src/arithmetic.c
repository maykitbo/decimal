#include "s21_decimal.h"

static void s21_div_sub(s21_decimal *value_1, s21_decimal value_2, s21_decimal *result);
static int s21_mul_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
static int s21_add_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal buff = *result;
    int minus = 0, error = 0;
    if (!s21_is_positiv(value_1) && !s21_is_positiv(value_2)) {
        minus = 1;
        s21_negate(value_1, &value_1);
        s21_negate(value_2, &value_2);
    }
    if (s21_is_positiv(value_1) && !s21_is_positiv(value_2)) {
        s21_negate(value_2, &value_2);
        error = s21_sub(value_1, value_2, result);
    } else if (!s21_is_positiv(value_1) && s21_is_positiv(value_2)) {
        s21_negate(value_1, &value_1);
        error = s21_sub(value_2, value_1, result);
    } else {
        if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2)) s21_make_equal_exp(&value_1, &value_2);
        int exp = s21_exp_to_int(value_1);
        int r = s21_add_help(value_1, value_2, result);
        while (r && exp) {
            exp--;
            s21_bank_round(&value_1);
            s21_bank_round(&value_2);
            r = s21_add_help(value_1, value_2, result);
        }
        if (r) {
            *result = buff;
            if (minus) {
                error = 2;
            } else {
                error = 1;
            }
        }
        if (minus) s21_negate(*result, result);
        s21_create_new_exp(result, exp);
    }
    return error;
}

static int s21_add_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    *result = s21_create_decimal();
    int r = 0;
    for (int k = 0; k < 96; k++) {
        int sum = s21_get_bit(value_1.bits[k / 32], k % 32) + s21_get_bit(value_2.bits[k / 32], k % 32) + r;
        if (sum == 1) {
            s21_set_bit(&result->bits[k / 32], k % 32);
            r = 0;
        } else if (sum == 2) {
            r = 1;
        } else if (sum == 3) {
            s21_set_bit(&result->bits[k / 32], k % 32);
            r = 1;
        } else {
            r = 0;
        }
    }
    return r;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0, minus = 0;
    if (!s21_is_positiv(value_1) && !s21_is_positiv(value_2)) {
        minus = 1;
        s21_negate(value_1, &value_1);
        s21_negate(value_2, &value_2);
    }
    if (s21_is_positiv(value_1) != s21_is_positiv(value_2)) {
        s21_negate(value_2, &value_2);
        error = s21_add(value_1, value_2, result);
    } else {
        int exp = s21_exp_to_int(value_1);
        if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2)) exp = s21_make_equal_exp(&value_1, &value_2);
        if (s21_is_less(value_1, value_2)) {
            s21_negate(value_1, &value_1);
            s21_negate(value_2, &value_2);
            error = s21_sub(value_2, value_1, result);
        } else {
            int r = 0;
            *result = s21_create_decimal();
            for (int k = 0; k < 96; k++) {
                int sub = s21_get_bit(value_1.bits[k / 32], k % 32) \
                         - s21_get_bit(value_2.bits[k / 32], k % 32) - r;
                if (sub == 1) {
                    s21_set_bit(&result->bits[k / 32], k % 32);
                    r = 0;
                } else if (sub == -1) {
                    s21_set_bit(&result->bits[k / 32], k % 32);
                    r = 1;
                } else if (sub == -2) {
                    r = 1;
                } else {
                    r = 0;
                }
            }
        }
        if (minus) s21_negate(*result, result);
        s21_create_new_exp(result, exp);
    }
    return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exp_1 = s21_exp_to_int(value_1), exp_2 = s21_exp_to_int(value_2), minus = 0;
    if (s21_is_positiv(value_1) != s21_is_positiv(value_2)) minus = 1;
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    *result = s21_create_decimal();
    int res = s21_mul_help(value_1, value_2, result);
    while (res && (exp_1 || exp_2)) {
        if (((s21_is_less(value_1, value_2)) && exp_2) || !exp_1) {
            s21_bank_round(&value_2);
            exp_2--;
        } else {
            s21_bank_round(&value_1);
            exp_1--;
        }
        res = s21_mul_help(value_1, value_2, result);
    }
    int exp = exp_1 + exp_2;
    while (exp > 28) {
        exp--;
        s21_bank_round(result);
    }
    s21_create_new_exp(result, exp);
    if (minus) s21_negate(*result, result);
    if (minus && res) res = 2;
    if (res) *result = s21_create_decimal();
    return res;
}

static int s21_mul_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 0;
    s21_decimal tmp = *result;
    while (s21_is_not_equal(value_2, s21_decimal_int(0)) && !res) {
        if (s21_get_bit(value_2.bits[0], 0)) {
            res = s21_add(tmp, value_1, &tmp);
        }
        if (s21_get_bit(value_1.bits[2], 31)) res = 1;
        s21_shift_right(&value_2, 1);
        s21_shift_right(&value_1, -1);
    }
    if (!res) *result = tmp;
    return res;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0, exp = s21_exp_to_int(value_1), minus = 0;
    if (s21_is_equal(value_2, s21_decimal_int(0))) error = 3;
    if (!error) {
        if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2)) {
            exp = s21_make_equal_exp(&value_1, &value_2);
        }
        if (!s21_is_positiv(value_1)) minus = 1;
        value_1.bits[3] = 0;
        value_2.bits[3] = 0;
        s21_div_help(&value_1, value_2, result);
        *result = value_1;
        if (minus) s21_negate(*result, result);
        s21_create_new_exp(result, exp);
    }
    return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    if (s21_is_equal(value_2, s21_decimal_int(0))) {
        error = 3;
    } else if (s21_is_equal(value_1, value_2)) {
        *result = s21_decimal_int(1);
    } else {
        if (s21_exp_to_int(value_1) != s21_exp_to_int(value_2)) {
            s21_make_equal_exp(&value_1, &value_2);
        }
        if (s21_is_equal(value_2, s21_decimal_int(0))) {
            if (s21_is_positiv(value_1) != s21_is_positiv(value_2)) {
                error = 2;
            } else {
                error = 1;
            }
        } else {
            int minus = 0, exp = 0;
            if (s21_is_positiv(value_1) != s21_is_positiv(value_2)) minus = 1;
            value_1.bits[3] = 0;
            value_2.bits[3] = 0;
            s21_decimal buff = s21_create_decimal(), mod = s21_create_decimal();
            s21_div_help(&value_1, value_2, &buff);
            while (exp < 28 && s21_is_not_equal(value_1, s21_decimal_int(0))) {
                if (s21_mul_10(&buff)) break;
                if (s21_mul_10(&value_1)) {
                    s21_bank_round(&value_1);
                    s21_bank_round(&value_2);
                    s21_mul_10(&value_1);
                }
                s21_div_help(&value_1, value_2, &mod);
                if (s21_add(buff, mod, &buff)) break;
                exp++;
            }
            s21_create_new_exp(&buff, exp);
            if (minus) s21_negate(buff, &buff);
            *result = buff;
        }
    }
    return error;
}

void s21_div_help(s21_decimal *value_1, s21_decimal value_2, s21_decimal *result) {
    if (s21_is_less(*value_1, value_2)) {
        *result = s21_create_decimal();
    } else if (s21_is_equal(*value_1, value_2)) {
        *result = s21_decimal_int(1);
        *value_1 = s21_create_decimal();
    } else {
        *result = s21_create_decimal();
        s21_div_sub(value_1, value_2, result);
    }
}

static void s21_div_sub(s21_decimal *value_1, s21_decimal value_2, s21_decimal *result) {
    if (s21_is_less_or_equal(value_2, *value_1)) {
        s21_decimal buff = s21_create_decimal();
        s21_decimal_copy(value_2, &buff);
        int shift = -1;
        while (s21_is_less_or_equal(value_2, *value_1) && !s21_get_bit(value_2.bits[2], 31)) {
            s21_shift_right(&value_2, -1);
            shift++;
        }
        if (s21_get_bit(value_2.bits[2], 31)) shift++;
        s21_shift_right(&value_2, 1);
        s21_sub(*value_1, value_2, value_1);
        s21_set_bit(&result->bits[shift / 32], shift % 32);
        s21_div_sub(value_1, buff, result);
    }
}
