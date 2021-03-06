#pragma once

#include <cstdint>

struct vec3f
{
    float x, y, z;

    vec3f(float p_x, float p_y, float p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec4f
{
    float x, y, z, w;

    vec4f(float p_x, float p_y, float p_z, float p_w)
    : x(p_x), y(p_y), z(p_z), w(p_w) {}
};

struct vec2f
{
    float x, y;

    vec2f(float p_x, float p_y)
    : x(p_x), y(p_y) {}
};

struct vec3i
{
    int x, y, z;

    vec3i(int p_x, int p_y, int p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec2i
{
    int x, y;

    vec2i(int p_x, int p_y)
    : x(p_x), y(p_y) {}
};

struct vec3u
{
    uint32_t x, y, z;

    vec3u(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec2u
{
    uint32_t x, y;

    vec2u(uint32_t p_x, uint32_t p_y)
    : x(p_x), y(p_y) {}
};

struct vec2b
{
    uint8_t x, y;

    vec2b(uint8_t p_x, uint8_t p_y)
    : x(p_x), y(p_y) {}
};

struct vec4b
{
    uint8_t x, y, z, w;

    vec4b(uint8_t p_x, uint8_t p_y, uint8_t p_z, uint8_t p_w)
    : x(p_x), y(p_y), z(p_z), w(p_w) {}
};

template<typename T>
struct vec2
{
    T x, y;

    vec2(T p_x, T p_y)
    : x(p_x), y(p_y) {}
};

template<typename T>
struct vec3
{
    T x, y;

    vec3(T p_x, T p_y)
    : x(p_x), y(p_y) {}
};

struct Vertex {
    vec3f Pos;
    vec2f TexCoord;
    vec3f Normal;

    Vertex(vec3f p_pos, vec2f p_texCoord, vec3f p_normal)
    : Pos(p_pos), TexCoord(p_texCoord), Normal(p_normal) {}
};
