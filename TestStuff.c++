// A unit test source that makes use of gtest
#include <iostream>         // ostream
#include <vector>           // vector
#include <algorithm>        // equal

/*
 * This is the gtest header.
 * The usual installation is in /usr/include/
 *
 * It's already installed there on the CS machines,
 * but if you've installed it elsewhere on your own,
 * there's no need to change this line.
 *
 * You just need to make sure to include the folder where
 * you put the gtest folder when compiling.
 */
#include "gtest/gtest.h"

/*
 * Here's the good stuff
 * The TEST( ... ) { ... } is a macro
 * It's defined in gtest/gtest.h, and we're using it here
 * to create a test for us.
 * 
 * The first argument is the name of the test case.
 * This is used for grouping tests together.
 * The second name is the name of the test itself
 * ASSERT_EQ is a macro, that will test for equality between
 * two non-float types
 */
TEST(SampleTestCase, SampleTest) {
	ASSERT_EQ(1, 1);
	ASSERT_EQ('a', 'a');
}

/*
 * For convenience, tests are grouped up by Test Cases
 * The output will place a gap between Test cases,
 * making it easier to read.
 * 
 * This test will be grouped up with the previous test
 * Because it is in the same Test Case
 */
TEST(SampleTestCase, AnotherTest) {
	ASSERT_EQ(2, 2);
}

/*
 * This test will be tested separately from the previous two
 * because it is in a new Test Case
 */
TEST(OtherTestCase, SampleTest) {
	ASSERT_EQ(2, 2);
}

/*
 * This test will fail because 2 does not equal 1
 * What's nice about gtest is that it will clearly print which test
 * is failing, giving us both the expected value and the actual value.
 *
 * You see, these ASSERT_EQ macros take two arguments.
 * The first is the value we're expecting.
 * The second value is the value we're actually getting.
 *
 * In practice, they look something like:
 * 		ASSERT_EQ(720, factorial(6));
 *
 * or 	ASSERT_EQ(expected, actual);
 */
TEST(OtherTestCase, SampleTestFail) {
	ASSERT_EQ(1, 2);
}

/*
 * Often times, when unit testing, we find that we repeat a lot of code
 * to set up the tests.
 * This is when Test Fixtures come to the rescue.
 * 
 * Text Fixtures are classes that extend the testing::Test class
 * defined in gtest/gtest.h.
 * They allow us to do a lot of the set up here.
 * We can create the set up once, and reuse it in all of our tests.
 *
 * There are, however, a few rules.
 * First, this class MUST be defined BEFORE any of the tests that use it
 * Second, any test using this fixture MUST use the name TEST_F instead TEST.
 * Third, the test MUST use the name of this class as its Test Case name
 * 
 * Also worth remembering, each test using this fixture will get a fresh,
 * brand new instance of this class.
 * Changes made during one test WILL NOT affect future tests.
 */
class VectorTest : public testing::Test {
protected:
	std::vector<int> v;

	/*
	 * This function will be called at the beginning of every
	 * test involving this fixture, like a constructor.
	 *
	 * Do note that this is NOT a constructor, and an actual constructor
	 * may be used as well.
	 *
	 * You don't HAVE to write this method, it's here if you want it
	 */
	virtual void SetUp() {
		v.push_back(0);
		v.push_back(1);
		v.push_back(2);
	}

	/*
	 * This function will be called at the end of every test
	 * involving this fixture, like a destructor.
	 *
	 * Again, this is not a real destructor, and you're not required to define it
	 */
	virtual void TearDown() {
		// Nothing
	}

	/*
	 * You are free to write a constructor and/or destructor for this class
	 * as you see fit.
	 * They aren't required, but may come in handy
	 */
};

/*
 * So now I'm creating a test that uses my fixture
 * I HAVE to use TEST_F, and the test case name HAS to be the name
 * of the fixture.
 */
TEST_F(VectorTest, SampleVectorTest) {
	/*
	 * Notice here that I didn't have to do anything special to get v,
	 * I didn't even have to give a class name.
	 * Within this test, I have access to all public and protected members
	 * of the VectorTest class
	 */
	ASSERT_EQ(3, v.size());

	/*
	 * You may notice that I've used a new macro here.
	 * The expect macro is useful when we would like to check some value, but
	 * don't necessarily need to stop the test if the value is wrong.
	 * 
	 * The test will be reported a failure if the expectation is not met, even
	 * if it passes all the assertions.
	 *
	 * As a general rule of thumb, use assert when future code depends on the
	 * value being correct, use expect otherwise.
	 */
	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(1, v[1]);
	EXPECT_EQ(2, v[2]);
}

/*
 * For your convenience, these macros can be treated like output streams,
 * and you can pass them strings to print upon failure.
 */
