CC = g++ -std=c++17 -Wall -Wextra -Werror -g
OS = $(shell uname)

CTEST_FLAGS = -lgtest -lgmock -pthread


ifeq ($(OS), Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit 
	LEAKS = CK_FORK=no valgrind  --leak-check=full  --track-origins=yes  ./test
else
	FLAGS = -lcheck
	LEAKS = leaks -atExit -- ./test
endif

all: clean

tests: clean
	touch ./test/cube.obj | cat ./test/cube.obj.txt > ./test/cube.obj
	$(CC) $(FLAGS) ./test/tests.cc ./file_reader/file_reader.cc ./conversionModel/conversionModel.cc -o tests $(CTEST_FLAGS)
	./tests



clang:
	clang-format -style=google -i ./*/*.cpp ./*/*.cc
	clang-format -style=google -i ./*/*.h

clean:
	rm -rf build* ./test/cube.obj tests


install: uninstall
	mkdir -p ../build
	qmake6 3DViewer/3DViewer.pro -o ../build/Makefile
	cd ../build; make > /dev/zero 2> /dev/zero
	mkdir -p ~/Applications ; cp -r ../build/3DViewer.app ~/Applications/3DViewer.app

uninstall: clean
	rm -rf ../build
	rm -rf ~/Applications/3DViewer.app


dvi:
	@open dvi.html

dist:
	@mkdir -p ./build_tar
	@tar -cvzf ./build_tar/3DViewer.tgz *


