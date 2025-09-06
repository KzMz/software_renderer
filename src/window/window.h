//
// Created by KzMz on 06/09/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "defines.h"
#include <stdbool.h>

typedef struct framebuffer
{
    unsigned char* buffer;
    size2d size;
} framebuffer;

void window_open(const char *title, size2d size);
bool window_should_close(void);
void window_present(void);
void window_close(void);

void window_get_framebuffer(framebuffer* framebuffer);

#endif //WINDOW_H