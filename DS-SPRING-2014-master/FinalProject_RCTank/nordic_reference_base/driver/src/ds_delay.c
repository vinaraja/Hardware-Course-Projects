/* ds_delay.c --- 
 * 
 * Filename: ds_delay.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb 14 19:56:48 2013 (-0500)
 * Version: 
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */
#include <ds_delay.h> 
#include <ds_led.h>
#include <stdio.h>

void ds_delay_init(void) {
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  uint16_t PrescalerValue = 0;

  __IO uint16_t CCR1_Val = 40961;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  //  PrescalerValue = (uint16_t) ((SystemCoreClock) / 72000000) - 1;
  PrescalerValue = (uint16_t) ((SystemCoreClock) / 36000000) - 1;

  
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

  TIM_Cmd(TIM3, ENABLE);
}

void ds_delay_uS(uint16_t uS_count) {
  if (uS_count >= 1000) {
    uS_count = 1000;
  }
  uS_count *= 36; 
  TIM_Cmd(TIM3, DISABLE);
  TIM_SetCounter(TIM3,0);
  TIM_SetCompare1(TIM3,uS_count);
  TIM_Cmd(TIM3, ENABLE);  
  //   ds_led_on(1);
  while (TIM_GetFlagStatus(TIM3,TIM_FLAG_CC1)==RESET);
  //   ds_led_off(1);
  TIM_ClearFlag(TIM3,TIM_FLAG_CC1);
  TIM_Cmd(TIM3, DISABLE);  
} 



/* ds_delay.c ends here */
