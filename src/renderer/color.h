#ifndef COLOR_H
#define COLOR_H

typedef union color
{
    struct
    {
        unsigned char r, g, b, a;
    };
    unsigned char data[4];
} color;

typedef union colorf
{
    struct
    {
        float r, g, b, a;
    };
    float data[4];
} colorf;

color color_from_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
colorf colorf_from_rgba(float r, float g, float b, float a);
colorf colorf_from_color(color c);
color color_from_colorf(colorf c);
int color_pack(color c);
int colorf_pack(colorf c);

#ifdef COLOR_IMPLEMENTATION

color color_from_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (color) {{r, g, b, a}};
}

colorf colorf_from_rgba(float r, float g, float b, float a)
{
    return (colorf) {{r, g, b, a}};
}

colorf colorf_from_color(color c)
{
    return (colorf) {{
        c.r / 255.0f,
        c.g / 255.0f,
        c.b / 255.0f,
        c.a / 255.0f
    }};
}

color color_from_colorf(colorf c) 
{
    return (color)  {{
        (unsigned char)(c.r * 255.0f),
        (unsigned char)(c.g * 255.0f),
        (unsigned char)(c.b * 255.0f),
        (unsigned char)(c.a * 255.0f)
    }};
}

int color_pack(color c)
{
    return (int)((c.r << 24) | (c.g << 16) | (c.b << 8) | c.a);
}

int colorf_pack(colorf c)
{
    return (int)((int)(c.r * 255.0f) << 24 | (int)(c.g * 255.0f) << 16 | (int)(c.b * 255.0f) << 8 | (int)(c.a * 255.0f));
}

#endif // COLOR_IMPLEMENTATION

#endif // COLOR_H