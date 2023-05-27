

all := $(shell find .  -iname "*.c")
TEST_FILES := array_stack_help.c calculate.c string_edit.c tests/main.c tests/test.c validate.c
	
all: install 
	./build/3DViewer

install:
	mkdir -p ./build
	cmake -S . -B ./build
	cmake open ./build/ 
	cmake --build ./build --target 3DViewer 
	
uninstall:
	rm -rf ./build

test:
	mkdir -p ./build
	cmake -S . -B ./build 
	cmake open ./build/ 
	cmake --build ./build --target test
	./build/test  || true

dvi:
	open readme.html

dist:
	git archive --format=tar.gz -o C8_3DViewer_v1.0 / develop

gcov_report: test
	mv ./build/CMakeFiles/test.dir/*.gcda . || true
	mv ./build/CMakeFiles/test.dir/*.gcno . || true
	gcov *.c 
	find ./ -type f -iname '*.gcda'
	lcov --directory ./ --capture --output-file postgresql.info --gcov-tool=gcov
	mkdir cov-report || true
	genhtml -o ./cov-report/ postgresql.info || true

cppcheck: $(all) 
	cppcheck  $^;

format: $(all)
	cp ../materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./cov-report
	-rm -rf ./report/ && rm -rf test.a.* && rm -rf main.a*
	-rm -rf lib* && rm -rf test
	-rm -rf test_*
	-rm -rf *tar.gz
