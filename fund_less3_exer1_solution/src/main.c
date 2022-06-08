#include <zephyr.h>
#include <sys/printk.h>
#include "myfunction.h"

void main(void)
{
	int a = 3, b = 4;

	while(1) {
		printk("Hello World!\n\r");
		
		printf("Button 1 was pressed!\n\r");
		LOG_INF("nRF CONNECT SDK FUNDAMENTALS");
		k_msleep(1000);

		// printk("The result of adding %d and %d is %d\n", a, b, sum(a, b));
	}
}