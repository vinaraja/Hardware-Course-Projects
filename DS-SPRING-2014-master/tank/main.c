/* f3d_timer4.c --- 
 * 
 * Filename: f3d_timer4.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Feb 18 09:31:16 2014
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

// Pins PD12 
#include <timer4.h>
#include <ds_led.h>
#include <stdio.h>
#include <stm32f30x.h>
//#include<ds_uart.h>

/*TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
uint32_t pulse_width = 0;	

static void f3d_timer4_pins(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;
  // Pin Initializations

  // Enable the clock to Port D
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

    // Configure PD12 as an output
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

    // Configure PD13 as an output
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
 
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_2);
  
}

void timer4_init(void) {

  // Configure the PortD 12-15 and assign to timer4
  f3d_timer4_pins();	

  // Enable the clock to Timer4 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  // Setup the timebase. 2khz/40 to give a 50Hz period

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 2000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 39;	
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

 
  /* // Setup PWM Output Channel 
   TIM_OCStructInit(&TIM_OCInitStructure); 
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
   TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 
   TIM_OCInitStructure.TIM_Pulse = (uint16_t) (2700); // 1.5mS high time initially.  
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 
   TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
   TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 
   
   TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
   TIM_OC2Init(TIM4, &TIM_OCInitStructure);
   
  // Enable PWM Channel
  TIM_CCxCmd(TIM4,TIM_Channel_1,TIM_CCx_Enable);
  TIM_CCxCmd(TIM4,TIM_Channel_2,TIM_CCx_Enable);
  

  // Enable the timer
  TIM_Cmd(TIM4, ENABLE);
 
}

static int leds[] = {GPIO_Pin_13, GPIO_Pin_14};
void pin_on(int led) {
  // enable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  if ((led>=0) && (led < 2)) {
    GPIOD->BSRR = leds[led];
  }
}



void f3d_hightime_oc1_uS(uint32_t time_uS) {
  uint32_t time_nS = time_uS * 1000;
  time_nS /= 555; 
  TIM_SetCompare1(TIM4,time_nS);
}
void f3d_hightime_oc2_uS(uint32_t time_uS) {
  uint32_t time_nS = time_uS * 1000;
  time_nS /= 555; 
  TIM_SetCompare1(TIM4,time_nS);
}
*/
void main(void)
{
setvbuf(stdin, NULL, _IONBF, 0);
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

ds_led_init();
timer4_init();
//ds_uart_init();
int i=0;
int j=0;
while(i<3000000)
{
pin_off(1);
pin_on(0); 
f3d_hightime_oc1_uS(100);
//f3d_hightime_oc2_uS(50);
i++;
//printf("%c",i);
ds_led_on(2);
 } 
ds_led_off(2);
while(j<3000000)
{
pin_on(1);
pin_on(0); 
//f3d_hightime_oc2_uS(30000);
f3d_hightime_oc1_uS(1000);
j++;
}
pin_off(0);
pin_off(1);
//f3d_hightime_oc1_uS(1000);

}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* f3d_timer4.c ends here */
