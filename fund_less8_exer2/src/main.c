/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <kernel.h>
#include <kernel_structs.h>
#include <string.h>
#include <random/rand32.h>

#define THREAD0_STACKSIZE       512
#define THREAD1_STACKSIZE       512

/* STEP 3 - Set the priority of the two threads to have equal priority*/
#define THREAD0_PRIORITY 	    4
#define THREAD1_PRIORITY 	    4

/* STEP 5 - Define the two counters with a constant combined total */
#define COMBINED_TOTAL 		40

int32_t increment_partner = 0;
int32_t decrement_partnert = COMBINED_TOTAL;

/* STEP 11 - Define mutex to protect access to shared code section */
K_MUTEX_DEFINE(test_mutex);

// Shared code run by both threads
void shared_code_section(void)
{
	/* STEP 12.1 - Lock the mutex */
	k_mutex_lock(&test_mutex, K_FOREVER);
	k_mutex_unlock(&test_mutex);

	/* STEP 6 - Increment partner and decrement partner changed */
	/* according to logic defined in exercise text */
	increment_partner++;
	increment_partner = increment_partner % COMBINED_TOTAL;

	decrement_partnert--;
	if (decrement_partnert == 0){
		decrement_partnert = COMBINED_TOTAL;
	}

	/* STEP 12.2 - Unlock the mutex */

	/* STEP 7 - Print counter values if they do not add up to COMBINED_TOTAL */
	if (increment_partner + decrement_partnert != COMBINED_TOTAL) {
		printk("Increment partner (%d) + Decrement partner (%d) = %d\n", increment_partner, decrement_partnert, (increment_partner + decrement_partnert));
	}
}

/* STEP 4 - Functions for thread0 and thread1 with a shared code section */
void thread0(void)
{
	printk("Thread 0 started\n");
	while (1) {
		shared_code_section();
		// k_sleep(K_MSEC(100));
	}
}

void thread1(void)
{
	printf("Thread 1 started\n");
	while (1) {
		shared_code_section();
		// k_sleep(K_MSEC(100));
	}
}

// Define and initialize threads
K_THREAD_DEFINE(thread0_id, THREAD0_STACKSIZE, thread0, NULL, NULL, NULL,
		THREAD0_PRIORITY, 0, 0);

K_THREAD_DEFINE(thread1_id, THREAD1_STACKSIZE, thread1, NULL, NULL, NULL,
		THREAD1_PRIORITY, 0, 0);

