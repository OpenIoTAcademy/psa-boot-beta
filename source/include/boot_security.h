
#ifndef __BOOT_SECURITY_H
#define __BOOT_SECURITY_H

#include "boot_upgrade_package.h"

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package);

void boot_decrypt_upgrade_package(boot_upgrade_package_t* package);

#endif
