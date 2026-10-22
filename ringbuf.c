#include "ringbuf.h"

#define RB_MASK (RINGBUF_SIZE - 1u)

void RingBuf_Init(RingBuf_t *rb)
{
    rb->head = 0u;
    rb->tail = 0u;
    rb->overflow = 0u;
}

void RingBuf_Put(RingBuf_t *rb, unsigned char byte)
{
    unsigned char next = (unsigned char)((rb->head + 1u) & RB_MASK);

    if (next == rb->tail) {                 /* full: drop newest byte */
        if (rb->overflow < 255u) {
            rb->overflow++;
        }
        return;
    }
    rb->buf[rb->head] = byte;
    rb->head = next;
}

int RingBuf_Get(RingBuf_t *rb, unsigned char *byte)
{
    if (rb->tail == rb->head) {
        return 0;
    }
    *byte = rb->buf[rb->tail];
    rb->tail = (unsigned char)((rb->tail + 1u) & RB_MASK);
    return 1;
}
