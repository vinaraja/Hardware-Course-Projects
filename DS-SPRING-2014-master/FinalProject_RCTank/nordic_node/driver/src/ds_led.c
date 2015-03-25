/* led.c --- 
 * 
 * Filename: led.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 10:53:06 2013
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
#include <ds_led.h>

static int leds[] = {GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,\
		     GPIO_Pin_12,GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};

void ds_led_init(void) {
  // initialize the port and pins for the 8 leds
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|\
    GPIO_Pin_10|GPIO_Pin_11|\
    GPIO_Pin_12|GPIO_Pin_13|\
    GPIO_Pin_14|GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void ds_led_on(int led) {
  // enable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  if ((led>=0) && (led <= 8)) {
    GPIOE->BSRR = leds[led];
  }
}
 
void ds_led_off(int led) {
  // disable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  if ((led>=0) && (led <= 8)) {
    GPIOE->BRR = leds[led];
  }
} 

void ds_led_all_on(void) {
  // turn on all 8 leds 
  GPIOE->BSRR = 0xFF00;
} 

void ds_led_all_off(void) {
  // turn off all 8 leds
  GPIOE->BRR = 0xFF00;
} 

/* led.c ends here */

