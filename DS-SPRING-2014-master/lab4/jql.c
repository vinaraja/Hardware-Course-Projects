#include<f3d_systick.h>
#include<stdio.h>
#include <f3d_button.h>
#include <math.h>
static int j=0;
static int k=0;
static int m=0;
static int n=0;
static int16_t l[9000];
static int32_t z[300];
static uint8_t pu8[3] ={0};
float Raw[3]={0};
void f3d_systick_init(void)
{
// Setup a systick rate of 100hz.
    SysTick_Config(SystemCoreClock/100);
    setvbuf(stdin, NULL, _IONBF, 0);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);

}


void print_val(void)
{
int i;
int y=0;
float pressure1;
float Altitude_ft;
for(i=0;i<8999;i=i+3){
    Raw[0]=(float)l[i]/L3G_Sensitivity_500dps;
    Raw[1]=(float)l[i+1]/L3G_Sensitivity_500dps;
    Raw[2]=(float)l[i+2]/L3G_Sensitivity_500dps;
    printf("%f",Raw[0]);
    printf(",");
    printf("%f",Raw[1]);
    printf(",");
    printf("%f",Raw[2]);
    printf(",");
    if(i%30==0){
    pressure1 = z[0] / 4096;
   // printf("%d",y);
    Altitude_ft = (1-pow(pressure1/1013.25,0.190284))*145366.45;
    printf("%f",Altitude_ft);}
    printf("\n");
}

}   


void SysTick_Handler(void)
{
   


    k++;
    j++;
    static state = 0;
    int systick_flag;
     USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
   
    if(k%10==0 && k<30000)
    {
    int16_t pfData[3];
    f3d_gyro_getdata(pfData);
   
   
    int i;
    for(i=0; i<3; i++) {
    l[m]= pfData[i];
    m++;
    }
   
    if(j%100==0)
    {
           
        state ^= 1;
        if (state==1)
            GPIOE->BSRR = GPIO_Pin_9;   
        else
            GPIOE->BRR = GPIO_Pin_9;
        systick_flag = 1;
       
        f3d_sensor_read(pu8, 0x28, 3);//READING PRESSURE
            uint32_t pressure = ((uint32_t)pu8[2]<<16)|((uint32_t)pu8[1]<<8)|pu8[0]; // make a unsigned 32 bit variable
        //z[0]=pressure;     
        //n++;
        //float b=pressure;
	
    
    }
}







}
