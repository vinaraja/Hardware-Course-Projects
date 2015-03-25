#include <stm32f30x.h>

static void f3d_timer4_pins(void); 
void timer4_init(void);
void f3d_frequency4(uint32_t freq);
void f3d_hightime_oc1_uS4(uint32_t time_uS);
static void f3d_timer2_pins(void); 
void timer2_init(void);
void f3d_frequency(uint32_t freq);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
