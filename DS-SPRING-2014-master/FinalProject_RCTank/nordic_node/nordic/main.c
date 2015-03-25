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
#include <ds_nordic.h>
#include <ds_wifibase.h>
#include <nrf24l01.h>
#include <nrf24l01base.h>
#include <stdio.h>
#include <string.h>
#include<math.h>
#include<timer4.h>

float compTilt(float temp, float xaxis, float yaxis)
{
  if(xaxis>0.0 && yaxis>0.0){return temp+180.0;}
  if(xaxis>0.0 && yaxis<0.0){return(temp+180.0);}
  if(xaxis<0.0 && yaxis<0.0){return(temp);}
  if(xaxis<0.0 && yaxis>0.0){return(temp+360.0);}
}
int main(void) {
  
  int i=0;
  float j=0;
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
  ds_nordic_init();
  ds_wifibase_init();
  timer4_init();
  ds_led_all_off();
  int flag=0;
  while(1){
  int r;
  //float q=90.0;
  float axn,ayn;
  char rxdata[8];
  /* nrf24l01_initialize_debug(false, 1, false);  // Setup Node at transmitter, Standard Shockburst */
  ds_delay_uS(130);
  nrf24l01_initialize_debug(true,8, true);     // Enhanced Shockburst, Auto Ack turned on
  nrf24l01_set_as_rx(true);
  nrf24l01_clear_flush();
  //char rcv_command[3];
  float val = 0;
  float val2 = 0;
  ds_led_on(2);
  //printf("hello");
  printf("waiting for value...");
  while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()));
  ds_led_on(6);
  nrf24l01_read_rx_payload(rxdata,8);	
  nrf24l01_irq_clear_all();
  ds_delay_uS(130);
  val = val + 100*((float)(rxdata[0]-'0'));
  val = val + 10*((float)(rxdata[1]-'0'));
  val = val + ((float)(rxdata[2]-'0')); 
  val2 = val2 + 10*((float)(rxdata[4]-'0'));
  val2 = val2 + ((float)(rxdata[5]-'0')); 

  printf("Value sent by user is%f\n",val);
  printf("Time sent by user is%f\n",val2);	
  //   nrf24l01base_initialize_debug(true, 1, true);  // setup wifibase as a receiver, Standard Shockburst
  //nrf24l01base_initialize_debug(true, 32, true);       // Enhanced Shockburst, Auto Ack turned on
 // nrf24l01base_clear_flush();

  
 
  // Node Transmission
  char data[8];
  char string[8];
  float tilt,pitch,roll,xh,yh,mx,my,mz,ax,ay,az,tilt1;
  float accel_data[3];
  float mag_data[3];
  float temp_tilt=0.0;
  float temp_tilt1;
  int index=0;
  int m=0;
  int km;
  int sv;
  ds_accel_read(accel_data);
  ax = accel_data[0];
  ay = accel_data[1];
  az = accel_data[2];
  axn = (ax/sqrt(ax*ax+ay*ay+az*az));
  ayn = (ay/sqrt(ax*ax+ay*ay+az*az));
  pitch = asin(-axn);
  roll = asin(ayn/cos(pitch));
  ds_mag_read(mag_data);
  mx = mag_data[0];
  my = mag_data[1];
  mz = mag_data[2];
  xh = mx*cos(pitch)+mz*sin(pitch);
  yh = mx*sin(roll)*sin(pitch)+(my*cos(roll))-(mz*sin(roll)*cos(pitch));
  printf("\n");
  printf("\n");
  tilt=atan(yh/xh)*57.2957795;
  temp_tilt1=compTilt(tilt,xh,yh);
  printf("calculated tilt%f",temp_tilt1);
  if(val <= temp_tilt1 && flag==0) 
 	{        nrf24l01_set_as_tx();
 		 while(temp_tilt < (val-5.0)||temp_tilt > val+5.0){
   			pin_off(1);
  			pin_on(0); 
		        //f3d_hightime_oc1_uS(12000);
		        f3d_hightime_oc1_uS(0);
			f3d_hightime_oc2_uS(4000);
   			ds_led_on(6);
   			ds_accel_read(accel_data);
  			ax = accel_data[0];
  			ay = accel_data[1];
  			az = accel_data[2];
  			axn = (ax/sqrt(ax*ax+ay*ay+az*az));
  			ayn = (ay/sqrt(ax*ax+ay*ay+az*az));
  			pitch = asin(-axn);
  			roll = asin(ayn/cos(pitch));
  			ds_mag_read(mag_data);
  			mx = mag_data[0];
  			my = mag_data[1];
  			mz = mag_data[2];
  			xh = mx*cos(pitch)+mz*sin(pitch);
  			yh = mx*sin(roll)*sin(pitch)+(my*cos(roll))-(mz*sin(roll)*cos(pitch));
  			tilt=atan(yh/xh)*57.2957795;
			//printf("calculated tilt%f",tilt);
 			temp_tilt=compTilt(tilt,xh,yh);
	 		//printf("compensated tilt%f\n",temp_tilt);
 			sprintf(string,"%f",temp_tilt);
  			//printf("stringgggggggggggggggggggggggg%s",string);
  			for(index=0;index<strlen(string);index++){
				data[index]=string[index];
  				printf("%c",data[index]);
  			}
  			printf("\n");
  			//printf("Node: transmit character %c\n",data);
  			while(km<1000000)
			{km++;}
			km=0;
  			nrf24l01_write_tx_payload(data, 8, true);      // nordic writes a character
			printf("sending data...");
  			while(!(nrf24l01_irq_pin_active() && (nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active())));// wait until it is gone
			if (!nrf24l01_irq_max_rt_active()) {
    				nrf24l01_irq_clear_all();
    				nrf24l01_set_as_rx(true);
  			}
  			else {
    				nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
    				nrf24l01_irq_clear_all(); //clear all interrupts
    				//    printf("Node: Failed to send %c\n",data);
  			} 
			printf("value transmitted");
  			nrf24l01_irq_clear_all();
  			ds_led_on(1); 
  
   
  		}
            	flag=1;
		sv=0;
		while(sv<20){
			nrf24l01_write_tx_payload("$", 8, true);
			sv++;
		}
		sv=0;
		while(!(nrf24l01_irq_pin_active() && (nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active())));// wait until it is gone
			if (!nrf24l01_irq_max_rt_active()) {
    				nrf24l01_irq_clear_all();
    				nrf24l01_set_as_rx(true);
  			}
  			else {
    				nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
    				nrf24l01_irq_clear_all(); //clear all interrupts
    				//    printf("Node: Failed to send %c\n",data);
  			} 
			printf("value transmitted");
  			nrf24l01_irq_clear_all();
  			ds_led_on(1); 
	}
 
  else if(val > temp_tilt1 && flag==0) 
	{	nrf24l01_set_as_tx();
		while(temp_tilt < (val-10.0)||temp_tilt > val+10)
  		{       
   			pin_on(1);
  			pin_off(0); 
  			//f3d_hightime_oc1_uS(12000);
  			ds_led_on(8);
			f3d_hightime_oc1_uS(1000);
  			//f3d_hightime_oc2_uS(0);
 			//printf("hello");
   			ds_accel_read(accel_data);
  			ax = accel_data[0];
  			ay = accel_data[1];
  			az = accel_data[2];
  			axn = (ax/sqrt(ax*ax+ay*ay+az*az));
  			ayn = (ay/sqrt(ax*ax+ay*ay+az*az));
  			pitch = asin(-axn);
  			roll = asin(ayn/cos(pitch));
  			ds_mag_read(mag_data);
  			mx = mag_data[0];
  			my = mag_data[1];
  			mz = mag_data[2];
  			xh = mx*cos(pitch)+mz*sin(pitch);
  			yh = mx*sin(roll)*sin(pitch)+(my*cos(roll))-(mz*sin(roll)*cos(pitch));
  			tilt=atan(yh/xh)*57.2957795;
			//printf("calculated tilt%f",tilt);
 			temp_tilt=compTilt(tilt,xh,yh);
 			//printf("compensated tilt%f\n",temp_tilt); 
  			sprintf(string,"%f",temp_tilt);
  			//printf("stringgggggggggggggggggggggggg%s",string);
  			for(index=0;index<strlen(string);index++){
				data[index]=string[index];
  				printf("%c",data[index]);
  			}
  			printf("\n");
  			//printf("Node Data: ");
  			for (index=0;index<strlen(string);index++) {
  	  			printf("%c",data[index]);
  			}
  			//  printf("Node: transmit character %c\n",data);
  			while(km<1000000)
			{km++;}
			km=0;
  			nrf24l01_write_tx_payload(data, 8, true);      // nordic writes a character
			printf("sending data...");
  			while(!(nrf24l01_irq_pin_active() && (nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active())));// wait until it is gone
			if (!nrf24l01_irq_max_rt_active()) {
    				nrf24l01_irq_clear_all();
    				nrf24l01_set_as_rx(true);
  			}
  			else {
    				nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
    				nrf24l01_irq_clear_all(); //clear all interrupts
    				//    printf("Node: Failed to send %c\n",data);
  			} 
			printf("value transmitted");
  			nrf24l01_irq_clear_all();
  			ds_led_on(2); 
   
  		}
            	flag=1;
		sv=0;
		while(sv<20){
			nrf24l01_write_tx_payload("$", 8, true);
			sv++;
		}
		sv=0;
		nrf24l01_write_tx_payload("$", 8, true);
		while(!(nrf24l01_irq_pin_active() && (nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active())));// wait until it is gone
			if (!nrf24l01_irq_max_rt_active()) {
    				nrf24l01_irq_clear_all();
    				nrf24l01_set_as_rx(true);
  			}
  			else {
    				nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
    				nrf24l01_irq_clear_all(); //clear all interrupts
    				//    printf("Node: Failed to send %c\n",data);
  			} 
			printf("value transmitted");
  			nrf24l01_irq_clear_all();
  			ds_led_on(1); 
	}
  while(j < (val2*200000))
 	{
 		ds_led_off(2);
 		pin_on(1);
 		pin_on(0); 
 		//f3d_hightime_oc2_uS(1000);
 		f3d_hightime_oc1_uS(1000);
 		j++;
 	}
 j = 0;	
 pin_off(1);
 pin_off(0); 
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
