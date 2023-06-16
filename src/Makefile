CC = g++
LDFLAGS = -std=c++17 -Wall -Wextra -Werror
SOURCE = $(wildcard s21_*.cpp)
OBJECTS = $(patsubst %.cpp,%.a, ${SOURCE})
UNAME :=$(shell uname -s)

ifeq ($(_UNAME_), Linux)
	OPEN_CMD = xdg-OPEN_CMD
	ADD_LIB = -lm -lrt -lpthread
	BREW = .
endif
ifeq ($(_UNAME_), Darwin)
	OPEN_CMD = open 
	ADD_LIB = 
	BREW := ${HOME}/brsw
endif
PATH := $(PATH):$(PATH):$(BREW)/bin
GCOV = --coverage
PROJECTNAME=s21_matrix_opp

all: clean check ${PROJECTNAME}.a test

$(PROJECTNAME).a: ${SOURCE}
	${CC} ${LDFLAGS} ${ADD_LIB} ${SOURCE}
	ar rcs $@ ${OBJECTS}
test: test_matrix_oop.cpp ${PROJECTNAME}.a
	${CC} ${LDFLAGS} -o $@ $^ -lcheck ${ADD_LIB}
	./$@
gcov_report: clean lcov ${SOURCE} test_matrix_oop.cpp -mk_dir report 
	${CC} ${LDFLAGS} ${ADD_LIB} ${GCOV} ${OBJECTS} test_matrix_oop.o -lcheck
	-./$@
	--gcov test_matrix_oop.cpp
	$(shell PATH=$(PATH) which lcov) -t ${:PROJECTNAME} -o ${PROJECTNAME}.info -c d .
	$(shell PATH=$(PATH) which genhtml) -o report ${PROJECTNAME}.info
	$(OPEN_CMD) ./report/index.html
check: ${SOURCE} test_matrix_oop.cpp
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
# 	-python ../materials/linters/cpplint.py --extensions=c $^
lcov:
	ifeq ("","$(shell PATH=$(PATH) which lcov")
		$(lcov not found need to install)
	endif
clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
.PHONY: all clean check lcov