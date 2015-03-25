#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>
#include<queue.h>
#include<f3d_gyro.h>
#include<f3d_systick.h>
#include<f3d_delay.h>
#include <sensor.h>
#include <f3d_timer4.h>
#include <f3d_sdcard.h>
#include <diskio.h>
#include<string.h>
#include<f3d_accel.h>
#include<f3d_mag.h>
#include<math.h>
#include <stm32f30x_rtc.h>

float compTilt(float temp, float xaxis, float yaxis)
{
if(xaxis>0.0 && yaxis>0.0)
{return temp+180.0;}
if(xaxis>0.0 && yaxis<0.0)
{return(temp+180.0);}
if(xaxis<0.0 && yaxis<0.0)
{return(temp);}
if(xaxis<0.0 && yaxis>0.0)
{return(temp+360.0);}
}

void main(void) 
{
f3d_systick_init();
f3d_uart_init();
f3d_i2c1_init();
f3d_accel_init();
f3d_mag_init();
f3d_led_init();
f3d_delay_init();
setvbuf(stdin, NULL, _IONBF, 0);
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
float accel_data[3];
float mag_data[3];
//int c;
float tilt,pitch,roll,xh,yh,mx,my,mz,ax,ay,az,temp_tilt,axn,ayn,tilt1;
while(1)
{


f3d_accel_read(accel_data);

ax = accel_data[0];
ay = accel_data[1];
az = accel_data[2];

f3d_mag_read(mag_data);

mx = mag_data[0];
my = mag_data[1];
mz = mag_data[2];
axn = (ax/sqrt(ax*ax+ay*ay+az*az));
ayn = (ay/sqrt(ax*ax+ay*ay+az*az));
pitch = asin(-axn);
roll = asin(ayn/cos(pitch));
xh = mx*cos(pitch)+mz*sin(pitch);
yh = mx*sin(roll)*sin(pitch)+(my*cos(roll))-(mz*sin(roll)*cos(pitch));
tilt=atan(yh/xh)*57.2957795;\
printf("x-axis:%f",mx);
printf("y-axis:%f",my);
printf("z-axis:%f\n",mz);
//printf("x-axis:%f\n",xh);
//printf("y-axis:%f\n",yh);
//printf("head direction:%f\n",tilt);
temp_tilt=compTilt(tilt,xh,yh);
printf("rotation:%f\n ",temp_tilt);
}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  printf("Assertion: %s %d\n",file, line);
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif
