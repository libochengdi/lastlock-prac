/* 
Controlling LEDs through UART. Press 1-4 on your keyboard to toggle LEDS 1-4 on your development kit */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

#include <drivers/uart.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#define ERORR 1
#define SUCCESS 0

/* LED pin numbers */
#define LED0_NODE 	DT_ALIAS(led0)
#define LED0		DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0		DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAG0		DT_GPIO_FLAGS(LED0_NODE, gpios)
#define LED1_NODE 	DT_ALIAS(led1)
#define LED1		DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1		DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAG1		DT_GPIO_FLAGS(LED1_NODE, gpios)
#define LED2_NODE 	DT_ALIAS(led2)
#define LED2		DT_GPIO_LABEL(LED2_NODE, gpios)
#define PIN2		DT_GPIO_PIN(LED2_NODE, gpios)
#define FLAG2		DT_GPIO_FLAGS(LED2_NODE, gpios)

/* STEP 9.1.1 - Define the size of the receive buffer */

/* STEP 9.2 - Define the receiving timeout period */

/* STEP 5.1 - Get C identifiers for the DeviceTree labels and properties' values related to LEDs */

static const struct device *leds;

/* STEP 8.1 - Define the transmission buffer, which is a buffer to hold the data to be sent over UART */


/* STEP 9.1.2 - Define the receive buffer */


/* STEP 6 - Define the callback function for UART */

void CheckError(int err) {
	if (err != 0) {
		exit(err);
	} else {
		; // Nowhere man in nowhere lands...
	}
}

int main(void)
{
	int ret;
	leds = device_get_binding(LED0);
	if (leds == NULL) {
		return 1 ;
	}

/* STEP 4 - Get the device struct of the UART hardware */
	const struct device *uart = device_get_binding(DT_LABEL(DT_NODELABEL(uart0)));
	if (uart == NULL) {
		printk("Cannot get UART device\n\r");
		return ERROR;
	}

	ret = gpio_pin_configure(leds, PIN0, GPIO_OUTPUT_ACTIVE | FLAG0);
	CheckError(ret);

	ret = gpio_pin_configure(leds, PIN1, GPIO_OUTPUT_ACTIVE | FLAG1);
	CheckError(ret);

	ret = gpio_pin_configure(leds, PIN2, GPIO_OUTPUT_ACTIVE | FLAG2);
	CheckError(ret);
/* STEP 5.2 - Configure the LEDs */

/* STEP 7 - Register the UART callback function */

/* STEP 8.2 - Send the data over UART by calling uart_tx() */

/* STEP 9.3  - Start receiving by calling uart_rx_enable() and pass it the address of the receive  buffer */

	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}
}
