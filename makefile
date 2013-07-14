# Makefile to demonstrate how to build gtest

test: TestStuff
	TestStuff

# Important stuff here
# Normally, you will want to compile the framework specifically for each project
# but for here, we're just using the pre-compiled version already in /usr/lib/
#
# -lgtest brings in most of what we need
# -lpthread is the posix multithreaded library, and is required for gtest
# -lgtest_main simply includes a main, so we don't have to write one ourselves
#
# You can write your own main if you want to, but make sure not to link libgtest_main.a
# or you will have two main functions defined, which WILL cause compilation errors
TestStuff:
	g++ -pedantic -std=c++0x -Wall TestStuff.c++ -o TestStuff -lgtest -lgtest_main -pthread

clean:
	rm -rf *.o
	rm -f TestStuff