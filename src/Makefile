CC=gcc
FLAGS=-g -Wall -Wextra -Werror -std=c11 -pedantic
CFLAGS=-c $(FLAGS)
TEST_FLAGS=-lcheck -lgcov

#SRCS
SRC_MATRIX=s21_create_matrix.c s21_calc_complements.c s21_determinant.c s21_eq_matrix.c  \
s21_mult_matrix.c s21_mult_number.c s21_remove_matrix.c s21_sub_matrix.c \
s21_sum_matrix.c s21_transpose.c s21_inverse_matrix.c s21_util.c 
SRC_TEST=s21_test.c

#OBJECTS
OBJ=$(notdir $(SRC_MATRIX:.c=.o))
OBJ_TEST=$(notdir $(SRC_TEST:.c=.o))

#DIRECTORY
OBJ_DIR=objects
SRC_DIR=s21_matrix
TEST_DIR=s21_test
UTIL_DIR=util

#INCLUDES
INCLUDE=s21_matrix.h s21_util.h

vpath %.c $(SRC_DIR) $(UTIL_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(UTIL_DIR)

.PHONY: all clean test gcov_report

all: gcov_report test s21_matrix.a

%.o: %.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

test: $(OBJ_TEST) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ) $(OBJ_TEST)) $(TEST_FLAGS) -o test
	./test

s21_matrix.a: $(INCLUDE) $(OBJ)
	ar rcs $@  $(addprefix $(OBJ_DIR)/, $(OBJ))
	ranlib $@

gcov_report:CFLAGS += -coverage
gcov_report: clean test
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;

valgrind: test
	valgrind --leak-check=full ./test

clean:
	rm -rf $(OBJ_DIR) report s21_matrix.a test gcov_report.info
