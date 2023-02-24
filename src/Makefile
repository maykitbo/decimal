CC=gcc
SRC=alignig.c common.c arithmetic.c compare.c round.c transfer.c
OBJ=alignig.o common.o arithmetic.o compare.o round.o transfer.o
CFLAGS=-Wall -Werror -Wextra
TESTFLAGS=-lcheck -lm -lpthread -lgcov

all: s21_decimal.o test gcov_report s21_decimal.a

gcov_report: s21_decimal.o test
	gcovr -r. --html --html-details -o tests/coverage_report.html

test: lib.a s21_decimal_test.o $(OBJ)
	$(CC) $(FLAGS) lib.a s21_decimal_test.o $(OBJ) $(TESTFLAGS) -o test
	./test

lib.a: $(OBJ)
	ar rcs lib.a $(OBJ)

s21_decimal.a: s21_decimal_verter.o
	ar rcs s21_decimal.a $(OBJ)

s21_decimal_test.o: s21_decimal_test.c
	$(CC) $(CFLAGS) --coverage -c $^

s21_decimal.o: $(SRC)
	$(CC) $(CFLAGS) --coverage -c $^

s21_decimal_verter.o: $(SRC)
	$(CC) $(CFLAGS) -c $^

debug: $(SRC)
	$(CC) $(CFLAGS) $^ main.c
	./a.out

clean:
	rm -rf *.o
	rm -rf *.gc*
	rm -rf *.a
	rm -rf test
	rm -rf a.out
