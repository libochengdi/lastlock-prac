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

#define PRODUCER_STACKSIZE       512
#define CONSUMER_STACKSIZE       512

/* STEP 2 - Set the priority of the producer and consumper thread */
#define PRODUCER_PRIORITY        5
#define CONSUMER_PRIORITY        4

/* STEP 9 - Define semaphore to monitor instances of available resource */

K_SEM_DEFINE(instance_monitor_sem, 10, 10);

/* STEP 3 - Initialize the available instances of this resource */
volatile uint32_t available_instance_count = 10;

// Function for getting access of resource
void get_access(void)
{
	/* STEP 10.1 - Get semaphore before access to the resource */
	k_sem_take(&instance_monitor_sem, K_FOREVER);

	/* STEP 6.1 - Decrement available resource */
	available_instance_count--;
	printk("Resource taken and available_insrtance count is %d\n\r", available_instance_count);

}

// Function for releasing access of resource
void release_access(void)
{
	/* STEP 6.2 - Increment available resource */
	available_instance_count++;
	printk("Resource given and available_insrtance count is %d\n\r", available_instance_count);
	/* STEP 10.2 - Give semaphore after finishing access to resource */

	k_sem_give(&instance_monitor_sem);

}

/* STEP 4 - Producer thread relinquishing access to instance */
void producer(void)
{
	printk("Producer thread started\n\r");
	while (1) {
		release_access();
		// Assume the resource instance access is released at this point
		k_msleep(sys_rand32_get() % 10);
	}
}

/* STEP 5 - Consumer thread obtaining access to instance */
void consumer(void)
{
	printf("Consumer thread started\n\r");
	while (1) {
		get_access();
		// Assume the resource instance access is obtained at this point
		k_msleep(sys_rand32_get() % 10);
	}
}

// Define and initialize threads
K_THREAD_DEFINE(producer_id, PRODUCER_STACKSIZE, producer, NULL, NULL, NULL,
		PRODUCER_PRIORITY, 0, 0);

K_THREAD_DEFINE(consumer_id, CONSUMER_STACKSIZE, consumer, NULL, NULL, NULL,
		CONSUMER_PRIORITY, 0, 0);