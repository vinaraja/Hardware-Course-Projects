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
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_button.h>
#include <stdio.h>

#define TIMER 20000
void positiveled(float a)
{
 if(a>20 )
{
f3d_led_on(0);f3d_led_off(1);f3d_led_off(2);f3d_led_off(3);f3d_led_off(4);//printf("%s\n","aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}if(a>100.0)
{
f3d_led_on(1);f3d_led_off(2);f3d_led_off(3);f3d_led_off(4);//printf("%s\n","bbbbbbbbbbbbbbbbbbbbbbbbb");
}
if(a>200.0)
{
f3d_led_on(2);f3d_led_off(3);f3d_led_off(4);//printf("%s\n","cccccccccccccccccccccc");
}
if(a>300)
{
f3d_led_on(3);f3d_led_on(4);//printf("%s\n","ddddddddddddddddddddddddddddd");
}  
}
void negativeled(float a)
{
 if(a<-4.0 )
{
f3d_led_on(0);f3d_led_off(1);f3d_led_off(2);f3d_led_off(3);f3d_led_off(4);//printf("%s\n","cccccccccccaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}if(a<-100.0)
{
f3d_led_on(7);f3d_led_off(6);f3d_led_off(5);f3d_led_off(4);//printf("%s\n","gggggggggggbbbbbbbbbbbbbbbbbbbbbbbbb");
}
if(a<-200.0)
{
f3d_led_on(6);f3d_led_off(5);f3d_led_off(4);//printf("%s\n","mmmmmmmmmmmmcccccccccccccccccccccc");
}
if(a<-300)
{
f3d_led_on(5);f3d_led_on(4);//printf("%s\n","kikkkkkkkkkkkkkkkkkkkkkkkddddddddddddddddddddddddddddd");
}  
}

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  int j=0;
  int i=0;
  f3d_uart_init();
  f3d_led_init();
  //f3d_uart_init();
  f3d_gyro_init();
  f3d_button_init();
  float buf[3];
  int c;
 while(1)
{ 

f3d_gyro_getdata(buf);
int k=f3d_button_read();
  while(k ==1)

	{  
	
           	
  	   while(1)
	   {k=f3d_button_read();
           if(k == 0)
	
	  {     
		while(k==0)
		{
                if(j == 0)
		{ 
		 printf("%s\n","X-axis");
		}
		else if(j == 1)
		 printf("%s\n","Y-axis");
		else if(j == 2)
		 printf("%s\n","Z-axis");
		f3d_gyro_getdata(buf);
		float m=buf[j];
		if(m>20.0 || m<-20.0)
		printf("%f\n",buf[j]);
		if(m>20.0)
		{
		positiveled(m);
			}
		else if(m<20.0 && m>-20.0)
		{	//printf("%s","iiiiiiffifififfififi");
		f3d_led_all_off();}
		else negativeled(m);
                c=getchar();
		if(c=='x')
                j=0;
		if(c=='y')
		j=1;
		if(c=='z')
		j=2;
		if(f3d_button_read() == 1){
		if(j==2)
	        {j=0;}
  		else j++;
		break;
		}
		}
		}
	   }
	}
}
//t=getchar();
//printf("%d\n",t);

printf("Reset\n");
  while (1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
printf("%s\n",file);
printf("%d\n",line);
  while (1);
}
#endif

/* main.c ends here */
