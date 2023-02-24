
#include "s21_decimal.h"

static int s21_fftd_error(float src, s21_decimal *dst);
static s21_decimal s21_parse_float(float src, int *exp_float, int *m_float);
static int s21_find_num_bits_0(int m_float);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int res = 0;
    if (dst == NULL) {
        res = 1;
    } else {
        *dst = s21_create_decimal();
        int minus = 0;
        s21_decimal f = *dst;
        if (src < 0) {
            minus = 1;
            src *= -1;
        }
        for (int i = 31; i >= 0; i--) {
            if (s21_get_bit(src, i)) {
                s21_set_bit(&f.bits[0], i);
            }
        }
        if (minus) s21_negate(f, &f);
        *dst = f;
    }
    return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int res = 0;
    if (dst == NULL) {
        res = 1;
    } else {
        if (s21_is_less(s21_decimal_int(INT_MAX), src) || s21_is_less(src, s21_decimal_int(INT_MIN))) {
            res = 1;
        } else {
            s21_truncate(src, &src);
            *dst = src.bits[0];
            if (!s21_is_positiv(src)) *dst *= -1;
        }
    }
    return res;
}

static int s21_find_num_bits_0(int m_float) {
    int num_bits_0 = 0;
    for (int k = 0; k < 32; k++) {
        if (s21_get_bit(m_float, k)) {
            num_bits_0 = 32 - k;
            break;
        }
    }
    return num_bits_0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int res = 0;
    *dst = s21_create_decimal();
    if (s21_fftd_error(src, dst)) {
        res = 1;
    } else {
        int exp = 0, minus = 0, exp_float = 0, m_float = 0, r = -23;
        if (src < 0) {
            src *= -1;
            minus = 1;
        }
        s21_decimal buff = s21_parse_float(src, &exp_float, &m_float);
        if (exp_float >= 96) res = 1;
        int num_bits_0 = s21_find_num_bits_0(buff.bits[0]);
        if (exp_float < 23) {
            r += exp_float;
            r += 32 - num_bits_0;
            if (r < 0) {
                s21_shift_right(&buff, 32 - num_bits_0);
            } else {
                s21_shift_right(&buff, 23 - exp_float);
            }
            while (r < 0) {
                if (exp < 28) {
                    exp++;
                    s21_mul_10(&buff);
                    s21_shift_right(&buff, 1);
                    r++;
                } else {
                    s21_shift_right(&buff, 1);
                    r++;
                }
            }
        } else {
            s21_shift_right(&buff, 23 - exp_float);
        }
        s21_create_new_exp(&buff, exp);
        if (minus) s21_negate(buff, &buff);
        *dst = buff;
    }
    return res;
}

static s21_decimal s21_parse_float(float src, int *exp_float, int *m_float) {
    s21_decimal buff = s21_create_decimal();
    union ft_b {
        float f;
        int g;
    } h;
    h.f = src;
    *exp_float = (h.g >> 23)&255;
    *m_float = h.g & 8388607;
    *exp_float -= 127;
    buff.bits[0] = *m_float & 8388607;
    s21_set_bit(&buff.bits[0], 23);
    return buff;
}

static int s21_fftd_error(float src, s21_decimal *dst) {
    int res = 0;
    if (dst == NULL) res = 1;
    if (isnan(src)) res = 1;
    if (src < 1e-28 && src > -1e-28) {
        res = 1;
        *dst = s21_create_decimal();
    }
    if (src > 79228162514264337593543950335.0) res = 1;
    if (src < -79228162514264337593543950335.0) res = 1;
    return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = 0;
    if (dst == NULL) {
        res = 1;
    } else {
        s21_correct_exp(&src);
        int minus = 1;
        long double result = 0, two = 1;
        if (!s21_is_positiv(src)) minus = -1;
        for (int k = 0; k < 96; k++) {
            if (s21_get_bit(src.bits[k / 32], k % 32)) result += two;
            two *= 2;
        }
        for (int k = 0; k < s21_exp_to_int(src); k++) {
            result /= 10.0;
        }
        *dst = minus * (float)result;
    }
    return res;
}
