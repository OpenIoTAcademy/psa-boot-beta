#include "pch.h"
#include "CppUnitTest.h"
#include "../../../source/boot_security.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace psaboottest
{
	TEST_CLASS(psaboottest)
	{
	public:
		/// <summary>
		/// Tests sum_correct function
		/// Positive Test
		/// </summary>
		TEST_METHOD(sum_correct_test)
		{
			int val1 = 2;
			int val2 = 3;
			int expected_sum = val1 + val2;

			int actual_sum = sum_correct(val1, val2);

			Assert::AreEqual(expected_sum, actual_sum);
		}

		/// <summary>
		/// Tests sum_correct function for a 100x100 matrix
		/// </summary>
		TEST_METHOD(sum_correct_test_loop)
		{
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					int expected_sum = i + j;
					int actual_sum = sum_correct(i, j);

					Assert::AreEqual(expected_sum, actual_sum);
				}
			}
		}

		/// <summary>
		/// Tests sum_correct_fail function which must fail
		/// </summary>
		TEST_METHOD(sum_correct_fail)
		{
			int val1 = 2;
			int val2 = 3;
			int expected_sum = val1 + val2;

			int actual_sum = sum_wrong(val1, val2);

			Assert::AreNotEqual(expected_sum, actual_sum);

			/* Actual Sum value should be wrong so the following line must fail */
			Assert::AreEqual(expected_sum, actual_sum);
		}

		/// <summary>
		/// Tests ecdsa_verify_signature function
		/// Positive Test
		/// </summary>

		TEST_METHOD(ecdsa_verify_signature_correct)
		{

		}


		/// <summary>
		/// Tests ecdsa_verify_signature function which must fail
		/// </summary>

		TEST_METHOD(ecdsa_verify_signature_fail)
		{

		}

		/// <summary>
		/// Tests boot_authenticate_upgrade_package function
		/// Positive Test
		/// </summary>
		TEST_METHOD(boot_authenticate_upgrade_package_correct)
		{
			
			
		}
	};
}
