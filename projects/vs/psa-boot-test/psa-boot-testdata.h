
#ifndef __PSA_BOOT_TESTDATA_H
#define __PSA_BOOT_TESTDATA_H

#include <stdint.h>

static const uint8_t td_package_valid[] = {
    // Prefix : ZAYA
    0x5A, 0x41, 0x59, 0x41,
    // Version
    0x01, 0x00, 0x00, 0x00,
    // Size
    0x20, 0x00, 0x00, 0x00,
    // Reserved
    0x00, 0x00, 0x00, 0x00,
    // IV
    0x88, 0x61, 0x8D, 0xBF, 0x2A, 0x75, 0xC5, 0x97, 0x7D, 0x2C, 0x7C, 0x7D, 0x7B, 0x88, 0xD6, 0x92,
    // Signature
    0xBF, 0xA6, 0x82, 0x07, 0x89, 0x5E, 0x18, 0xB7, 0x77, 0xC9, 0xD3, 0x76, 0x62, 0x85, 0x61, 0xA6,
    0xBE, 0x53, 0xEE, 0xAC, 0xCA, 0x12, 0x9B, 0x59, 0xBC, 0x11, 0x5F, 0xC2, 0xB4, 0x36, 0x95, 0x06,
    0x44, 0xB1, 0xC5, 0xF9, 0xEF, 0xC6, 0x14, 0xD7, 0x88, 0xD9, 0x7D, 0x55, 0x0E, 0xFE, 0x18, 0x70,
    0x2D, 0xE9, 0xD8, 0xCD, 0x7E, 0x96, 0xFF, 0xF0, 0xCE, 0x89, 0x2C, 0x38, 0xB3, 0xD0, 0x17, 0x88,
    // Encrypted Image
    0xE0, 0x6E, 0xEF, 0x6F, 0x66, 0x34, 0xF5, 0x4C, 0x3B, 0x56, 0x7D, 0x4B, 0x24, 0x6A, 0xA4, 0x23,
    0x73, 0xD8, 0xA0, 0xD9, 0x74, 0xD8, 0x59, 0x70, 0x02, 0x43, 0x32, 0x3F, 0xBC, 0xD2, 0xBB, 0x0B
};

static const uint8_t td_valid_package_plain_image_content[] = "Application Image is success!";
static const uint8_t td_valid_package_plain_image_len = sizeof(td_valid_package_plain_image_content) - 1;

static const uint8_t td_package_invalid_image[] = {
    // Prefix : ZAYA
    0x5B, 0x41, 0x59, 0x41,
    // Version
    0x01, 0x00, 0x00, 0x00,
    // Size
    0x20, 0x00, 0x00, 0x00,
    // Reserved
    0x00, 0x00, 0x00, 0x00,
    // IV
    0x88, 0x61, 0x8D, 0xBF, 0x2A, 0x75, 0xC5, 0x97, 0x7D, 0x2C, 0x7C, 0x7D, 0x7B, 0x88, 0xD6, 0x92,
    // Signature
    0xBF, 0xA6, 0x82, 0x07, 0x89, 0x5E, 0x18, 0xB7, 0x77, 0xC9, 0xD3, 0x76, 0x62, 0x85, 0x61, 0xA6,
    0xBE, 0x53, 0xEE, 0xAC, 0xCA, 0x12, 0x9B, 0x59, 0xBC, 0x11, 0x5F, 0xC2, 0xB4, 0x36, 0x95, 0x06,
    0x44, 0xB1, 0xC5, 0xF9, 0xEF, 0xC6, 0x14, 0xD7, 0x88, 0xD9, 0x7D, 0x55, 0x0E, 0xFE, 0x18, 0x70,
    0x2D, 0xE9, 0xD8, 0xCD, 0x7E, 0x96, 0xFF, 0xF0, 0xCE, 0x89, 0x2C, 0x38, 0xB3, 0xD0, 0x17, 0x88,
    // Encrypted Image
    0xE1, 0x6E, 0xEF, 0x6F, 0x66, 0x34, 0xF5, 0x4C, 0x3B, 0x56, 0x7D, 0x4B, 0x24, 0x6A, 0xA4, 0x23,
    0x73, 0xD8, 0xA0, 0xD9, 0x74, 0xD8, 0x59, 0x70, 0x02, 0x43, 0x32, 0x3F, 0xBC, 0xD2, 0xBB, 0x0B
};

