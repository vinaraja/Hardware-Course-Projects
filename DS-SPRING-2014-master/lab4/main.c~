#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_button.h>
#include <f3d_uart.h>
#include<stdio.h>
#include<queue.h>
#include<f3d_gyro.h>
#include<f3d_systick.h>
#include <sensor.h>

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    uint8_t ctrl1=0x00;
    f3d_led_init();
    f3d_button_init();
    f3d_uart_init();
    f3d_gyro_init();  
    f3d_sensor_interface_init();
    f3d_sensor_init();
    int j=0;
    while(1){
    j=f3d_button_read();
    if(j==1)
    {
    f3d_systick_init();
    j=f3d_button_read();
    if(j==0)
    {
    while(1){   
    j=f3d_button_read();
    if(j==1)
    print_val();}}}
    
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{

printf("Assert Called!");

/* Infinite loop */
/* Use GDB to find out why we're here */
    while (1);

}
#endif
