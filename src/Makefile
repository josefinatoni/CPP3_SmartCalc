FLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -lstdc++
OS = $(shell uname)

ifeq ($(OS), Linux)
 CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm -lsubunit -lgtest
else
 CHECK_FLAGS = -lcheck -lm -lpthread -lgtest
endif

MODEL = SmartCalc/Model
VIEW = SmartCalc/View
CONTROLLER = SmartCalc/Controller
MAIN = main.cc
CC = $(MODEL)/model.cc $(CONTROLLER)/controller.cc
H = $(MODEL)/*.h $(CONTROLLER)/*.h
VIEWCC = $(VIEW)/*.cc
VIEWH = $(VIEW)/*.h
TEST = tests.cc

all: clean install dist dvi clean

s21_calc.a: s21_calc.o
	ar rcs s21_calc.a *.o
	ranlib *.a

s21_calc.o:
	gcc -c $(FLAGS) $(CC)

install: uninstall dvi
	mkdir build
	cp -rf SmartCalc/* build
	cd build && qmake SmartCalc.pro
	make -C build
	cd build && make clean
	open ./build/SmartCalc.app/Contents/MacOS/SmartCalc

uninstall:
	rm -rf build*
	make clean


open:
	open ./build/SmartCalc.app/Contents/MacOS/SmartCalc

run: install open

dvi:
	open readme.md

dist:
	tar -cvf build/calculator.tar build
	gzip build/calculator.tar
	mv build/calculator.tar.gz ./

test: clean s21_calc.a
	gcc $(FLAGS) $(CHECK_FLAGS) $(TEST) s21_calc.a -o test.out 
	./test.out

style:
	cp ../materials/linters/.clang-format .
	clang-format -n SmartCalc/Model/*.cc
	clang-format -n SmartCalc/Model/*.h
	clang-format -n SmartCalc/Controller/*.cc
	clang-format -n SmartCalc/Controller/*.h
	clang-format -n SmartCalc/View/*.cc
	clang-format -n SmartCalc/View/*.h
	rm .clang-format

gcov_report:
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) $(CC) $(CHECK_FLAGS) -o test
	./test
	lcov -t "test" --ignore-errors mismatch -o test.info --no-external -c -d  ./
	genhtml test.info -o report
	open report/index.html

style_correct:
	cp ../materials/linters/.clang-format .
	clang-format -i SmartCalc/Model/*.cc
	clang-format -i SmartCalc/Model/*.h
	clang-format -i SmartCalc/Controller/*.cc
	clang-format -i SmartCalc/Controller/*.h
	clang-format -i SmartCalc/View/*.cc
	clang-format -i SmartCalc/View/*.h
	rm .clang-format

leak: test
	CK_FORK=no leaks --atExit -- ./test.out

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

clean:
	@rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        s21_test \
        vtests_run \
		run \
		*.gz \

rebuild: clean all


