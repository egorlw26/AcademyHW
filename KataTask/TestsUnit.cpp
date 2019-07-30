#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TDD_HW/Parser.h"
#include "../TDD_HW/Parser.cpp"
#include "../TDD_HW/StringCalc.h"
#include "../TDD_HW/StringCalc.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StringCalcUnitTests
{		
	TEST_CLASS(CalculatorTests)
	{
	public:
		
		TEST_METHOD(Expect_0_When_Empty)
		{
			StringCalc sc;
			int expected = 0;
			Assert::AreEqual(expected, sc.Add(""));
		}

		TEST_METHOD(Expect_3_When_1coma2)
		{
			StringCalc sc;
			int expected = 3;
			Assert::AreEqual(expected, sc.Add("1,2"));
		}

		TEST_METHOD(Expect_6_When_Condition)
		{
			StringCalc sc;
			int expected = 6;
			Assert::AreEqual(expected, sc.Add("//[;]\n1\n2;3"));
		}

		TEST_METHOD(Expect_Exception_When_Negatives)
		{
			StringCalc sc;
			Assert::ExpectException < std::exception>([&sc] {sc.Add("//[;]\n-1\n-2;3"); });
		}

		TEST_METHOD(Expect_10_When_Multiple_Delimeters)
		{
			StringCalc sc;
			int expected = 10;
			Assert::AreEqual(expected, sc.Add("//[;][***][+]\n1\n2;3;2***2"));
		}

	};
}