
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

#define FALSE 0
#define TRUE 1

#define DECIMAL_MAX 79228162514264337593543950335.0
#define DECIMAL_MIN 1e-28

START_TEST(decimal_add_new) {
    for (int k = 0; k < 50; k++) {
        s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), c = s21_create_decimal();
        float x = -888e12, y = 333e12, r = 0.0;
        x += k * 123e11;
        y -= k * 321e11;
        s21_from_float_to_decimal(x, &a);
        s21_from_float_to_decimal(y, &b);
        s21_add(a, b, &c);
        s21_from_decimal_to_float(c, &r);
        ck_assert_float_eq(r, x + y);
    }
}

START_TEST(int_decimal_int) {
    s21_decimal a = s21_create_decimal();
    int i = INT32_MAX, res = 0;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i  = INT32_MIN;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i = 0;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i = -123456;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i = 987654;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i = -1;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);

    i = 2;
    s21_from_int_to_decimal(i, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(float_decimal_float) {
    s21_decimal a = s21_create_decimal();
    float f = 1e-10, res = 0;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -3e-25;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = 0;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = 7.9e28;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -7.9e28;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = 123456.789;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -23e9;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = 123e-5;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -0.01234567898766;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = 33333333333;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -0;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = DECIMAL_MIN;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);

    f = -DECIMAL_MIN;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_cycle_1) {
    float f = 79.11e27, res = 0;
    for (int k = 0; k < 30; k++) {
        s21_decimal a = s21_create_decimal();
        s21_from_float_to_decimal(f, &a);
        s21_from_decimal_to_float(a, &res);
        ck_assert_float_eq(f, res);
        f -= 79.11e27 / 16.0;
    }
}
END_TEST

START_TEST(float_decimal_float_cycle_2) {
    float f = 5e-21, res = 0;
    for (int k = 0; k < 30; k++) {
        s21_decimal a = s21_create_decimal();
        s21_from_float_to_decimal(f, &a);
        s21_from_decimal_to_float(a, &res);
        ck_assert_float_eq(f, res);
        f += 4e-21;
    }
}
END_TEST

START_TEST(float_decimal_error) {
    s21_decimal a = s21_create_decimal();
    float f = DECIMAL_MAX + 1;
    int r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
    f = -DECIMAL_MAX - 1;
    r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
    f = 1e-29;
    r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
    f = -1e-29;
    r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
    f = -1e-45;
    r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
    f = 1e30;
    r = s21_from_float_to_decimal(f, &a);
    ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(decimal_int_) {
    s21_decimal a = s21_create_decimal();
    float f = 123.456;
    s21_from_float_to_decimal(f, &a);
    int res = 0;
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, 123);

    f = 0.45;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, 0);

    f = -147.777;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, -147);

    f = 1234569.9;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, 1234569);

    f = -9.999;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, -9);

    f = -1e-10;
    s21_from_float_to_decimal(f, &a);
    s21_from_decimal_to_int(a, &res);
    ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(decimal_int_error) {
    s21_decimal a = s21_create_decimal();
    float f = 1e20;
    s21_from_float_to_decimal(f, &a);
    int i = 0;
    int res = s21_from_decimal_to_int(a, &i);
    ck_assert_int_eq(res, 1);

    f = -1.5e16;
    s21_from_float_to_decimal(f, &a);
    res = s21_from_decimal_to_int(a, &i);
    ck_assert_int_eq(res, 1);

    f = (float)INT32_MAX + 390;
    i = 0;
    s21_from_float_to_decimal(f, &a);
    res = s21_from_decimal_to_int(a, &i);
    ck_assert_int_eq(res, 1);

    f = (float)INT32_MIN - 500.0;
    s21_from_float_to_decimal(f, &a);
    res = s21_from_decimal_to_int(a, &i);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(decimal_floor) {
    s21_decimal a = s21_create_decimal();
    float f = 123.456;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    float res = 0;
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = -0.0123;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = 123;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = 0;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = -0;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = 1e15;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = 1234.55;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));

    f = 888;
    s21_from_float_to_decimal(f, &a);
    s21_floor(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, floor(f));
}
END_TEST

