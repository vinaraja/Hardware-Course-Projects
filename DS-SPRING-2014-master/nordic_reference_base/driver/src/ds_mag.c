/* ds_mag.c --- 
 * 
 * Filename: ds_mag.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 31 19:38:44 2013 (-0500)
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

/* Code: */
#include <ds_mag.h>

void ds_mag_init() {
  // MAG I2C Address = 0x3C 

  uint8_t value = 0; 
 
  value = 0x14;                  //Temp sensor disable,30Hz Output Rate 
  ds_i2c1_write(0x3C, 0x00,  &value); // Mag (0x3C), CRA (0x00) 

  value = 0xE0;                      // +/- 8.1 Gauss Full Scale
  ds_i2c1_write(0x3C, 0x01, &value); // Mag (0x3C), CRB (0x01)

  value = 0x00;                      // Continuous Conversion
  ds_i2c1_write(0x3C, 0x02, &value); // Mag (0x3C), MR  (0x23)
}

void ds_mag_read(float *mag_data) {
  uint8_t buffer[6];
  int i;
  
  ds_i2c1_read(0x3C, 0x03, buffer,2);   // Read X Axis
  ds_i2c1_read(0x3C, 0x07, buffer+2,2); // Read Y Axis
  ds_i2c1_read(0x3C, 0x05, buffer+4,2); // Read Z Axis (notice that Z is out of order in the chip). 
  
  for (i=0; i<2; i++) {
    mag_data[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]))/230;
  }
  mag_data[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]))/205;
}

/* ds_mag.c ends here */
