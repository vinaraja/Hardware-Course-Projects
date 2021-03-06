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
//#include <schedule.h> 
#include <ds_delay.h>
#include <ff.h>
#include <diskio.h>
#include <ds_nordic.h>
#include <ds_wifibase.h>
#include <nrf24l01.h>
#include <nrf24l01base.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

float compTilt(float temp, float xaxis, float yaxis)
{
if(xaxis>0.0 && yaxis>0.0)
{return temp+180.0;}
if(xaxis>0.0 && yaxis<0.0)
{return(temp+180.0);}
if(xaxis<0.0 && yaxis<0.0)
{return(temp);}
if(xaxis<0.0 && yaxis>0.0)
{return(temp+360.0);}
}

int main(void) { 

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
	
  ds_led_init();
  f3d_led_init();
  ds_button_init();
  ds_uart_init();
  ds_gyro_init();
  ds_i2c1_init();
  ds_accel_init();
  ds_mag_init();
  ds_systick_init();
  ds_rtc_init();
  ds_delay_init();
  ds_nordic_init();
  ds_wifibase_init();
  float tilt,pitch,roll,xh,yh,mx,my,mz,ax,ay,az,tilt1;
  float accel_data[3];
  float mag_data[3];
  float temp_tilt;
  int c=0;
  int i=0;
  char data[32];
  char string[32];
  /* nrf24l01_initialize_debug(false, 1, false);  // Setup Node at transmitter, Standard Shockburst */
  while(1){
  nrf24l01_initialize_debug(false, 32, true);     // Enhanced Shockburst, Auto Ack turned on
  nrf24l01_clear_flush();
  
  //   nrf24l01base_initialize_debug(true, 1, false);  // setup wifibase as a receiver, Standard Shockburst
  nrf24l01base_initialize_debug(true, 32, true);       // Enhanced Shockburst, Auto Ack turned on
  nrf24l01base_clear_flush();
  
  while(c<9999999)
	{c++;}
  c=0;
  //ds_delay_uS(1000);
  f3d_led_off(5);
  //printf("Enter the angle of rotation");
  printf("\n#### Begin Wifi ####\n");
  ds_accel_read(accel_data);
  ax = accel_data[0];
  ay = accel_data[1];
  az = accel_data[2];
 float axn = (ax/sqrt(ax*ax+ay*ay+az*az));
 float ayn = (ay/sqrt(ax*ax+ay*ay+az*az));
 pitch = asin(-axn);
 roll = asin(ayn/cos(pitch));
 ds_mag_read(mag_data);
 mx = mag_data[0];
 my = mag_data[1];
 mz = mag_data[2];
 xh = mx*cos(pitch)+mz*sin(pitch);
 yh = mx*sin(roll)*sin(pitch)+(my*cos(roll))-(mz*sin(roll)*cos(pitch));
 printf("xaxis%f ",xh);
 printf("\n");
 printf("yaxis%f ",yh);
 printf("\n");
 tilt=atan(yh/xh)*57.2957795;
printf("calculated tilt%f",tilt);
 temp_tilt=compTilt(tilt,xh,yh);
 printf("\n");
 printf("compensated tilt%f",temp_tilt);
 printf("\n");
 int index=0;
 sprintf(string,"%f",temp_tilt);
 for(i=0;i<strlen(string);i++)
 {data[i]=string[i];
  //printf("%c",data[i]);
}

 
 
/* printf("Node Data: ");
 for (index=0;index<10;index++) {
    printf("%c",data[index]);
  }
  printf("\n");
 */  
  //  printf("Node: transmit character %c\n",data);
  nrf24l01_write_tx_payload(data, 32, true);      // nordic writes a character
  while(!(nrf24l01_irq_pin_active() && (nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active()))); // wait until it is gone

  // Node Listen Mode if the maximum retry limit was not hit
  if (!nrf24l01_irq_max_rt_active()) {
    nrf24l01_irq_clear_all();
    nrf24l01_set_as_rx(true);
  }
  else {
    nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
    nrf24l01_irq_clear_all(); //clear all interrupts
    //    printf("Node: Failed to send %c\n",data);
  } 
  
  // Base Reception
  char rxdata[32];
  while(!(nrf24l01base_irq_pin_active() && nrf24l01base_irq_rx_dr_active()));
  nrf24l01base_read_rx_payload(rxdata, 32);	
  nrf24l01base_irq_clear_all();
  //f3d_led_on(3);
  //ds_delay_uS(10000);
   while(c<9999999)
	{c++;}
  f3d_led_all_off();
  ds_delay_uS(130);

  // Payload Translation
  printf("Base Data: ");
 for (index=0;index<10;index++) {

    printf("%c",rxdata[index]);
  }
  printf("\n");
  
  for (index=0;index<10;index++) {
      rxdata[index]=data[index];
    
  }

  /* printf("Base: receive character: %c\n",rxdata); */
  /* rxdata-=32; */
  //  printf("Base: upcase: %c\n",rxdata);
    
  // Base Transmission
  //  printf("Base: Sending Upcase char: %c\n",rxdata);
  nrf24l01base_set_as_tx();
  nrf24l01base_write_tx_payload(rxdata, 32, true);
  while(!(nrf24l01base_irq_pin_active() && (nrf24l01base_irq_tx_ds_active() || nrf24l01base_irq_max_rt_active())));
  nrf24l01base_irq_clear_all();
  nrf24l01base_set_as_rx(true);

  // Node Reception
 /* char noderx[32];
  while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()));
  nrf24l01_read_rx_payload(noderx, 32);
  f3d_led_on(1);
  ds_delay_uS(10000);
  f3d_led_all_off();

  printf("Node Data: ");
 for (index=0;index<10;index++) {
    printf("%c",noderx[index]);
  }
  printf("\n");

  printf("Node: Receive character %c\n",noderx);   */
  nrf24l01_irq_clear_all();
  ds_delay_uS(130);
  nrf24l01_set_as_tx();
  
  c=0;
  printf("#### End Wifi ####\n");
  f3d_led_all_on();
  //ds_delay_uS(1000000);
   while(c<9999999)
	{c++;}
  f3d_led_all_off();	
  /*while (1) {
    if (systick_flag) {
      systick_flag=0;
      schedule();
    }*/
    //}
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
