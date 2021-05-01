#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Texture
{
private:
    uint32_t texture_ID;
    uint8_t* localBuffer;
    const char* filepath;
    int width, height, bitsPerPixel;

public:
    Texture(const char* filepath);
    ~Texture();

public:
    int GetWidth() const;
    int GetHeight() const;
    int GetBitsPerPixel() const;
 
public:
    void Bind(uint32_t slot = 0) const;
    void UnBind() const;
};

#endif