#include <zephyr.h>
#include <sys/printk.h>

void main(void)
{
    while (1) {
        printk("Hello, world!\n");
        k_msleep(1000); // What's the difference between this and k_sleep?
    }
    
}