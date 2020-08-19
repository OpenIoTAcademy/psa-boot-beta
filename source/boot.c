
#include "boot_upgrade_package.h"

#include "boot_security.h"

#include "hal_timer.h"
#include "hal_log.h"

#include "aes.h"

#define PSA_VERSION_VER_MAJOR			0
#define PSA_VERSION_VER_MINOR			1

bool check_for_upgrade(void)
{
	return true;
}

uint32_t get_upgrade_package_offset(void)
{
	{
		/* Test code to remove */
		static uint8_t buffer[4 * 1024];
		boot_upgrade_package_t* package = (boot_upgrade_package_t*)buffer;

		strcpy((char*)buffer, "ZAYA");
		package->metadata.size = 128;

		return (uint32_t)buffer;
	}
}

void jump_to_latest_image(void)
{
	LOG_PRINTF(" >> BOOT : Application is being started!");
	while (1);
}

int main(void) {

	/* Let us wait for a while; because the UI may not be ready yet to send logs. */
	hal_timer_sleep(100);

	LOG_PRINTF("psa-boot v%d.%d", PSA_VERSION_VER_MAJOR, PSA_VERSION_VER_MINOR);

	if (check_for_upgrade())
	{
		uint32_t package_offset = get_upgrade_package_offset();

		boot_upgrade_package_t* upgrade_package = (boot_upgrade_package_t*)package_offset;

		if (boot_authenticate_upgrade_package(upgrade_package)) 
		{
			LOG_PRINTF(" >> BOOT : Upgrade package authentication : SUCCESS");
			boot_decrypt_upgrade_package(upgrade_package);

			LOG_PRINTF(" >> BOOT : Upgrade package decryption : SUCCESS");
		}
		else
		{
			LOG_PRINTF(" >> BOOT : Upgrade package authentication failed!");
		}
	}

	jump_to_latest_image();

	return 0;
}
