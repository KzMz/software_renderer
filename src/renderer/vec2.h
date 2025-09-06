#ifndef VEC2_H
#define VEC2_H

#include <math.h>

typedef union vec2
{
    struct
    {
        float x;
        float y;
    };
    struct
    {
        float u;
        float v;
    };
    float data[2];
} vec2;

vec2 vec2_new(float x, float y);

vec2 vec2_add(vec2 a, vec2 b);
void vec2_add_this(vec2* a, vec2 b);

vec2 vec2_sub(vec2 a, vec2 b);
void vec2_sub_this(vec2* a, vec2 b);

vec2 vec2_mul(vec2 a, vec2 b);
void vec2_mul_this(vec2* a, vec2 b);

vec2 vec2_div(vec2 a, vec2 b);
void vec2_div_this(vec2* a, vec2 b);

vec2 vec2_scale(vec2 v, float s);
void vec2_scale_this(vec2* v, float s);

float vec2_dot(vec2 a, vec2 b);
float vec2_length(vec2 v);

vec2 vec2_normalize(vec2 v);
void vec2_normalize_this(vec2* v);

vec2 vec2_lerp(vec2 a, vec2 b, float t);

#ifdef VEC2_IMPLEMENTATION

vec2 vec2_new(float x, float y)
{
    return (vec2) {{ x, y }};
}

vec2 vec2_add(vec2 a, vec2 b)
{
    return (vec2) {{ a.x + b.x, a.y + b.y }};
}

void vec2_add_this(vec2* a, vec2 b)
{
    a->x += b.x;
    a->y += b.y;
}

vec2 vec2_sub(vec2 a, vec2 b)
{
    return (vec2) {{ a.x - b.x, a.y - b.y }};
}

void vec2_sub_this(vec2* a, vec2 b)
{
    a->x -= b.x;
    a->y -= b.y;
}

vec2 vec2_mul(vec2 a, vec2 b)
{
    return (vec2) {{ a.x * b.x, a.y * b.y }};
}

void vec2_mul_this(vec2* a, vec2 b)
{
    a->x *= b.x;
    a->y *= b.y;
}

vec2 vec2_div(vec2 a, vec2 b)
{
    return (vec2) {{ a.x / b.x, a.y / b.y }};
}

void vec2_div_this(vec2* a, vec2 b)
{
    a->x /= b.x;
    a->y /= b.y;
}

vec2 vec2_scale(vec2 v, float s)
{
    return (vec2) {{ v.x * s, v.y * s }};
}

void vec2_scale_this(vec2* v, float s)
{
    v->x *= s;
    v->y *= s;
}

float vec2_dot(vec2 a, vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

float vec2_length(vec2 v)
{
    return sqrtf(vec2_dot(v, v));
}

vec2 vec2_normalize(vec2 v)
{
    float length = vec2_length(v);
    if (length != 0.0f)
    {
        return vec2_scale(v, 1.0f / length);
    }
    return v;
}

void vec2_normalize_this(vec2* v)
{
    float length = vec2_length(*v);
    if (length != 0.0f)
    {
        vec2_scale_this(v, 1.0f / length);
    }
}

vec2 vec2_lerp(vec2 a, vec2 b, float t)
{
    return vec2_add(a, vec2_scale(vec2_sub(b, a), t));
}

#endif //VEC2_IMPLEMENTATION

#endif //VEC2_H