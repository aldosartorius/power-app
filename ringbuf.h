/****************************************************************************
* @Filename  : ringbuf.h
* @Notes     : Single-producer (ISR) / single-consumer (main loop) byte FIFO.
*              Size must be a power of two. Lock-free on Cortex-M (8-bit
*              head/tail indices are written atomically). ISO C90.
*****************************************************************************/
#ifndef RINGBUF_H
#define RINGBUF_H

#define RINGBUF_SIZE 64u   /* power of two; 64 B = 4.5 PC frames */

typedef struct {
    volatile unsigned char head;          /* written only by producer (ISR) */
    volatile unsigned char tail;          /* written only by consumer       */
    volatile unsigned char overflow;      /* bytes dropped, saturates 255   */
    unsigned char buf[RINGBUF_SIZE];
} RingBuf_t;

void RingBuf_Init(RingBuf_t *rb);
void RingBuf_Put(RingBuf_t *rb, unsigned char byte);   /* call from ISR  */
int  RingBuf_Get(RingBuf_t *rb, unsigned char *byte);  /* 1 = got a byte */

#endif
