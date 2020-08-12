
#ifndef __UPGRADE_PACKAGE_H
#define __UPGRADE_PACKAGE_H

#include "boot_types.h"

typedef struct
{
    uint32_t dummy;
    uint8_t prefix[4];
    uint32_t version;
    uint32_t size;
    uint8_t signature[64]
} boot_image_metadata_t;

typedef struct
{
    boot_image_metadata_t metadata;
    uint32_t image;
    /* TODO image here */
} boot_upgrade_package_t;

#endif
