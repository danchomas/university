CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CDEBUG = -g -Wall -Wextra -std=c11
GCOVFLAGS = --coverage
CHECKFLAGS = -pthread -lcheck_pic -lrt -lm -lsubunit

DECIMAL_SOURSES := $(wildcard *.c)
DECIMAL_OBJECTS := $(DECIMAL_SOURSES:.c=.o)

TEST_SOURCES := $(wildcard tests/*.c) 
TEST_OBJECTS := $(TEST_SOURCES:.c=.o)

all: clean s21_decimal.a test

test: clean s21_decimal.a build_test
	./test
build_test: $(TEST_OBJECTS) 
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o ./test -lm s21_decimal.a $(CHECKFLAGS)
s21_decimal.a: $(DECIMAL_OBJECTS)
	ar rcs s21_decimal.a $(DECIMAL_OBJECTS)
s21_decimal.o:
	$(CC) $(CFLAGS) -c $(DECIMAL_SOURSES)
s21_decimal.o_gcov:
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $(DECIMAL_SOURSES)
gcov_report: clean $(TEST_OBJECTS) s21_decimal.o_gcov
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o test_gcov $(TEST_OBJECTS) $(DECIMAL_OBJECTS) $(CHECKFLAGS)
	./test_gcov
	geninfo . -o ./coverage.info
	genhtml coverage.info -o gcov_report
debug: CFLAGS = $(CDEBUG)
debug: clean s21_decimal.a build_test
clang:
	cp ./../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	clang-format -n ./tests/*.c *.h
	clang-format -i *.c *.h
	clang-format -i ./tests/*.c *.h
	rm -f .clang-format
clean:
	rm -f *.o
	rm -f *.a
	rm -f test
	rm -f test_gcov
	rm -f ./*.gcno ./*.gcda ./*.info
	rm -rf ./gcov_report
	rm -rf tests/*.o