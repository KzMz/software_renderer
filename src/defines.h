//
// Created by KzMz on 06/09/2025.
//

#ifndef DEFINES_H
#define DEFINES_H

#include <stddef.h>

#define PI 3.14159265358979323846

#define UNUSED(x) (void)(x)

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080
#define BYTES_PER_PIXEL 4

#define RENDERER_MEMORY_SIZE (MAX_WIDTH * MAX_HEIGHT * BYTES_PER_PIXEL)

typedef struct size2d
{
    size_t width;
    size_t height;
} size2d;

#endif //DEFINES_H