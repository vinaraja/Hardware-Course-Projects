/* queue.c --- 
 * 
 * Filename: queue.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb  7 19:49:26 2013 (-0500)
 * Version: 
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */

#include "queue.h"

void init_queue(queue_t *buf) {
  buf->head=0;
  buf->tail=0;
}

int enqueue (queue_t *buf, int data) {
  int return_val=0;
  if ((((buf->head)+1)%QUEUE_SIZE)!=buf->tail) {
    buf->buffer[buf->head]=data;   
    buf->head=((buf->head)+1)%QUEUE_SIZE;
    return_val=1;
  }
  else {
    return_val=0;
  }
  return (return_val);
}

int dequeue (queue_t *buf) {
  int return_val=0;
  if (buf->tail!=buf->head) {
    return_val=buf->buffer[buf->tail];
    buf->tail=((buf->tail)+1)%QUEUE_SIZE;
  }
  return(return_val);
}

int queue_empty(queue_t *buf) {
  int retval = 0;
  if (buf->head==buf->tail) {
    retval=1;
  }
  return (retval);
}


/* queue.c ends here */
