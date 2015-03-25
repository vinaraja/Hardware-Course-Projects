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
  char command[8];
  char data[8];
  char index,h;
  int c;
  int r,t,v;
  int k=0;
  int count=0;
  float val =0;
  float val1,val2;
  char rxdata[8];
  bool flag = true;
  float value = 0;
  //   nrf24l01base_initialize_debug(true, 1, false);  // setup wifibase as a receiver, Standard Shockburst
  nrf24l01base_initialize_debug(false,8, true);       // Enhanced Shockburst, Auto Ack turned on
  nrf24l01base_clear_flush();
  while(1)
  {
  	nrf24l01base_clear_flush();
  	printf("Enter the angle of rotation(less than 360) and time(less than 100) : ");
  
  	for(c=0;c<6;c++)
  	{     
		while(h=getchar())
		{
        		//printf("value");
			command[c]=putchar(h);
			//printf("value is%c\n ",command[c]);
			break;
		}
  	}
	if (!nrf24l01base_irq_max_rt_active()) {
    		nrf24l01base_irq_clear_all();
    		nrf24l01base_set_as_rx(true);
  	}
  	else {
    		nrf24l01base_flush_tx(); //get the unsent character out of the TX FIFO
    		nrf24l01base_irq_clear_all(); //clear all interrupts
    		//    printf("Node: Failed to send %c\n",data);
  	} 
 	val1=0;
 	val=0;
 	val2=0;
	val1 = val1 + 100*((float)(command[0]-'0'));
	val1 = val1 + 10*((float)(command[1]-'0')); 
	val1 = val1 + ((float)(command[2]-'0')); 

	val2 = val2 + 10*((float)(command[4]-'0')); 
	val2 = val2 + ((float)(command[5]-'0')); 
			
  	printf("val1 %f  \n",val1);
	printf("val2 %f  \n",val2);
 
  	printf("aya");
	nrf24l01base_set_as_tx();       // Enhanced Shockburst, Auto Ack turned on
  	while(k<10)
 	{     	
		printf("in");
 		nrf24l01base_write_tx_payload(command,8, true);
		ds_delay_uS(130);
		printf("sending....\n");
		k++;
  	}
  	printf("gone");
  	while(!(nrf24l01base_irq_pin_active() && (nrf24l01base_irq_tx_ds_active() || nrf24l01base_irq_max_rt_active())));
  	ds_delay_uS(130);
        nrf24l01base_initialize_debug(true,8, true);
	       // Enhanced Shockburst, Auto Ack turned on
  	while(1){
  		nrf24l01base_set_as_rx(true);
  		// Base Reception
  		//printf("hi");
		ds_delay_uS(130);
		printf("hello");
  		while(!(nrf24l01base_irq_pin_active() && nrf24l01base_irq_rx_dr_active()));
		printf("hello");
  		ds_led_on(3);
  		nrf24l01base_read_rx_payload(rxdata,8);
		nrf24l01base_irq_clear_all();
  		ds_delay_uS(130);

  		// Payload Translation
 
 	 	printf("Node Data: ");
  		for (index=0;index<8;index++) {
			data[index]=rxdata[index];
    			printf("%c",rxdata[index]);
  		}
                val=0;
   		
  		printf("rxdata[0]: %c  \n",rxdata[0]);
		printf("rxdata[1]: %c  \n",rxdata[1]);
		printf("rxdata[2]: %c  \n",rxdata[2]);
		if(rxdata[2]=='.')
		{
			val = val + 10*((float)(rxdata[0]-'0')); //printf("10s:\t %f  \n",val);
			val = val + ((float)(rxdata[1]-'0')); //printf("1s:\t %f  \n",val);
		}
		else
		{
			val = val + 100*((float)(rxdata[0]-'0')); //printf("100s:\t %f  \n",val);
			val = val + 10*((float)(rxdata[1]-'0')); //printf("10s:\t %f  \n",val);
			val = val + ((float)(rxdata[2]-'0')); //printf("1s:\t %f  \n",val);
		}
		printf("hiiiiiiiiiii");
  		if(val == val1){
			printf("Current Heading: %f  \n",val);
			break;
  			printf("\n");
 		}
		//nrf24l01base_irq_clear_all();
	}
 	 printf("#### End of motion ####\n");
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
