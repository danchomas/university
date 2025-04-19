CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lm -pthread -lrt

SRC = my_matrix.c
OBJ = $(SRC:.c=.o)
OBJ_COV = $(SRC:.c=.gcov.o)
TEST_SRC = tests/s21_test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_OBJ_COV = $(TEST_SRC:.c=.gcov.o)
TARGET = my_matrix.a
TARGET_COV = my_matrix_cov.a
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
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) $(CHECK_LIBS)
	./$(TEST_BIN)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TARGET_COV) $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR)
	rm -f *.gcda *.gcno *.gcov *.gcov.o
	rm -f tests/*.gcda
	rm -f tests/*.gcov
	rm -f tests/*.gcov.o
	rm -f tests/*.gcno

rebuild: clean all