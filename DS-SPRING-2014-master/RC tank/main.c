#include <f3d_uart.h>
#include<f3d_accel.h>
#include<math.h>
#include <stdio.h>
#include <gyro.h>
#include <stm32f30x_rtc.h>

int main(void) {
  while(1)
 {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_led_init();
  f3d_uart_init();
  f3d_gyro_init();
  f3d_delay_init();
  f3d_systick_init();
  }
}

