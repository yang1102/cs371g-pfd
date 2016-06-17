# http://stackoverflow.com/questions/31176997/what-does-clang-check-do-without-analyze-option

FILES :=                              \
    PFD.c++                       \
    PFD.h                         \
    PFD.log                       \
    html                              \
    RunPFD.c++                    \
    RunPFD.in                     \
    RunPFD.out                    \
    TestPFD.c++                   \
    TestPFD.out                   
    # PFD-tests/sy6955-RunPFD.in   \
    # PFD-tests/sy6955-RunPFD.out  \
    # PFD-tests/sy6955-TestPFD.c++ \
    # PFD-tests/sy6955-TestPFD.out 

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

ifeq ($(CC), clang)
    CLANG-CHECK  := clang-check
    CXX          := clang++
else
    CXX          := g++-4.8
    GCOV         := gcov-4.8
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    GPROF        := gprof
    GPROFFLAGS   := -pg
endif

ifeq ($(CI), true)
    CLANG-FORMAT := clang-format
else
    CLANG-FORMAT := clang-format-3.4
endif

PFD-tests:
	git clone https://github.com/cs371g-summer-2016/PFD-tests.git

html: Doxyfile PFD.h PFD.c++ RunPFD.c++ TestPFD.c++
	doxygen Doxyfile

PFD.log:
	git log > PFD.log

Doxyfile:
	doxygen -g

RunPFD: PFD.h PFD.c++ RunPFD.c++
ifeq ($(CC), clang)
	$(CXX) $(CXXFLAGS) PFD.c++ RunPFD.c++ -o RunPFD
	-$(CLANG-CHECK) -extra-arg=-std=c++11          PFD.c++     --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze PFD.c++     --
	-$(CLANG-CHECK) -extra-arg=-std=c++11          RunPFD.c++  --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze RunPFD.c++  --
else
	$(CXX) $(CXXFLAGS) $(GPROFFLAGS) PFD.c++ RunPFD.c++ -o RunPFD
endif

RunPFD.tmp: RunPFD
	./RunPFD < RunPFD.in > RunPFD.tmp
	diff RunPFD.tmp RunPFD.out
ifeq ($(CC), gcc)
	$(GPROF) ./RunPFD < RunPFD.in > RunPFD.tmp
endif
	cat RunPFD.tmp

TestPFD: PFD.h PFD.c++ TestPFD.c++
ifeq ($(CC), clang)
	$(CXX) $(CXXFLAGS) PFD.c++ TestPFD.c++ -o TestPFD $(LDFLAGS)
	-$(CLANG-CHECK) -extra-arg=-std=c++11          PFD.c++     --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze PFD.c++     --
	-$(CLANG-CHECK) -extra-arg=-std=c++11          TestPFD.c++ --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze TestPFD.c++ --
else
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) PFD.c++ TestPFD.c++ -o TestPFD $(LDFLAGS)
endif

TestPFD.tmp: TestPFD
	$(VALGRIND) ./TestPFD                                       >  TestPFD.tmp 2>&1
ifeq ($(CC), gcc)
	$(GCOV) -b PFD.c++     | grep -A 5 "File 'PFD.c++'"     >> TestPFD.tmp
	$(GCOV) -b TestPFD.c++ | grep -A 5 "File 'TestPFD.c++'" >> TestPFD.tmp
endif
	cat TestPFD.tmp

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.plist
	rm -f  PFD.log
	rm -f  Doxyfile
	rm -f  gmon.out
	rm -f  RunPFD
	rm -f  RunPFD.tmp
	rm -f  TestPFD
	rm -f  TestPFD.tmp
	rm -rf PFD-tests
	rm -rf html
	rm -rf latex

config:
	git config -l

format:
	$(CLANG-FORMAT) -i PFD.c++
	$(CLANG-FORMAT) -i PFD.h
	$(CLANG-FORMAT) -i RunPFD.c++
	$(CLANG-FORMAT) -i TestPFD.c++

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: html PFD.log RunPFD.tmp TestPFD.tmp PFD-tests check
