CC=g++ -std=c++17 -Wall -Werror -Wextra
CHECKFLAGS=-lgtest
CURRENTDIR = $(shell pwd)
BUILD_DIR=build
APP=Navigator
REPORTDIR=gcov_report
GCOV=--coverage
OPEN=
FILTER=
CPPCHECKFLAG = --enable=all --suppress=unusedStructMember --suppress=missingIncludeSystem --language=c++ --std=c++17
TEST_LIB:=./tests/tests_main.cc \
    ./lib/s21_graph.cc \
	./lib/s21_graph_algorithms.cc \
	./lib/ant_algorithm.cc \
	./lib/annealing_algorithm.cc \
	./lib/genetic_algorithm.cc
MVC:=main.cc \
	./lib/s21_graph.cc \
	./lib/s21_graph_algorithms.cc \
	./lib/ant_algorithm.cc \
	./lib/annealing_algorithm.cc \
	./lib/genetic_algorithm.cc \
	./view/console.cc \
	./controller/controller.cc \
	./model/navigator.cc

OS = $(shell uname)

ifeq ($(OS), Linux)
	CC+=-D OS_LINUX -g -s
	CHECKFLAGS+=-lpthread
	CHECK_LEAKS=CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt
	OPEN=xdg-open
	DIR=
	QTFLAGS=-spec linux-g++
else
	CC+=-D OS_MAC
	CHECK_LEAKS=CK_FORK=no leaks --atExit --
	FILTER=--gtest_filter=-*.Exception*
	OPEN=open
	DIR=/$(APP).app
	QTFLAGS=
endif

all: build

s21_graph.a:
	@$(CC) -c ./lib/s21_graph.cc -o ./s21_graph.o
	@ar rcs s21_graph.a ./s21_graph.o
	@rm -rf s21_graph.o

s21_graph_algorithms.a:
	@$(CC) -c ./lib/s21_graph_algorithms.cc -o ./s21_graph_algorithms.o
	@ar rcs s21_graph_algorithms.a ./s21_graph_algorithms.o
	@rm -rf s21_graph_algorithms.o

build: 
	@$(CC) $(MVC) -o $(APP)
	./$(APP)

rebuild: clean build

dvi:
	doxygen ./docs/Doxyfile
	$(OPEN) ./docs/html/index.html

tests: mostlyclean
	@$(CC) $(TEST_LIB) $(CHECKFLAGS) -o Test
	@./Test
	@rm -rf *.o *.a Test

gcov_report: mostlyclean
	@$(CC) $(TEST_LIB) -o Test $(GCOV) $(CHECKFLAGS)
	@./Test
	@lcov --no-external -c -d . -o $(APP).info
	@genhtml -o $(REPORTDIR) $(APP).info
	@$(OPEN) ./$(REPORTDIR)/index.html

check: style cppcheck leaks

style: 
	@cp ../materials/linters/.clang-format .
	clang-format -style=google -n */*.cc */*.h
	@rm .clang-format

cppcheck:
	@cppcheck $(CPPCHECKFLAG) */*.cc */*/*.cc *.cc  */*.h */*/*.h *.h

leaks: mostlyclean
	@$(CC) $(TEST_LIB) $(CHECKFLAGS) -o Test
	@$(CHECK_LEAKS) ./Test $(FILTER)
	@rm -rf *.o *.a Test

clean:
	@rm -rf *.o *.a *.out *.gcno *.gch *.gcda *.info *.tgz $(REPORTDIR) Test $(BUILD_DIR) $(APP_DIR) $(APP) ./docs/html

mostlyclean:
	@rm -rf *.o *.out *.gcno *.gch *.gcda *.info *.tgz $(REPORTDIR) Test