START_TEST(decimal_round) {
    s21_decimal a = s21_create_decimal();
    float f = 123.456;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    float res = 0;
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = -123.456;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = 567;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = -0.99;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = 45.01;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = 4.5;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = -3.5;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));

    f = 0;
    s21_from_float_to_decimal(f, &a);
    s21_round(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, round(f));
}
END_TEST

START_TEST(decimal_truncate) {
    s21_decimal a = s21_create_decimal();
    float f = 123.456;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    float res = 0;
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, 123);

    f = -123.456;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -123);

    f = 0;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, 0);

    f = -999;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -999);

    f = 123456.9;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, 123456);

    f = 3.9999;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, 3);

    f = -898.01;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -898);

    f = -9.98;
    s21_from_float_to_decimal(f, &a);
    s21_truncate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -9);
}
END_TEST

START_TEST(decimal_negate) {
    s21_decimal a = s21_create_decimal();
    float f = -123.456;
    s21_from_float_to_decimal(f, &a);
    s21_negate(a, &a);
    float res = 0;
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -f);

    f = 8;
    s21_from_float_to_decimal(f, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -f);

    f = -1e9;
    s21_from_float_to_decimal(f, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -f);

    f = 876.54321;
    s21_from_float_to_decimal(f, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_float(a, &res);
    ck_assert_float_eq(res, -f);

    int i = INT32_MAX, r = 0;
    s21_from_int_to_decimal(i, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_int(a, &r);
    ck_assert_int_eq(r, -i);

    i = INT32_MIN + 1;
    s21_from_int_to_decimal(i, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_int(a, &r);
    ck_assert_int_eq(r, -i);

    i = 333;
    s21_from_int_to_decimal(i, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_int(a, &r);
    ck_assert_int_eq(r, -i);

    i = -90909;
    s21_from_int_to_decimal(i, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_int(a, &r);
    ck_assert_int_eq(r, -i);

    i = 0;
    s21_from_int_to_decimal(i, &a);
    s21_negate(a, &a);
    s21_from_decimal_to_int(a, &r);
    ck_assert_int_eq(r, -i);
}
END_TEST

START_TEST(decimal_mul_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12309;
    float y = 0;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1e-5;
    float y = -0.005;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e8;
    float y = -1e-5;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -2e7;
    float y = 3e8;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -888;
    float y = -0.0001;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_7) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12e-17;
    float y = 33;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_8) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -12e20;
    float y = -0.00001;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x * y);
}
END_TEST

START_TEST(decimal_mul_error_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1e20;
    float y = 2e17;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0.0);
    ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(decimal_mul_error_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e-14;
    float y = -2e-16;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0.0);
    ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(decimal_mul_error_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 2345e17;
    float y = -0.1e13;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0.0);
    ck_assert_int_eq(r, 2);
}
END_TEST

START_TEST(decimal_mul_error_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -3e-20;
    float y = -18e-21;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_mul(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0.0);
    ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(decimal_mod_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12309;
    float y = 1e10;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1e-5;
    float y = -0.005;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e2;
    float y = -4e-1;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -2e7;
    float y = 3e8;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -888;
    float y = -0.0001;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, fmod(x, y));
}
END_TEST

START_TEST(decimal_mod_error_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -888;
    float y = -0;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_mod(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 3);
}
END_TEST

START_TEST(decimal_div_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq_tol(result, x / y, 1e-2);
}
END_TEST

START_TEST(decimal_div_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 908070;
    float y = 0.89;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
}
END_TEST

START_TEST(decimal_div_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 0.1;
    float y = 123456;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
}
END_TEST

START_TEST(decimal_div_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e20;
    float y = -99;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
}
END_TEST

