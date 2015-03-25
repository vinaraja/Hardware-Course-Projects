#include <stm32f30x.h>

static void f3d_timer4_pins(void); 
void timer4_init(void);
void f3d_hightime_oc1_uS(uint32_t time_uS);
void f3d_hightime_oc2_uS(uint32_t time_uS);
void pin_on(int led);
void pin_off(int led);
