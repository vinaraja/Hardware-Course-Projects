/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
* Last-Updated:
* By:
* Update #: 0
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
#include <f3d_led.h>
#include <f3d_button.h>
#include <f3d_uart.h>
#include <queue.h>
#include <f3d_systick.h>
// Simple looping delay function

int delay(int m)
{
  int d;
  int i = 2000000;
  while (i-- > 0)
  {
    asm("nop");/* This stops it optimising code out*/
  }
f3d_button_read();
        d=getchar();
           if(d!=0)
           {
              if(d=='p')
{
if(m==0)
putstring(" North West ");
if(m==1)
                putstring(" N");
if(m==2)
                putstring(" NE");
if(m==3)
                putstring(" E");
if(m==4)
                putstring(" SE");
if(m==5)
                putstring(" S");
if(m==6)
                putstring(" SW");
if(m==7)
                putstring(" W");
if(m==8)
                putstring(" ALL");
if(m==9)
                putstring(" NONE");
                while(1)
{
if(getchar()=='r')
return;
}
}
           }
return;
}

int main(void)
{

f3d_led_init();
f3d_button_init();
f3d_uart_init();
f3d_systick_init();
while(1)
{
f3d_led_on(1);
delay(1);

f3d_led_off(1);
f3d_led_on(2);
delay(2);

f3d_led_off(2);
f3d_led_on(3);
delay(3);

f3d_led_off(3);
f3d_led_on(4);
delay(4);

f3d_led_off(4);
f3d_led_on(5);
delay(5);

f3d_led_off(5);
f3d_led_on(6);
delay(6);

f3d_led_off(6);
f3d_led_on(7);
delay(7);

f3d_led_off(7);
f3d_led_on(0);
delay(0);

f3d_led_off(0);
f3d_led_all_on();
delay(8);

f3d_led_all_off();
delay(9);	
}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