START_TEST(decimal_div_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12;
    float y = -88888;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
}
END_TEST

START_TEST(decimal_div_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -546;
    float y = 9;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
}
END_TEST

START_TEST(decimal_div_7) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234567890.1;
    float y = 0.000123;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    int r = s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x / y);
    ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(decimal_div_8) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -2e-20;
    float y = -45e-24;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_div(a, b, &res);
    int r = s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq_tol(result, x / y, 1e-2);
    ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(decimal_div_error_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 3e27;
    float y = 0.0012;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(decimal_div_error_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 3e27;
    float y = -0.0045678;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 2);
}
END_TEST

START_TEST(decimal_div_error_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -18e-8;
    float y = 0;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 3);
}
END_TEST

START_TEST(decimal_div_error_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -18e-8;
    float y = -1e22;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(decimal_add_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 0.1;
    float y = 123456;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e20;
    float y = -99;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12;
    float y = -88888;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -546;
    float y = 9;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x + y);
}
END_TEST

START_TEST(decimal_add_error_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 3e28;
    float y = 6e28;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(decimal_add_error_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -4e28;
    float y = -7e28;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 2);
}
END_TEST

START_TEST(decimal_sub_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 1234.9;
    float y = 0.44;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 0.1;
    float y = 123456;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -1e20;
    float y = -99;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 12;
    float y = -88888;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -546;
    float y = 9;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, x - y);
}
END_TEST

START_TEST(decimal_sub_error_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = 5.5e28;
    float y = -6.6e28;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(decimal_sub_error_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal(), res = s21_create_decimal();
    float x = -7.213e28;
    float y = 4.77e28;
    float result = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    int r = s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &result);
    ck_assert_float_eq(result, 0);
    ck_assert_int_eq(r, 2);
}
END_TEST

START_TEST(decimal_compare_1) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = -7.213e28;
    float y = 4.77e28;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less(a, b), TRUE);
    ck_assert_int_eq(s21_is_greater(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);
}
END_TEST

START_TEST(decimal_compare_2) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = 0;
    float y = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    s21_negate(a, &a);
    ck_assert_int_eq(s21_is_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_equal(b, a), TRUE);
    ck_assert_int_eq(s21_is_not_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);
}
END_TEST

START_TEST(decimal_compare_3) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = 1e-26;
    float y = 9e-27;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(decimal_compare_4) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = -4e20;
    float y = -5e20;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(decimal_compare_5) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = -4e-20;
    float y = -5e20;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(decimal_compare_6) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = 1234567;
    float y = 5.5e-11;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(decimal_compare_7) {
    s21_decimal a = s21_create_decimal(), b = s21_create_decimal();
    float x = 0;
    float y = 0;
    s21_from_float_to_decimal(x, &a);
    s21_from_float_to_decimal(y, &b);
    ck_assert_int_eq(s21_is_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_not_equal(a, b), FALSE);
    ck_assert_int_eq(s21_is_less(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater(a, b), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);
}
END_TEST

START_TEST(compare_less) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);

    s21_negate(dst1, &dst1);
    s21_negate(dst2, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);

    s21_negate(dst1, &dst1);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);
}
END_TEST

START_TEST(compare_greater) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);

    s21_negate(dst1, &dst1);
    s21_negate(dst2, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);

    s21_negate(dst1, &dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);
}
END_TEST

START_TEST(compare_less_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), FALSE);
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);

    s21_negate(dst1, &dst1);
    s21_negate(dst2, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE);

    s21_negate(dst1, &dst1);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE);
}
END_TEST

START_TEST(compare_greater_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);

    s21_negate(dst1, &dst1);
    s21_negate(dst2, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE);

    s21_negate(dst1, &dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), TRUE);
}
END_TEST

START_TEST(compare_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);
}
END_TEST

START_TEST(compare_equal_null) {
    s21_decimal dst1, dst2;
    s21_from_int_to_decimal(0, &dst1);
    s21_from_int_to_decimal(0, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);
}
END_TEST

