/* ds_accel.c --- 
 * 
 * Filename: ds_accel.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 31 19:38:21 2013 (-0500)
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
#include <ds_i2c.h>
#include <ds_accel.h>

void ds_accel_init() {
  // Accelerometer I2C Address = 0x32 

  uint8_t value = 0; 
 
  value = 0x40|0x07;                 // Normal Power Mode, All Axis Enable (X,Y,Z)
  ds_i2c1_write(0x32, 0x20, &value); // Accel (0x32), Ctrl Reg1 (0x20) 

  value = 0x08;                      // Continuous Update, Little Endian, 2G Sensitivity, High Resolution Mode
  ds_i2c1_write(0x32, 0x23, &value); // Accel (0x32, Ctrl Reg4  (0x23)


  value = 0x10 | 0x80;               // HPF Cutoff 16, High Pass Filter Normal Mode, AO1/AO1 Disable
  ds_i2c1_write(0x32, 0x21, &value); // Accel (0x32, Ctrl Reg2  (0x21)
}

void ds_accel_read(float *accel_data) {
  int16_t raw_data[3];
  uint8_t buffer[6];
  int i;

  ds_i2c1_read(0x32, 0x28, buffer, 6); // Read 6 bytes starting from accel (0x32), starting at register 0x28. 
  for (i=0; i<3; i++) {
    raw_data[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/(uint8_t)16;
    accel_data[i]=(float)raw_data[i]/1000.0;
  }
}

/* ds_accel.c ends here */
   
