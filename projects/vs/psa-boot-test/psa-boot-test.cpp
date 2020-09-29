#include "pch.h"
#include "CppUnitTest.h"
#include "../../../source/boot_security.c"
#include "psa-boot-testdata.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define GET_TEST_PACKAGE(_pack)                (boot_upgrade_package_t*)copy_package(_pack, sizeof(_pack))
#define RELEASE_TEST_PACKAGE(_pack)            free(_pack)

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
bool arrays_are_equal(const uint8_t* arr1, const uint8_t* arr2, uint32_t len)
{
    return memcmp(arr1, arr2, len) == 0;
}

namespace PSABootTests
{
    TEST_CLASS(PositiveCases)
    {
    public:
         /// <summary>
         /// In this case, we use a valid package
         /// that is encrypted with the encryption key.
         /// The decrypted image must be the same as
         /// the expected plain image value.
         /// </summary>
        TEST_METHOD(decryption_test_valid_image)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_valid);
            {
                bool isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* We should have encrypted image so, strings should not be the same before decryption */
                Assert::IsFalse(isEqual);

                /* Let us decrypt the valid package */
                boot_decrypt_upgrade_package(package);

                isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* After the encryption, the image must be the same with expected plain image */
                Assert::IsTrue(isEqual);
            }
            RELEASE_TEST_PACKAGE(package);
        }
        /// <summary>
        /// In this case, we use a valid package
        /// that is signed with the signing private key.
        /// The image must be authenticated
        /// using the signing public key.
        /// </summary>
        TEST_METHOD(authenticate_test_valid_image)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_valid);
            {
                /* Let us authenticate valid package */
                bool authenticated = boot_authenticate_upgrade_package(package);

                Assert::IsTrue(authenticated);
            }
            RELEASE_TEST_PACKAGE(package);
        }
    };

    TEST_CLASS(NegativeCases)
    {
    public:
        /// <summary>
        /// In this case, we use an invalid package
        /// which is not encrypted with the encryption key.
        /// The decrypted image must not be the same as
        /// the expected plain image value.
        /// </summary>
        TEST_METHOD(decryption_test_invalid_image)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_invalid_image);
            {
                bool isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* We should have encrypted image so, strings should not be the same before decryption */
                Assert::IsFalse(isEqual);

                /* Let us decrypt the valid package */
                boot_decrypt_upgrade_package(package);

                isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* After the encryption, the image must not be the same with expected plain image */
                Assert::IsFalse(isEqual);
            }
            RELEASE_TEST_PACKAGE(package);
        }

        /// <summary>
        /// In this case, we use an invalid package
        /// that has an invalid IV(Initialisation Vector).
        /// The decrypted image must not be the same as
        /// the expected plain image value.
        /// </summary>
        TEST_METHOD(decryption_test_invalid_IV)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_invalid_IV);
            {
                bool isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* We should have encrypted image so, strings should not be the same before decryption */
                Assert::IsFalse(isEqual);

                /* Let us decrypt the valid package */
                boot_decrypt_upgrade_package(package);

                isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* After the encryption, the image must not be the same with expected plain image */
                Assert::IsFalse(isEqual);
            }
            RELEASE_TEST_PACKAGE(package);
        }

        /// <summary>
        /// In this case, we use an invalid package
        /// that has a wrong size.
        /// The decrypted image must not be the same as
        /// the expected plain image value.
        /// </summary>
        TEST_METHOD(decryption_test_wrong_size)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_wrong_size);
            {
                bool isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* We should have encrypted image so, strings should not be the same before decryption */
                Assert::IsFalse(isEqual);

                /* Let us decrypt the valid package */
                boot_decrypt_upgrade_package(package);

                isEqual = arrays_are_equal(package->image, td_valid_package_plain_image_content, td_valid_package_plain_image_len);

                /* After the encryption, the image must not be the same with expected plain image */
                Assert::IsFalse(isEqual);
            }
            RELEASE_TEST_PACKAGE(package);
        }

        /// <summary>
        /// In this case, we use an invalid package
        /// that has an invalid signature.
        /// The image must not be authenticated
        /// using the signing public key.
        /// </summary
        TEST_METHOD(authenticate_test_invalid_signature)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_invalid_signature);
            {
                /* Let us the authenticate invalid signature package */
                bool authenticated = boot_authenticate_upgrade_package(package);

                Assert::IsFalse(authenticated);
            }
            RELEASE_TEST_PACKAGE(package);
        }

        /// <summary>
        /// In this case, we use an invalid package
        /// that has a wrong size.
        /// The image must not be authenticated
        /// using the signing public key.
        /// </summary>
        TEST_METHOD(authentication_test_wrong_size)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_wrong_size);
            {
                /* Let us the authenticate wrong size  package */
                bool authenticated = boot_authenticate_upgrade_package(package);

                Assert::IsFalse(authenticated);
            }
            RELEASE_TEST_PACKAGE(package);
        }

        /// <summary>
        /// In this case, we use an invalid package
        /// that has an invalid image
        /// The image must not be authenticated
        /// using the signing public key.
        /// </summary>
        TEST_METHOD(authentication_test_invalid_image)
        {
            boot_upgrade_package_t* package = GET_TEST_PACKAGE(td_package_invalid_image);
            {
                /* Let us the authenticate invalid package */
                bool authenticated = boot_authenticate_upgrade_package(package);

                Assert::IsFalse(authenticated);
            }
            RELEASE_TEST_PACKAGE(package);
        }
        };

    TEST_CLASS(PerformanceTests)
    {
    public:
        TEST_METHOD(decryption_performance_test)
        {
        }
    };
}