START_TEST(compare_not_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), TRUE);

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);
}
END_TEST

START_TEST(s21_add_1) {
    s21_decimal src1 = s21_create_decimal(), src2 = s21_create_decimal();
    int a = -1234;
    float b = 1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1232.766;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_2) {
    s21_decimal src1 = s21_create_decimal(), src2 = s21_create_decimal();
    int a = -1234;
    float b = -1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a + b;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_3) {
    s21_decimal src1 = s21_create_decimal(), src2 = s21_create_decimal();
    float a = DECIMAL_MAX - 1;
    int b = 5;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res = s21_create_decimal();
    s21_add(src1, src2, &res);
}
END_TEST

START_TEST(s21_add_4) {
    s21_decimal src1 = s21_create_decimal(), src2 = s21_create_decimal();
    float a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_5) {
    s21_decimal src1 = s21_create_decimal(), src2 = s21_create_decimal();
    int a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_7) {
    s21_decimal src1, src2;
    float a = -9403;
    float b = 0.00234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -9402.99766;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_8) {
    s21_decimal src1, src2;
    int a = -9403;
    int b = 234;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -9169;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_9) {
    s21_decimal src1, src2;
    float a = -940.3;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -940.299766;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_10) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -0.940066;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_11) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 2.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a + b;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_13) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -112.9637;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_14) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1052.0234;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_15) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -12140;
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_16) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_origin = a + b;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_create_decimal();
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_1) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = 9201;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_2) {
    s21_decimal src1, src2;
    int a = 9403;
    float b = 202.098;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 9200.902;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_3) {
    s21_decimal src1, src2;
    float a = -9403;
    float b = 202.098;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_4) {
    s21_decimal src1, src2;
    float a = 9403.0;
    float b = 202.09e8;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -20208990597;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_5) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    float b = 202.09e8;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -20208059700;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_6) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    int b = -202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_8) {
    s21_decimal src1, src2;
    float a = -94;
    float b = -202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_create_decimal();
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_9) {
    s21_decimal src1, src2;
    src1.bits[3] = 0b00000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000110011011110000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000001000101000111010110;
    s21_decimal result_origin;
    result_origin.bits[3] = 0b00000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000001000111110001111101010;
    s21_decimal result_our = s21_create_decimal();
    s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_mul_1) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = 189940600;
    s21_decimal res_od = s21_create_decimal();
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_2) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    float b = 9403.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 884164090000;
    s21_decimal res_od = s21_create_decimal();
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_3) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = 1899406;
    s21_decimal res_od = s21_create_decimal();
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_4) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 2;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -65536;
    s21_decimal res_od = s21_create_decimal();
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_5) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 32768;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -1073741824;
    s21_decimal res_od = s21_create_decimal();
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mod_1) {
    s21_decimal src1, src2;
    int a = 3;
    int b = 2;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_2) {
    s21_decimal src1, src2;
    int a = -98765;
    int b = 1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_3) {
    s21_decimal src1, src2;
    int a = 30198;
    int b = 20210;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_4) {
    s21_decimal src1, src2;
    int a = -98765;
    int b = -1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_5) {
    s21_decimal src1, src2;
    int a = 98765;
    int b = 127234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_6) {
    s21_decimal src1, src2;
    int a = 342576;
    int b = 1542134;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_7) {
    s21_decimal src1, src2;
    float a = 1.2;
    float b = 0.3;
    float res_origin = fmod(a, b);
    float res = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_8) {
    s21_decimal src1, src2;
    float a = 1.2;
    int b = 3;
    float res_origin = fmod(a, b);
    float res = 0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_mod = s21_create_decimal();
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST

START_TEST(s21_div_1) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = 4654.950495049504950495049505;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_2) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 2;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -16384;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_3) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    float b = -2020.29;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 465.4282306005573457275935633;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_4) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    float b = 2020.29;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -465.4282306005573457275935633;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_5) {
    s21_decimal src1, src2;
    float a = -9403.0e20;
    float b = 2.28e17;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_6) {
    s21_decimal src1, src2;
    float a = -0.9;
    float b = 30.323;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_7) {
    s21_decimal src1, src2;
    float a = -0.9e3;
    float b = 30.32;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_8) {
    s21_decimal src1, src2;
    float a = -0.9e3;
    int b = 30;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_9) {
    s21_decimal src1, src2;
    float a = -0.9;
    float b = 0.000076;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_create_decimal();
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_trun_1) {
    s21_decimal src1;
    src1.bits[3] = 0x000A0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    s21_decimal res_od = s21_create_decimal();
    s21_truncate(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_3) {
    s21_decimal src1;
    src1.bits[3] = 0x80000000;
    src1.bits[2] = 0x0;
    src1.bits[1] = INT_MIN + 1;
    src1.bits[0] = INT_MIN + 1;
    s21_decimal result;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = INT_MIN + 1;
    result.bits[0] = INT_MIN + 1;
    s21_decimal res_od = s21_create_decimal();
    s21_truncate(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_8) {
    s21_decimal src1;
    src1.bits[0] = 0b01111000101001111011110011000110;
    src1.bits[1] = 0b10011111111111001111101010000100;
    src1.bits[2] = 0b00011111111010011010111101101101;
    src1.bits[3] = 0b00000000000111000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_create_decimal();
    s21_truncate(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_negate_1) {
    int a = 10;
    int res_a = 0;
    s21_decimal src;
    s21_from_int_to_decimal(a, &src);
    s21_decimal res = s21_create_decimal();
    s21_negate(src, &res);
    s21_from_decimal_to_int(res, &res_a);
    ck_assert_int_eq(-10, res_a);
}
END_TEST

START_TEST(s21_negate_2) {
    float a = 10.12345;
    float res_a = 0;
    s21_decimal src;
    s21_from_float_to_decimal(a, &src);
    s21_decimal res = s21_create_decimal();
    s21_negate(src, &res);
    s21_from_decimal_to_float(res, &res_a);
    ck_assert_float_eq(-10.12345, res_a);
}
END_TEST

START_TEST(s21_negate_3) {
    float a = 10.1234e5;
    float res_a = 0;
    s21_decimal src;
    s21_from_float_to_decimal(a, &src);
    s21_decimal res = s21_create_decimal();
    s21_negate(src, &res);
    s21_from_decimal_to_float(res, &res_a);
    ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
    s21_decimal val;

    s21_from_int_to_decimal(0, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-128, &val);
    ck_assert_int_eq(val.bits[0], 128);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);

    s21_from_int_to_decimal(127, &val);
    ck_assert_int_eq(val.bits[0], 127);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-2147483648, &val);
    ck_assert_int_eq(val.bits[0], -2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);

    s21_from_int_to_decimal(2147483647, &val);
    ck_assert_int_eq(val.bits[0], 2147483647);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
    s21_decimal val;
    s21_from_float_to_decimal(-2.1474836E+09, &val);
    ck_assert_int_eq(val.bits[0], -2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
    s21_decimal val;
    s21_from_float_to_decimal(1.02E+09, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
    s21_decimal val;
    float a = 1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
    s21_decimal val;
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
    s21_decimal val;
    float a = 0.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
    s21_decimal src;
    int result = 0, number = 0;
    src.bits[0] = INT_MAX;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_float_eq(number, 2147483647);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
    s21_decimal src;
    int result = 0, number = 0;
    src.bits[0] = 133141;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, 133141);
    ck_assert_int_eq(result, 0);
}
END_TEST


START_TEST(s21_from_decimal_to_float_3) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.bits[0] = 0XFFFFFF;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, 16777215);
    ck_assert_int_eq(result, 0);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Suite");

    TCase *tc1_1 = tcase_create("tests");
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, decimal_add_new);
    tcase_add_test(tc1_1, int_decimal_int);
    tcase_add_test(tc1_1, float_decimal_float);
    tcase_add_test(tc1_1, float_decimal_float_cycle_1);
    tcase_add_test(tc1_1, float_decimal_float_cycle_2);
    tcase_add_test(tc1_1, float_decimal_error);
    tcase_add_test(tc1_1, decimal_int_);
    tcase_add_test(tc1_1, decimal_int_error);
    tcase_add_test(tc1_1, decimal_floor);
    tcase_add_test(tc1_1, decimal_round);
    tcase_add_test(tc1_1, decimal_truncate);
    tcase_add_test(tc1_1, decimal_negate);
    tcase_add_test(tc1_1, decimal_mul_1);
    tcase_add_test(tc1_1, decimal_mul_2);
    tcase_add_test(tc1_1, decimal_mul_3);
    tcase_add_test(tc1_1, decimal_mul_4);
    tcase_add_test(tc1_1, decimal_mul_5);
    tcase_add_test(tc1_1, decimal_mul_6);
    tcase_add_test(tc1_1, decimal_mul_7);
    tcase_add_test(tc1_1, decimal_mul_8);
    tcase_add_test(tc1_1, decimal_mul_error_1);
    tcase_add_test(tc1_1, decimal_mul_error_2);
    tcase_add_test(tc1_1, decimal_mul_error_3);
    tcase_add_test(tc1_1, decimal_mul_error_4);
    tcase_add_test(tc1_1, decimal_mod_1);
    tcase_add_test(tc1_1, decimal_mod_2);
    tcase_add_test(tc1_1, decimal_mod_3);
    tcase_add_test(tc1_1, decimal_mod_4);
    tcase_add_test(tc1_1, decimal_mod_5);
    tcase_add_test(tc1_1, decimal_mod_6);
    tcase_add_test(tc1_1, decimal_mod_error_1);
    tcase_add_test(tc1_1, decimal_div_1);
    tcase_add_test(tc1_1, decimal_div_2);
    tcase_add_test(tc1_1, decimal_div_3);
    tcase_add_test(tc1_1, decimal_div_4);
    tcase_add_test(tc1_1, decimal_div_5);
    tcase_add_test(tc1_1, decimal_div_6);
    tcase_add_test(tc1_1, decimal_div_7);
    tcase_add_test(tc1_1, decimal_div_8);
    tcase_add_test(tc1_1, decimal_div_error_1);
    tcase_add_test(tc1_1, decimal_div_error_2);
    tcase_add_test(tc1_1, decimal_div_error_3);
    tcase_add_test(tc1_1, decimal_div_error_4);
    tcase_add_test(tc1_1, decimal_add_1);
    tcase_add_test(tc1_1, decimal_add_2);
    tcase_add_test(tc1_1, decimal_add_3);
    tcase_add_test(tc1_1, decimal_add_4);
    tcase_add_test(tc1_1, decimal_add_5);
    tcase_add_test(tc1_1, decimal_add_6);
    tcase_add_test(tc1_1, decimal_add_error_1);
    tcase_add_test(tc1_1, decimal_add_error_2);
    tcase_add_test(tc1_1, decimal_sub_1);
    tcase_add_test(tc1_1, decimal_sub_2);
    tcase_add_test(tc1_1, decimal_sub_3);
    tcase_add_test(tc1_1, decimal_sub_4);
    tcase_add_test(tc1_1, decimal_sub_5);
    tcase_add_test(tc1_1, decimal_sub_6);
    tcase_add_test(tc1_1, decimal_sub_error_1);
    tcase_add_test(tc1_1, decimal_sub_error_2);
    tcase_add_test(tc1_1, decimal_compare_1);
    tcase_add_test(tc1_1, decimal_compare_2);
    tcase_add_test(tc1_1, decimal_compare_3);
    tcase_add_test(tc1_1, decimal_compare_4);
    tcase_add_test(tc1_1, decimal_compare_5);
    tcase_add_test(tc1_1, decimal_compare_6);
    tcase_add_test(tc1_1, decimal_compare_7);

    tcase_add_test(tc1_1, compare_less);
    tcase_add_test(tc1_1, compare_greater);
    tcase_add_test(tc1_1, compare_less_or_equal);
    tcase_add_test(tc1_1, compare_greater_or_equal);
    tcase_add_test(tc1_1, compare_equal);
    tcase_add_test(tc1_1, compare_equal_null);
    tcase_add_test(tc1_1, compare_not_equal);
    tcase_add_test(tc1_1, s21_add_1);
    tcase_add_test(tc1_1, s21_add_2);
    tcase_add_test(tc1_1, s21_add_3);
    tcase_add_test(tc1_1, s21_add_4);
    tcase_add_test(tc1_1, s21_add_5);
    tcase_add_test(tc1_1, s21_add_7);
    tcase_add_test(tc1_1, s21_add_8);
    tcase_add_test(tc1_1, s21_add_9);
    tcase_add_test(tc1_1, s21_add_10);
    tcase_add_test(tc1_1, s21_add_11);
    tcase_add_test(tc1_1, s21_add_13);
    tcase_add_test(tc1_1, s21_add_14);
    tcase_add_test(tc1_1, s21_add_15);
    tcase_add_test(tc1_1, s21_add_16);
    tcase_add_test(tc1_1, s21_sub_1);
    tcase_add_test(tc1_1, s21_sub_2);
    tcase_add_test(tc1_1, s21_sub_3);
    tcase_add_test(tc1_1, s21_sub_4);
    tcase_add_test(tc1_1, s21_sub_5);
    tcase_add_test(tc1_1, s21_sub_6);
    tcase_add_test(tc1_1, s21_sub_8);
    tcase_add_test(tc1_1, s21_sub_9);
    tcase_add_test(tc1_1, s21_mul_1);
    tcase_add_test(tc1_1, s21_mul_2);
    tcase_add_test(tc1_1, s21_mul_3);
    tcase_add_test(tc1_1, s21_mul_4);
    tcase_add_test(tc1_1, s21_mul_5);
    tcase_add_test(tc1_1, s21_mod_1);
    tcase_add_test(tc1_1, s21_mod_2);
    tcase_add_test(tc1_1, s21_mod_3);
    tcase_add_test(tc1_1, s21_mod_4);
    tcase_add_test(tc1_1, s21_mod_5);
    tcase_add_test(tc1_1, s21_mod_6);
    tcase_add_test(tc1_1, s21_mod_7);
    tcase_add_test(tc1_1, s21_mod_8);
    tcase_add_test(tc1_1, s21_div_1);
    tcase_add_test(tc1_1, s21_div_2);
    tcase_add_test(tc1_1, s21_div_3);
    tcase_add_test(tc1_1, s21_div_4);
    tcase_add_test(tc1_1, s21_div_5);
    tcase_add_test(tc1_1, s21_div_6);
    tcase_add_test(tc1_1, s21_div_7);
    tcase_add_test(tc1_1, s21_div_8);
    tcase_add_test(tc1_1, s21_div_9);
    tcase_add_test(tc1_1, s21_trun_1);
    tcase_add_test(tc1_1, s21_trun_3);
    tcase_add_test(tc1_1, s21_trun_8);
    tcase_add_test(tc1_1, s21_negate_1);
    tcase_add_test(tc1_1, s21_negate_2);
    tcase_add_test(tc1_1, s21_negate_3);
    tcase_add_test(tc1_1, s21_from_int_to_decimal_1);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_3);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_5);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_7);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_8);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_9);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_3);

    SRunner *sr = srunner_create(s1);

    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);

    return 0;
}
