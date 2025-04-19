CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lm -pthread -lrt

SRC = s21_decimal.c comprasion_operators.c converters.c arithmetic_operators.c other_functions.c
OBJ = $(SRC:.c=.o)
OBJ_COV = $(SRC:.c=.gcov.o)
TEST_SRC = tests/tests.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_OBJ_COV = $(TEST_SRC:.c=.gcov.o)
TARGET = s21_decimal.a
TARGET_COV = s21_decimal_cov.a
TEST_BIN = tests/tests
GCOV_REPORT_DIR = gcov_report

.PHONY: all clean test gcov_report rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

$(TARGET_COV): $(OBJ_COV)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.gcov.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

test: $(TARGET_COV) $(TEST_OBJ_COV)
	rm -f *.gcov.o *.gcov.gcno
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) $(CHECK_LIBS)
	./$(TEST_BIN)
	rm -f $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) *.gcda *.gcno
	rm -f tests/*.gcov.o tests/*.gcov.gcno


gcov_report: $(TARGET_COV) $(TEST_OBJ_COV)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) $(CHECK_LIBS)
	./$(TEST_BIN)
	mkdir -p $(GCOV_REPORT_DIR)
	lcov -t "s21_decimal" -o $(GCOV_REPORT_DIR)/coverage.info -c -d .
	genhtml -o $(GCOV_REPORT_DIR) $(GCOV_REPORT_DIR)/coverage.info
	rm -f $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) *.gcda *.gcno *.gcov.o *.gcov.gcno
	rm -f */*.gcov.o */*.gcov.gcno


clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TARGET_COV) $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR)
	rm -f *.gcda *.gcno *.gcov *.gcov.o
	rm -f tests/*.gcda
	rm -f tests/*.gcov
	rm -f tests/*.gcov.o
	rm -f tests/*.gcno

rebuild: clean all
