/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author:
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated:
 *           By:
 *     Update #: 0
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */
/* Code: */

#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_button.h>
// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
f3d_button_read();
}

int main(void) {
f3d_led_init();
f3d_button_init();
while(1)
{
f3d_led_all_off();
f3d_led_on(1);
delay();
f3d_led_off(1);
f3d_led_on(2);
delay();
f3d_led_off(2);
f3d_led_on(3);
delay();
f3d_led_off(3);
f3d_led_on(4);
delay();
f3d_led_off(4);
f3d_led_on(5);
delay();
f3d_led_off(5);
f3d_led_on(6);
delay();
f3d_led_off(6);
f3d_led_on(7);
delay();
f3d_led_off(7);
f3d_led_on(0);
delay();
f3d_led_off(0);
f3d_led_all_on();
delay();
}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
