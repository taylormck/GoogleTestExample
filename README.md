Google Test Example
============

A demonstration of how to use the Google C++ Testing Framework

Introduction
------------
Hi, I'm Taylor, and I'm a former student of [Professor Glenn Downing](https://www.cs.utexas.edu/users/downing/drupal/).
I've been asked to write a quick tutorial for the Google C++ Testing Framework.
Called gtest for short, this framework is a friendlier and more up to date unit testing framework for C++ than CppUnit.
Some of the reasons I prefer gtest to Cppunit are:
- No more compiler warnings due to CppUnit's autopointers
- A prettier, more organized, and more descriptive interface
- Integrates with Eclipse CDT (my preferred IDE), and several other popular IDE's
- No more need to list all your tests at the bottom of a class definition, simply make the tests and they will run
- Text fixtures allow us to reuse set up code instead of writing it again for every test that needs it
- Expectations allow us to check conditions and report failure without stopping the test early
- A few helpful macros allow us to test for complex equality between floating point numbers and c strings
- Reports the time used during each test
- Unlike CppUnit, I've been able to get this working on Windows
- Since it prints the name of tests both before and after running, tracking down segmentation faults is much easier.

How to use gtest on the CS machines
-----------------------------------
Gtest is already installed on the public UTCS machines, and will run without any trouble.
Now, technically speaking, a custom version *should* be compiled for each project,
as certain compilation options can give redefinition errors,
but for everything within the scope of Professor Downing's classes, the precompiled binaries should work.

In order to use gtest, you need to import "gtest/gtest.h" into the test source file,
and you need to link the libraries libgtest.a and libpthread.a when compiling.
Linking libgtest_main.a is also recommended.
Just add -lgtest -lpthread -lgtest_main to the compile command.
It should look something like

    g++ {options} {TestSource} -o {TestProgram} -lgtest -lpthread -lgtest_main

Take a look at my [makefile](https://github.com/taylormck/GoogleTestExample/blob/master/makefile)
and [TestStuff.c++](https://github.com/taylormck/GoogleTestExample/blob/master/TestStuff.c%2B%2B)
if it's giving you trouble.

How to use gtest on your own machine
------------------------------------
Now, I promise it's not too difficult to get gtest running on your personal machine.

I'll fill in better instructions for installation later, but for now I'm just going to give a quick overview.
- You need cmake. You'll have to install it if you don't already have it.
- Next, install the gtest source (for debain systems, **sudo apt-get install libgtest-dev** is the easiest way)
- Now, you need to compile the source using cmake (in debain, it's in /usr/src/)
- You can either compile the libraries per project (Google's recommended way),
- or you can do what I did: compile the general version and move them into the libraries folder (in debain, /usr/lib/)

If you choose to install the gtest/gtest.h header somewhere out of the standard compilation path,
you **must** include it when compiling.

If you're lost, take a look at my [makefile](https://github.com/taylormck/GoogleTestExample/blob/master/makefile)
and [TestStuff.c++](https://github.com/taylormck/GoogleTestExample/blob/master/TestStuff.c%2B%2B).

Creating a test program
-----------------------
Now that you've got everything hooked up, it's time to start writing some tests.
Take a look at [TestStuff.c++](https://github.com/taylormck/GoogleTestExample/blob/master/TestStuff.c%2B%2B).
It contains some examples to show you the basic style of writing tests
and teaches you some cool stuff you can do with gtest.

Remember, you **need** iostream and gtest/gtest.h.
If you choose to write your own main (it isn't necessary), remember **not** to link libgtest_main.a.

Running gtest
-------------
Compile your test program and run it like normal.
In this example, it's as simple as 'make test'.
Of course, you can set up your tests and makefile to your liking.
