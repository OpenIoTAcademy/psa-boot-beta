#include "pch.h"
#include "CppUnitTest.h"
#include "../../../source/boot_security.c"
#include "psa-boot-testdata.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace psaboottest
{
	TEST_CLASS(psaboottest)
	{
#define GET_TEST_PACKAGE(_pack)				(boot_upgrade_package_t*)copy_package(_pack, sizeof(_pack))
#define RELEASE_TEST_PACKAGE(_pack)			free(_pack)

	private:
		/// <summary>
		/// Copies a package into Read/Write Buffer. 
		/// Example Tests packages are constant values so
		/// decryption cannot update the packages, therefore,
		/// we need to copy the package to a updatable memory.
		/// </summary>
		/// <param name="source">Source Package</param>
		/// <param name="size">Source Package Size</param>
		/// <returns>Destination Package</returns>
		uint8_t* copy_package(const uint8_t* source, uint32_t size)
		{
			uint8_t* dest = (uint8_t*)malloc(size);
			if (dest == NULL)
			{
				return NULL;
			}

			memcpy(dest, source, size);

			return dest;
		}

		/// <summary>
		/// Compares two strings and returns true if strings are equals
		/// </summary>
		/// <param name="str1">String 1</param>
		/// <param name="str2">String 2</param>
		/// <returns>True if strings are equal, otherwise returns false</returns>
		bool strings_are_equal(const uint8_t* str1, const uint8_t* str2)
		{
			int str_len = strlen((char*)str1) > strlen((char*)str2) ? strlen((char*)str2) : strlen((char*)str1);

			return strncmp((char*)str1, (char*)str2, str_len) == 0;
		}

	public:
		/// <summary>
		/// Tests boot_decrypt_upgrade_package() function using a valid
		/// upgrade package
		/// </summary>
		TEST_METHOD(decryption_test_valid)
		{
			boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_valid_package);
			{
				bool isEqual = strings_are_equal(package->image, td_valid_package_plain_image_content);

				/* We should have encrypted image so, strings should not be the same before decryption */
				Assert::IsFalse(isEqual);

				/* Let us decrypt the valid package */
				boot_decrypt_upgrade_package(package);

				isEqual = strings_are_equal(package->image, td_valid_package_plain_image_content);

				/* After the encryption, the image must be the same with expected plain image */
				Assert::IsTrue(isEqual);
			}
			RELEASE_TEST_PACKAGE(package);
		}
		/// <summary>
		/// Tests boot_decrypt_upgrade_package() function using a invalid
		/// upgrade package
		/// </summary>
		TEST_METHOD(decryption_test_invalid)
		{
			boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_invalid_package);
			{
				bool isEqual = strings_are_equal(package->image, td_valid_package_plain_image_content);

				/* We should have encrypted image so, strings should not be the same before decryption */
				Assert::IsFalse(isEqual);

				/* Let us decrypt the valid package */
				boot_decrypt_upgrade_package(package);

				isEqual = strings_are_equal(package->image, td_valid_package_plain_image_content);

				/* After the encryption, the image must be the same with expected plain image */
				Assert::IsFalse(isEqual);
			}
			RELEASE_TEST_PACKAGE(package);
		}
	};
}
