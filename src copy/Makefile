CC = g++
CPPFLAGS = -lgtest -std=c++17
WAEX = -Wall -Werror -Wextra

all: s21_matrix_oop.a

test: 
	@${CC} s21_matrix_oop.cpp s21_test_matrix_oop.cpp ${WAEX} ${CPPFLAGS} -o s21_test_matrix_oop
	@./s21_test_matrix_oop

%.o: %.cpp
	@${CC} -std=c++17 ${WAEX} -c $^

%.a: %.o
	@ar rcs $@ $^
	@ranlib $@

clean:
	@/bin/rm -rf *.o *.a s21_test_matrix_oop *.gcno *gcda report *.info s21_test_matrix_oop *.out

gcov_report: s21_matrix_oop.cpp s21_test_matrix_oop.cpp
	@$(CC) --coverage $^ ${CPPFLAGS} ${WAEX} -o s21_test_matrix_oop
	@./s21_test_matrix_oop
	@lcov -t "s21_test_matrix_oop" -o s21_test_matrix_oop.info -c -d ./
	@genhtml -o report s21_test_matrix_oop.info

style:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp

leaks: test
	valgrind --leak-check=full ./s21_test_matrix_oop