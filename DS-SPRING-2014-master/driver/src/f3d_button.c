/* f3d_button.c --- 
 * 
 * Filename: f3d_button.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Jan 17 16:21:57 2013 (-0500)
 * Version: 
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords
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
#include <f3d_button.h>
#include <stm32f30x.h>
int f3d_button_init() {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  //   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  //  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  GPIO_StructInit(&GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  //  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  GPIO_StructInit(&GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  //  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  GPIO_StructInit(&GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  //  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  
}
uint8_t f3d_button_read() {
  int i = 0;
  if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)) == SET) {
    i = 1;
  }
  else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)) == RESET) {
    i = 2;
  }
  /*else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)) == SET) {
    i = 3;
  }
 else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)) == SET) {
    i = 4;
  }*/
  else i = 0;
  return i;
}

/* f3d_button.c ends here */
