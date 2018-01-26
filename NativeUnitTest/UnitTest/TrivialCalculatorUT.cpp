#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\NativeUnitTest\TrivialCalculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NativeUnitTest_Namespace
{
	TEST_CLASS(TrivialCalculatorTest)
	{
	public:
		TrivialCalculatorTest()
		{
			test = new TrivialCalculator;
		}

		~TrivialCalculatorTest()
		{
			delete test;
		}

		TEST_METHOD(AddTest)
		{
			//TrivialCalculator test;
			double actual = test->Add(1.0, 2.0);
			double expected = 3.0;

			Assert::AreEqual(expected, actual, 0.0001);
		}

		TEST_METHOD(SubtractTest)
		{
			//TrivialCalculator test;
			double actual = test->Subtract(2.0, 1.0);
			double expected = 1.0;

			Assert::AreEqual(expected, actual, 0.0001);

			//Assert::AreEqual(1, 2, 0.0001);
		}


	public:
		TrivialCalculator * test;

	};

}