#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "defines.h"
#include <stddef.h>
#include <stdint.h>

typedef struct framebuffer
{
    unsigned char* buffer;
    size2d size;
} framebuffer;

#endif //FRAMEBUFFER_H