TEST_F(VectorTest, SecondVectorTest) {
	EXPECT_EQ(4, v.size()) << "Hi, I'm a custom failure message."
                           << " I'll print to the console because this expect fails";

	ASSERT_EQ(3, v.size()) << "Assertions can have custom messages, too, but this won't fail.";
}

/*
 * To be clear, there are many type of assertions to use, and each with an
 * equivalent expect macro.
 *
 * Here are a few of them and when to use them.
 */
TEST(AssertionTypes, ShowAssertionTypes) {
	// Boolean expressions
	ASSERT_TRUE(true);
	ASSERT_FALSE(false);

	/*
	 * Binary comparisons
	 * Use these for most built in types
	 * and for user types that have the == and < operators defined
	 */
	ASSERT_EQ(1, 1); // ==
	ASSERT_NE(1, 2); // !=
	ASSERT_LT(1, 2); // <
	ASSERT_LE(1, 2); // <=
	ASSERT_GT(2, 1); // >
	ASSERT_GE(2, 1); // >=

	/*
	 * Floating point number binary comparisons
	 * I won't go into detail, but comparing floating point numbers isn't as
	 * easy as other types.
	 * No worries, we have some macros to make things easier
	 */
	ASSERT_FLOAT_EQ(2.0, 2.0);
	ASSERT_DOUBLE_EQ(2.0, 2.0);

	// These macros will measure equality to FOUR decimal places
	ASSERT_FLOAT_EQ(2.00001, 2.000011);

	// If you need more than that, use this macro, which lets you
	// specify the precision you want
	EXPECT_NEAR(2.00001, 2.000011, 0.0000001) << "These floats are not equal to the specified precision";

	/*
	 * About strings...
	 * For c++ strings, you can use the normal operators shown above
	 * but for c strings, you will need to use these
	 */
	ASSERT_STREQ("hi", "hi"); 		// content equals
	ASSERT_STRNE("hi", "hello"); 	// content not equals
	ASSERT_STRCASEEQ("hi", "HI");	// content equals, ignoring case
	ASSERT_STRCASENE("HI", "Hey");	// content not equals, ignoring case
}

/*
 * For arrays, there aren't any special macros
 * (Well, there are addons that have them, but they're not in the standard
 * Google C++ Unit Testing Framework)
 * We can just rely on fixtures and std::equal
 */
class ArrayEquals : public testing::Test {
protected:
	const int v[3];
	ArrayEquals(): v{1, 2, 3}{}
};

TEST_F(ArrayEquals, ArrayEqualsTest) {
	const int w[3] = {1, 2, 3};
	ASSERT_TRUE(std::equal(w, w + 3, v));
}

/*
 * Sometimes, we'll be building one or more classes that will use the same
 * interface. Other times, we'll be building a class to
 * ... hint hint... replicate the interface of another class
 *
 * Using Typed Tests, we can run the same tests on multiple types without
 * rewriting the code.  This can be handy for making sure all of our classes
 * work. Or, we can run tests with the class we're trying to emulate, so we
 * can be confident in our tests when we run them on our own class.
 *
 * First, you need to create a templated type fixture.
 * Create it just like any other type fixture. Give it a name, extend
 * testing::Test, and make its members protected or public.
 */
template <typename T>
class TypeTest : public testing::Test {
	protected:
		T x;
		T y;

		TypeTest(): x(0), y(0){}
};

/*
 * Next, we need to get our types together.
 * Gtest has defined a templated Types class we can make use of.
 *
 * Create a quick typedef, using testing::Types and put all the types you
 * need to test in the template, then give this templated type a name.
 */
typedef testing::Types<int, char> MyTypes;

/*
 * Next, we create a Typed Test Case, which will run the corresponding
 * Typed Tests on all the types specified. Pass it the name of the fixture
 * you created, then the name of the templated Types type you created.
 */
TYPED_TEST_CASE(TypeTest, MyTypes);

/*
 * Now create a TYPED_TEST using the name of the fixture/typed test case,
 * and give it a name.
 *
 * Unlike earlier, we need to use the keyword 'this' to get at the members
 * of our fixture.
 */
TYPED_TEST(TypeTest, TemplateTypeEquals) {
	ASSERT_EQ(this->x, this->y);
}


/*
 * If you want, you can totally write your own main.
 * I chose not to, and instead linked the compiler to libgtest_main.a,
 * which contains a boilerplate main.
 * Remember, you can't have BOTH, it's only one or the other.
 *
 * Anyways, here's what it would look like.
 */
 // int main(int argc, char **argv) {
 // 	::testing::InitGoogleTest(&argc, argv);
 // 	return RUN_ALL_TESTS();
 // }

/*
 * Remember, this is just barely scratching the surface of what gtest can do.
 *
 * If you want more, you can find some samples at
 * http://code.google.com/p/googletest/wiki/Samples
 *
 * You can also find read advanced tutorials,
 * which will show you a lot of features I've left out at
 * http://code.google.com/p/googletest/wiki/AdvancedGuide
 */
