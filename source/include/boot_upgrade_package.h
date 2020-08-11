
#ifndef __UPGRADE_PACKAGE_H
#define __UPGRADE_PACKAGE_H

#include "boot_types.h"

typedef struct
{
    uint32_t dummy;
    /* TODO all fields here */
} boot_image_metadata_t;

typedef struct
{
    boot_image_metadata_t metadata;
    /* TODO image here */
} boot_upgrade_package_t;

#endif