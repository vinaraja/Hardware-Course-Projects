TEMPLATEROOT = ..

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 

# object files

OBJS=  $(STARTUP) 
OBJS+= main.o ds_led.o ds_button.o ds_uart.o ds_gyro.o ds_i2c.o 
OBJS+= ds_accel.o ds_mag.o ds_systick.o ds_rtc.o queue.o schedule.o
OBJS+= ds_sdcard.o ds_delay.o ds_nordic.o ds_wifibase.o
OBJS+= stm32f30x_spi.o stm32f30x_rcc.o stm32f30x_gpio.o stm32f30x_misc.o 
OBJS+= stm32f30x_usart.o stm32f30x_i2c.o stm32f30x_rtc.o stm32f30x_pwr.o 
OBJS+= stm32f30x_tim.o
OBJS+= newlib_stubs.o nrf24l01.o nrf24l01base.o timer4.o
include $(TEMPLATEROOT)/Makefile.common