static const uint8_t td_package_invalid_IV[] = {
    // Prefix : ZAYA
    0x5A, 0x41, 0x59, 0x41,
    // Version
    0x01, 0x00, 0x00, 0x00,
    // Size
    0x20, 0x00, 0x00, 0x00,
    // Reserved
    0x00, 0x00, 0x00, 0x00,
    // IV
    0x89, 0x61, 0x8D, 0xBF, 0x2A, 0x75, 0xC5, 0x97, 0x7D, 0x2C, 0x7C, 0x7D, 0x7B, 0x88, 0xD6, 0x92,
    // Signature
    0xBF, 0xA6, 0x82, 0x07, 0x89, 0x5E, 0x18, 0xB7, 0x77, 0xC9, 0xD3, 0x76, 0x62, 0x85, 0x61, 0xA6,
    0xBE, 0x53, 0xEE, 0xAC, 0xCA, 0x12, 0x9B, 0x59, 0xBC, 0x11, 0x5F, 0xC2, 0xB4, 0x36, 0x95, 0x06,
    0x44, 0xB1, 0xC5, 0xF9, 0xEF, 0xC6, 0x14, 0xD7, 0x88, 0xD9, 0x7D, 0x55, 0x0E, 0xFE, 0x18, 0x70,
    0x2D, 0xE9, 0xD8, 0xCD, 0x7E, 0x96, 0xFF, 0xF0, 0xCE, 0x89, 0x2C, 0x38, 0xB3, 0xD0, 0x17, 0x88,
    // Encrypted Image
    0xE0, 0x6E, 0xEF, 0x6F, 0x66, 0x34, 0xF5, 0x4C, 0x3B, 0x56, 0x7D, 0x4B, 0x24, 0x6A, 0xA4, 0x23,
    0x73, 0xD8, 0xA0, 0xD9, 0x74, 0xD8, 0x59, 0x70, 0x02, 0x43, 0x32, 0x3F, 0xBC, 0xD2, 0xBB, 0x0B
};

static const uint8_t td_invalid_package[] = {
    // Prefix : ZAYA
    0x5A, 0x41, 0x59, 0x41,
    // Version
    0x01, 0x00, 0x00, 0x00,
    // Size
    0x20, 0x00, 0x00, 0x00,
    // Reserved
    0x00, 0x00, 0x00, 0x00,
    // IV
    0x88, 0x61, 0x8D, 0xBF, 0x2A, 0x75, 0xC5, 0x97, 0x7D, 0x2C, 0x7C, 0x7D, 0x7B, 0x88, 0xD6, 0x92,
    // Signature
    0xBF, 0xA6, 0x82, 0x07, 0x89, 0x5E, 0x18, 0xB7, 0x77, 0xC9, 0xD3, 0x76, 0x62, 0x85, 0x61, 0xA6,
    0xBE, 0x53, 0xEE, 0xAC, 0xCA, 0x12, 0x9B, 0x59, 0xBC, 0x11, 0x5F, 0xC2, 0xB4, 0x36, 0x95, 0x06,
    0x44, 0xB1, 0xC5, 0xF9, 0xEF, 0xC6, 0x14, 0xD7, 0x88, 0xD9, 0x7D, 0x55, 0x0E, 0xFE, 0x18, 0x70,
    0x2D, 0xE9, 0xD8, 0xCD, 0x7E, 0x96, 0xFF, 0xF0, 0xCE, 0x89, 0x2C, 0x38, 0xB3, 0xD0, 0x17, 0x88,
    // Encrypted Image
    0x0F, 0x66, 0xEF, 0x6F, 0x66, 0x34, 0xF5, 0x4C, 0x3B, 0x56, 0x7D, 0x4B, 0x24, 0x6A, 0xA4, 0x23,
    0x73, 0xD8, 0xA0, 0xD9, 0x74, 0xD8, 0x59, 0x70, 0x02, 0x43, 0x32, 0x3F, 0xBC, 0xD2, 0xBB, 0x0B
};
static const uint8_t td_invalid_IV_package[] = {
    // Prefix : ZAYA
    0x5A, 0x41, 0x59, 0x41,
    // Version
    0x01, 0x00, 0x00, 0x00,
    // Size
    0x20, 0x00, 0x00, 0x00,
    // Reserved
    0x00, 0x00, 0x00, 0x00,
    // IV
    0x77, 0x61, 0x8D, 0xBF, 0x2A, 0x75, 0xC5, 0x97, 0x7D, 0x2C, 0x7C, 0x7D, 0x7B, 0x88, 0xD6, 0x92,
    // Signature
    0xBF, 0xA6, 0x82, 0x07, 0x89, 0x5E, 0x18, 0xB7, 0x77, 0xC9, 0xD3, 0x76, 0x62, 0x85, 0x61, 0xA6,
    0xBE, 0x53, 0xEE, 0xAC, 0xCA, 0x12, 0x9B, 0x59, 0xBC, 0x11, 0x5F, 0xC2, 0xB4, 0x36, 0x95, 0x06,
    0x44, 0xB1, 0xC5, 0xF9, 0xEF, 0xC6, 0x14, 0xD7, 0x88, 0xD9, 0x7D, 0x55, 0x0E, 0xFE, 0x18, 0x70,
    0x2D, 0xE9, 0xD8, 0xCD, 0x7E, 0x96, 0xFF, 0xF0, 0xCE, 0x89, 0x2C, 0x38, 0xB3, 0xD0, 0x17, 0x88,
    // Encrypted Image
    0xE0, 0x6E, 0xEF, 0x6F, 0x66, 0x34, 0xF5, 0x4C, 0x3B, 0x56, 0x7D, 0x4B, 0x24, 0x6A, 0xA4, 0x23,
    0x73, 0xD8, 0xA0, 0xD9, 0x74, 0xD8, 0x59, 0x70, 0x02, 0x43, 0x32, 0x3F, 0xBC, 0xD2, 0xBB, 0x0B
};

#endif // __PSA_BOOT_TESTDATA_H
