/* ds_uart.h --- 
 * 
 * Filename: ds_uart.h
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Tue Jan 15 11:13:19 2013
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

#include <stm32f30x.h>
#include <queue.h>

extern queue_t rxbuf;
extern queue_t txbuf;

void ds_uart_init(void);
int putchar(int); 
int getchar(void); 
int getchar_nb(void); 
void flush_uart(void);

/* ds_uart.h ends here */
