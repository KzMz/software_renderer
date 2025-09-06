#include <stdio.h>
#include "window/window.h"

#define STADIUM_IMPLEMENTATION
#include "stadium/stadium.h"

int main(void)
{
    window_open("Software Renderer", (size2d) { .width = 800, .height = 600 });

    framebuffer framebuffer;
    while (!window_should_close())
    {
        window_get_framebuffer(&framebuffer);

        size_t pitch = framebuffer.size.width * 4;
        unsigned char* row = framebuffer.buffer;
        for (size_t y = 0; y < framebuffer.size.height; ++y)
        {
            unsigned char* pixel = row;
            UNUSED(pixel);
            for(size_t x = 0; x < framebuffer.size.width; ++x)
            {
                *pixel = 255;
                ++pixel;

                *pixel = 0;
                ++pixel;

                *pixel = 0;
                ++pixel;

                *pixel = 255;
                ++pixel;
            }
            row += pitch;
        }
    }

    window_close();
    return 0;
}