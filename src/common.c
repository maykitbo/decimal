
#include "s21_decimal.h"

void s21_set_bit(int *x, int pos) {
    unsigned int mask = 1 << pos;
    *x |= mask;
}

int s21_get_bit(int x, int pos) {
    unsigned int mask = 1 << pos;
    int res = x & mask;
    if (res) res = 1;
    return res;
}

void s21_invers_bit(int *x, int pos) {
    unsigned int mask = 1 << pos;
    *x ^= mask;
}

int s21_exp_to_int(s21_decimal dec) {
    int exp = 0;
    int buff = 0;
    for (int i = 16; i < 24; i++) {
        buff = !!(s21_get_bit(dec.bits[3], i));
        exp += buff * pow(2, i-16);
    }
    return exp;
}

void s21_create_new_exp(s21_decimal *src, int new_exp) {
    int buff = 0;
    for (int i = 0; i < 8; i++) {
        buff = new_exp & 1 << i;
        if (buff) {
            s21_set_bit(&src->bits[3], (16 + i));
        } else {
            s21_set_bit(&src->bits[3], (16 + i));
            s21_invers_bit(&src->bits[3], (16 + i));
        }
    }
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int res = 0;
    if (result == NULL) res = 1;
    if (!res) {
        s21_decimal_copy(value, result);
        s21_invers_bit(&result->bits[3], 31);
    }
    return res;
}

s21_decimal s21_decimal_int(int num) {
    s21_decimal res = s21_create_decimal();
    s21_from_int_to_decimal(num, &res);
    return res;
}


s21_decimal s21_create_decimal() {
    s21_decimal result;
    result.bits[0] = 0;
    result.bits[1] = 0;
    result.bits[2] = 0;
    result.bits[3] = 0;
    return result;
}

int s21_is_positiv(s21_decimal src) {
    int res = 1;
    if (s21_get_bit(src.bits[3], 31)) res = 0;
    return res;
}

void s21_minus_nul(s21_decimal *src) {
    if (src->bits[0] == 0 && src->bits[1] == 0 && src->bits[2] == 0) {
        if (!s21_is_positiv(*src)) s21_negate(*src, src);
    }
}

void s21_correct_exp(s21_decimal *src) {
    if (s21_exp_to_int(*src) > 28) s21_create_new_exp(src, 28);
}

void s21_shift_right(s21_decimal *buff, int shift) {
    s21_decimal new = s21_create_decimal();
    if (shift < 0) {
        shift *= -1;
        for (int k = 0; k < 96; k++) {
            if (s21_get_bit(buff->bits[k / 32], k % 32))
                s21_set_bit(&new.bits[(k + shift) / 32], (k + shift) % 32);
        }
    } else {
        for (int k = 0, l = shift; k < 96 && l < 96; k++, l++) {
            if (s21_get_bit(buff->bits[l / 32], l % 32))
                s21_set_bit(&new.bits[(int)(k / 32)], k % 32);
        }
    }
    s21_decimal_copy(new, buff);
}

int s21_mul_10(s21_decimal *result) {
    int r = 0;
    s21_decimal buff = *result;
    if (s21_get_bit(result->bits[2], 31) || \
        s21_get_bit(result->bits[2], 30) || \
        s21_get_bit(result->bits[2], 29)) {
        r = 1;
    } else {
        s21_decimal one = *result, three = *result;
        s21_shift_right(&one, -1);
        s21_shift_right(&three, -3);
        *result = s21_create_decimal();
        r = s21_add(one, three, result);
        result->bits[3] = buff.bits[3];
    }
    if (r) *result = buff;
    return r;
}

void s21_decimal_copy(s21_decimal value, s21_decimal *result) {
    for (int k = 0; k < 4; k++) result->bits[k] = value.bits[k];
}
