//
// Created by KzMz on 06/09/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "defines.h"
#include "renderer/framebuffer.h"
#include <stdbool.h>

void window_open(const char *title, size2d size);
bool window_should_close(void);
void window_put_pixel(size_t x, size_t y, unsigned int packed_color);
void window_present(void);
void window_close(void);

void window_get_framebuffer(framebuffer* framebuffer);
size2d window_get_framebuffer_size(void);
size2d window_get_window_size(void);

#endif //WINDOW_H