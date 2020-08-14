#ifndef __UPGRADE_PACKAGE_H
#define __UPGRADE_PACKAGE_H

#include "boot_types.h"

/*
 * Upgrade Package Metadata
 */

typedef struct
{

    /* Upgrade Package Metadata Prefix : Must be ZAYA */
    uint8_t prefix[4];
    /* Version of the image/application */
    uint32_t version;
    /* Image size */
    uint32_t size;
    uint8_t reserved[4];
    /* Signature */
    uint8_t signature[128];
} boot_image_metadata_t;

typedef struct
{
    /* Metadata */
    boot_image_metadata_t metadata;
    /* Application */
    uint8_t image[1];
    /* TODO image here */

} boot_upgrade_package_t;

#endif