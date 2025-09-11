//
// Created by KzMz on 06/09/2025.
//

#include "window.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

static HWND window_handle;
static MSG last_message;
static BITMAPINFO last_info;
static bool is_running;

static unsigned char bitmap_memory[RENDERER_MEMORY_SIZE]; // statically allocated memory
static size2d bitmap_size;
static size2d window_size;

const char CLASS_NAME[]  = "Software Renderer Window Class";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void update_window_size(void);

static void resize_dib(int width, int height)
{
    last_info.bmiHeader = (BITMAPINFOHEADER)
    {
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = width,
        .biHeight = -height,
        .biPlanes = 1,
        .biBitCount = 32,
        .biCompression = BI_RGB,
    };

    memset(bitmap_memory, 0, RENDERER_MEMORY_SIZE);
    bitmap_size = (size2d) {width, height};
}

static void present_buffer(HDC hdc)
{
    StretchDIBits(hdc,
                  0, 0, window_size.width, window_size.height,
                  0, 0, bitmap_size.width, bitmap_size.height,
                  bitmap_memory,
                  &last_info,
                  DIB_RGB_COLORS, SRCCOPY
    );
}

void window_open(const char *title, size2d size)
{
    WNDCLASSA wc =
    {
        .lpfnWndProc   = WindowProc,
        .hInstance     = GetModuleHandle(NULL),
        .lpszClassName = CLASS_NAME,
        .style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
    };

    RegisterClassA(&wc);

    window_handle = CreateWindowA(
        CLASS_NAME,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        size.width, size.height,
        NULL, NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (window_handle == NULL)
    {
        printf("Failed to create window\n");
        return;
    }

    window_size = size;
    resize_dib(size.width, size.height);

    ShowWindow(window_handle, SW_SHOW);
    is_running = true;
}

bool window_should_close(void)
{
    while (PeekMessageA(&last_message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&last_message);
        DispatchMessageA(&last_message);
    }

    return !is_running;
}

void window_put_pixel(size_t x, size_t y, unsigned int packed_color)
{
    if (x < bitmap_size.width && y < bitmap_size.height)
    {
        unsigned int* pixel = (unsigned int*) bitmap_memory;
        pixel += (y * bitmap_size.width) + x;
        *pixel = packed_color;
    }
}

void window_present(void)
{   
    HDC hdc = GetDC(window_handle);

    update_window_size();
    present_buffer(hdc);
    ReleaseDC(window_handle, hdc);
}

void window_get_framebuffer(framebuffer* framebuffer)
{
    framebuffer->buffer = bitmap_memory;
    framebuffer->size = bitmap_size;
}

size2d window_get_framebuffer_size(void)
{
    return bitmap_size;
}

size2d window_get_window_size(void)
{
    return window_size;
}

void window_close(void)
{
    memset(bitmap_memory, 0, RENDERER_MEMORY_SIZE);
}

void update_window_size(void)
{
    RECT rect;
    GetClientRect(window_handle, &rect);
    window_size.width = rect.right - rect.left;
    window_size.height = rect.bottom - rect.top;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (uMsg)
    {
        case WM_ACTIVATEAPP:
        {

        } break;

        case WM_SIZE:
        {
            //RECT rect;
            //GetClientRect(hwnd, &rect);
            //int width = rect.right - rect.left;
            //int height = rect.bottom - rect.top;
            //resize_dib(width, height);
        } break;

        case WM_CLOSE:
        case WM_DESTROY:
        {
            is_running = false;
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            update_window_size();
            present_buffer(hdc);

            EndPaint(hwnd, &ps);
        } break;

        default:
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } break;
    }
    return result;
}