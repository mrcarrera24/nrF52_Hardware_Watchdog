/*
 * hardware_watchdog.c
 *
 *	Created on: May 3, 2023
 *			Author: mrcarrera24
 *
 *			//main.c
 *			 int main(void) {
 *			 	prv_check_and_reset_reboot_reason();
 *
 *			 	hardware_watchdog_enable();
 *			 	//...
 *
 */
#include <nrf_wdt.h>
#include <nrf_soc.h>

static uint32_t s_registered_tasks = 0;
static uint32_t s_fed_tasks = 0;

// ...
#define HARDWARE_WATCHDOG_TIMEOUT_SECS 10


void hardware_watchdog_feed(void) {
	// Per "6.36.4.10" if this value is written to a reload
	// register that is enabled, the watchdog counter will be reset
	//
	// NOTE: It's common to see "magic" numbers as reload values
	// in an effort to prevent a bad memory access from
	// inadvertently resetting the watchdog
	const uint32_t reload_magic_value = 0x6E524635;
	NRF_WDT->RR[0] = reload_magic_value;
}

void prv_check_and_reset_reboot_reason(void) {
	const uint32_t last_reboot_reason;

	#ifndef SOFTDEVICE_PRESENT
		// Read reset reason
		last_reboot_reason = NRF_POWER->RESETREAS; // this should be used only when Softdevice NOT enabled, otherwise the board will reset
		NRF_POWER->RESETREAS = 0xFFFFFFFF;
	#endif
	#ifdef SOFTDEVICE_PRESENT
		sd_power_reset_reason_get(&last_reboot_reason);// If reset caused by Watchdog the resetReason is 2, and if caused by power reset, the reason is 1
		sd_power_reset_reason_clr(0xFFFFFFFF);
	#endif

	// Halt the system on boot-up if a
	// Watchdog Reset took place
	const uint32_t watchdog_reset_mask = 0x2;
	if ((last_reboot_reason & watchdog_reset_mask) == watchdog_reset_mask) {
		__asm("bkpt 10");
	}
}

void hardware_watchdog_enable(void) {
	if ((NRF_WDT->RUNSTATUS & 0x1) != 0) {
		// the watchdog is already running and cannot be configured
		return;
	}

	// "Counter reload value" - The number of 32.768kHz
	// clock cycles to elapse before a watchdog timeout
	NRF_WDT->CRV = 32768 * HARDWARE_WATCHDOG_TIMEOUT_SECS;

	// Enables the watchdog peripheral
	NRF_WDT->TASKS_START = 0x1;
}

void prv_task_watchdog_check(void) {
	if ((s_fed_tasks & s_registered_tasks) == s_registered_tasks) {
		// all the tasks have been fed or are idle!
		hardware_watchdog_feed();
		s_fed_tasks = 0;
	}
}

void task_watchdog_register_task(uint32_t task_id) {
	__disable_irq();

	s_registered_tasks |= (1 << task_id);

	__enable_irq();
}

void task_watchdog_unregister_task(uint32_t task_id) {
	__disable_irq();

	s_registered_tasks &= ~(1 << task_id);
	s_fed_tasks &= ~(1 << task_id);
	prv_task_watchdog_check();

	__enable_irq();
}

void task_watchdog_feed_task(uint32_t task_id) {
	__disable_irq();

	s_fed_tasks |= (1 << task_id);
	prv_task_watchdog_check();

	__enable_irq();
}


