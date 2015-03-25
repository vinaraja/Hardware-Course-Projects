/* ds_sdcard.c --- 
 * 
 * Filename: ds_sdcard.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb 14 09:27:52 2013 (-0500)
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

#include <ds_sdcard.h>
#include <ds_rtc.h>
#include <stdio.h>

// PB13  SCK
// PB14  MISO
// PB15  MOSI
// PC0   nCS

void ds_sdcard_interface_init() {
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  // Initialization for SCK, MISO, MOSI
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_5);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI2);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Configure the RX FIFO Threshold */
  SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
  /* Enable SPI1  */
  SPI_Cmd(SPI2, ENABLE);

  /* Configure GPIO PIN for Lis Chip select */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Deselect : Chip Select high */
  GPIO_SetBits(GPIOC, GPIO_Pin_0);
} 

void ds_sdcard_readwrite(uint8_t *rxbuf, uint8_t *txbuf, int count) {
  int index;

  for (index=0;index<count;index++) {
    if (txbuf) {
      SPI_SendData8(SPI2, *txbuf++);
    }
    else {
      SPI_SendData8(SPI2, 0xFF);
    }
    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET);
    if (rxbuf) {
      *rxbuf++ = (uint8_t) SPI_ReceiveData8(SPI2);
    }
    else {
      SPI_ReceiveData8(SPI2);      
    }
  }
}

uint32_t get_fattime(void) {
  // Return a packed 32-bit word 
  // bit31:25 Year from 1980 (0..127)
  // bit24:21 Month (1..12)
  // bit20:16 Day in month(1..31)
  // bit15:11 Hour (0..23)
  // bit10:5 Minute (0..59)
  // bit4:0 Second / 2 (0..29)
  uint32_t compressed_time = 0;
  uint32_t temp = 0;
  RTC_DateTypeDef RTC_DateStructure;
  RTC_TimeTypeDef RTC_TimeStructure;

  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure); 
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  
  //  printf("%d\n",RTC_DateStructure.RTC_Year);
  compressed_time |= (((2000-1980) + RTC_DateStructure.RTC_Year) << 25);
  compressed_time |= (RTC_DateStructure.RTC_Month << 21);
  compressed_time |= (RTC_DateStructure.RTC_Date << 16);
  compressed_time |= (RTC_TimeStructure.RTC_Hours << 11);
  compressed_time |= (RTC_TimeStructure.RTC_Minutes<<5);
  compressed_time |= RTC_TimeStructure.RTC_Seconds/2;
  return (compressed_time);
}



