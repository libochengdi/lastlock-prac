/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <logging/log.h>
#include <drivers/uart.h>

#define MAX_NUMBER_FACT 10
#define SLEEP_TIME_MS   10*60*1000

#define SW0_NODE    DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL  DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS  DT_GPIO_FLAGS(SW0_NODE, gpios)
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL  ""
#define SW0_GPIO_PIN    0
#define SW0_GPIO_FLAGS  0
#endif

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

LOG_MODULE_REGISTER(Less4_Exer3,LOG_LEVEL_DBG);

void button_pressed(const struct device *dev, struct gpio_callback *cb,
            uint32_t pins)
{
  int i;
  int j;
  long int factorial;
  LOG_INF("Calculating the factorials of numbers 1 to %d:",MAX_NUMBER_FACT);
  for (i=1;i<=MAX_NUMBER_FACT;i++){
       factorial =1;
        for (j=1;j<=i;j++){
            factorial = factorial*j;
        }
        LOG_INF("The factorial of %2d = %ld",i,factorial);
  }
  /*Important note! 
  Code in ISR runs at a high priority, therefore, it should be written with timing in mind.
  Too lengthy or too complex tasks should not be performed by an ISR, they should be deferred to a thread 
  */
}

static struct gpio_callback button_cb_data;

void main(void)
{
	const struct device *dev;

    const struct device *uart = device_get_binding(DT_LABEL(DT_NODELABEL(uart0)));
    if (uart == NULL) {
        LOG_ERR("Cannot get UART device");
        return;
    }

	int ret;
    int exercise_num=3;
    uint8_t data[] = {0x00, 0x01, 0x02, 0x03,
                      0x04, 0x05, 0x06, 0x07,
                      'H', 'e', 'l', 'l','o'};
    //Printf-like messages
    LOG_INF("nRF Connect SDK Fundamentals");
    LOG_INF("Exercise %d",exercise_num);    
    LOG_DBG("A log message in debug level");
    LOG_WRN("A log message in warning level!");
    LOG_ERR("A log message in error level!");
    //Hexdump some data
    LOG_HEXDUMP_INF(data, sizeof(data),"Sample Data!"); 

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}
    ret = gpio_pin_configure(dev, SW0_GPIO_PIN, GPIO_INPUT | SW0_GPIO_FLAGS);
    if (ret < 0) {
        return;
    }

    ret = gpio_pin_interrupt_configure(dev,
                       SW0_GPIO_PIN,
                       GPIO_INT_EDGE_TO_ACTIVE | GPIO_INT_DEBOUNCE);	

	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));	

	gpio_add_callback(dev, &button_cb_data);	
	while (1) {
        k_msleep(SLEEP_TIME_MS); 
	}
}