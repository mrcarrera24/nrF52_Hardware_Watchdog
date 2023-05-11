/*
 * hardware_watchdog.h
 *
 *  Created on: May 3, 2023
 *      Author: mrcarrera24
 */
//#include "Arduino.h"
#ifndef SRC_WATCHDOG_HARDWARE_WATCHDOG_H_
#define SRC_WATCHDOG_HARDWARE_WATCHDOG_H_

void hardware_watchdog_feed(void);
void prv_check_and_reset_reboot_reason(void);
void hardware_watchdog_enable(void);
static void prv_task_watchdog_check(void);
void task_watchdog_register_task(unsigned long int task_id);
void task_watchdog_unregister_task(unsigned long int task_id);
void task_watchdog_feed_task(unsigned long int task_id);

#endif /* SRC_WATCHDOG_HARDWARE_WATCHDOG_H_ */
