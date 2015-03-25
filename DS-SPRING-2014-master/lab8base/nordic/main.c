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

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers
#include <ds_led.h>     // Pull in include file for the local drivers
#include <ds_button.h>
#include <ds_uart.h>
#include <ds_gyro.h>
#include <ds_i2c.h>
#include <ds_accel.h>
#include <ds_mag.h>
#include <ds_systick.h>
#include <ds_rtc.h>
#include <schedule.h>
#include <ds_delay.h>
#include <ff.h>
#include <diskio.h>
#include <ds_nordic.h>
#include <ds_wifibase.h>
#include <nrf24l01.h>
#include <nrf24l01base.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
 
  ds_led_init();
  ds_button_init();
  ds_uart_init();
  ds_gyro_init();
  ds_i2c1_init();
  ds_accel_init();
  ds_mag_init();
  ds_systick_init();
  ds_rtc_init();
  ds_delay_init();
  ds_wifibase_init();

  char index;
 
  //   nrf24l01base_initialize_debug(true, 1, false);  // setup wifibase as a receiver, Standard Shockburst
  nrf24l01base_initialize_debug(true, 32, true);       // Enhanced Shockburst, Auto Ack turned on
  nrf24l01base_clear_flush();
  while(1)
  {
  // Base Reception
  char rxdata[32];
  printf("hi");
  while(!(nrf24l01base_irq_pin_active() && nrf24l01base_irq_rx_dr_active()));
  ds_led_on(3);
  nrf24l01base_read_rx_payload(rxdata, 32);   
  nrf24l01base_irq_clear_all();
  ds_delay_uS(130);

  // Payload Translation
 
  printf("Base Data: ");
  for (index=0;index<32;index++) {
    printf("%c",rxdata[index]);
  }
  printf("\n");
  //}
  /* printf("Base: receive character: %c\n",rxdata); */
  /* rxdata-=32; */
  //  printf("Base: upcase: %c\n",rxdata);
   
  printf("#### End Wifi Test ####\n");
 
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
