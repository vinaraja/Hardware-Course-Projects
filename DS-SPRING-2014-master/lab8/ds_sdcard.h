/* ds_sdcard.h --- 
 * 
 * Filename: ds_sdcard.h
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb 14 09:28:11 2013 (-0500)
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
#include <stm32f30x.h>

#define SD_CS_LOW()   GPIO_ResetBits(GPIOC, GPIO_Pin_0);
#define SD_CS_HIGH()  GPIO_SetBits(GPIOC, GPIO_Pin_0);

void ds_sd_interface_init(void);
void ds_sdcard_readwrite(uint8_t *, uint8_t *, int); 
uint32_t get_fattime(void);

/* ds_sdcard.h ends here */
