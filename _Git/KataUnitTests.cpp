#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\TDD_HW\Kata.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Expect_0_WhenEmpty)
		{
			int expected = 0;
			Assert::AreEqual(expected, Add(""));
		}

		TEST_METHOD(Expect_3_When_1_coma_2)
		{
			int expected = 14;
			Assert::AreEqual(expected, Add("//[,]\n12,2"));
		}

		TEST_METHOD(Expect_10_When_3_coma_3_slash_4)
		{
			int expected = 10;
			Assert::AreEqual(expected, Add("//[,][/]\n3,3/4"));
		}

		TEST_METHOD(Expect_exception_When_3_coma_7_slash_minus4)
		{
			Assert::ExpectException < std::string>([] {Add("//[,][/]\n3,7/-4"); });
		}

		TEST_METHOD(Expect_exception_When_minus3_coma_minus7_slash_minus4)
		{
			Assert::ExpectException < std::string>([] {Add("//[,][/]\n-3,-7/-4"); });
		}

		TEST_METHOD(Expect_2_When_2_1001)
		{
			int expected = 2;
			Assert::AreEqual(expected, Add("//[,]\n2,1001"));
		}

		TEST_METHOD(Expect_3_When_1starstarstar2starstarstar)
		{
			int expected = 3;
			Assert::AreEqual(expected, Add("//[***]\n1***2***"));
		}

		TEST_METHOD(Expect_100_When_10coma_20slash_30starstar_40)
		{
			int expected = 100;
			Assert::AreEqual(expected, Add("//[,][/][**]\n10,20/30**40"));
		}

		TEST_METHOD(Expect_6_1star_2percent_3)
		{
			int expected = 6;
			Assert::AreEqual(expected, Add("//[*][%]\n1*2%3"));
		}

	};
}