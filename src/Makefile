OBJ            =     matrix.o
SRCTEST        =     test.cc
CC             =     clang++ -std=c++17
LIBCHECK       =     -lgtest
TESTF          =     test.cc
TESTDIRECTORY  =     test
PUSHCOMMENT    =     "finish"
EXETEST        =     test
O              =     leaks
clean          =     clean
OS             =     $(shell uname -s)

.PHONY:
	clean rebuild test leaks all default

ifeq ($(OS), Linux)
	O = valgrind
endif


all: test gcov_report


$(clean):
	rm -rf *.txt valgrind test leaks *.dSYM *.out *.cfg
	rm -rf *.gcno *.gcda *.gcov *.info report
	rm -rf *.o *.a

cppcheck:
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem --suppress=unusedFunction $(SRC) $(TESTF) *.h

gcov_report: test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

main:
	$(CC)  main.cc -o main
	./main


leaks: $(LIB)
	$(CC) $(LIB) $(TESTF) $(LIBCHECK) -o leaks
	leaks -atExit -- ./leaks 

valgrind:
	$(CC) -g $(SRC) $(TESTF) $(LIBCHECK) -o valgrind
	valgrind -s --tool=memcheck --trace-children=yes --leak-check=full --show-leak-kinds=all ./valgrind

test: $(clean)
	$(CC) --coverage $(SRCTEST) -o $(EXETEST) $(LIBCHECK)
	./$(EXETEST)

memory: $(clean) $(O)

debug:
	$(CC) -g $(SRC) test.cpp -o debug.out

rebuild: clean all
