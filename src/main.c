#include <stdio.h>
#include "window/window.h"

#define STADIUM_IMPLEMENTATION
#include "stadium/stadium.h"

#define COLOR_IMPLEMENTATION
#include "renderer/color.h"

#define VEC2_IMPLEMENTATION
#include "renderer/vec2.h"

int main(void)
{
    window_open("Software Renderer", (size2d) { .width = 800, .height = 600 });

    colorf clear_color = colorf_from_rgba(0.5f, 0.0f, 1.0f, 1.0f);

    framebuffer framebuffer;
    while (!window_should_close())
    {
        window_get_framebuffer(&framebuffer);

        for (size_t y = 0; y < framebuffer.size.height; ++y)
        {
            for(size_t x = 0; x < framebuffer.size.width; ++x)
            {
                window_put_pixel(x, y, colorf_pack(clear_color));
            }
        }

        window_present();
    }

    window_close();
    return 0;
}