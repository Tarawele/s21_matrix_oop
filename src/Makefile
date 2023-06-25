CC = g++
CPPFLAGS = -lgtest -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra

all: test_matrix_oop.a

test: 
	@${CC} s21_matrix_oop.cpp test_matrix_oop.cpp ${CHECKFLAGS} ${CPPFLAGS} -o s21_matrix_main
	@./s21_matrix_main

%.o: %.cpp
	@${CC} -std=c++17 ${CHECKFLAGS} -c $^

%.a: %.o
	@ar rcs $@ $^
	@ranlib $@

clean:
	@/bin/rm -rf *.o *.a s21_matrix_main *.gcno *gcda report *.info s21_matrix_main *.out

gcov_report: test_matrix_oop.cpp
	@$(CC) --coverage $^ ${CPPFLAGS} ${CHECKFLAGS} -o s21_matrix_main
	@./s21_matrix_main
	@lcov -t "s21_matrix_main" -o s21_matrix_main.info -c -d ./
	@genhtml -o report s21_matrix_main.info

style:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp

leaks: test
	CK_FORK=no leaks --atExit -- ./s21_matrix_main