#include "Core/Texture.h"

Texture::Texture(const char* filepath)
    :texture_ID(0), localBuffer(nullptr), filepath(nullptr), width(0), height(0), bitsPerPixel(0)
{
    SDL_Surface* data = IMG_Load(filepath);
    
    if(!data)
    {
        std::cerr << "Failed to open texture file" << '\n';
        return;
    }

    this->localBuffer = new uint8_t[data->h * data->pitch];
    memcpy(this->localBuffer, (uint8_t*)data->pixels, data->h * data->pitch);
    
    this->filepath = filepath;
    this->width = data->w;
    this->height = data->h;
    this->bitsPerPixel = data->format->BitsPerPixel;

    int mode = data->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;
    
    //Create a texture buffer in the vram to store the texture
    glGenTextures(1, &this->texture_ID);
    glBindTexture(GL_TEXTURE_2D, this->texture_ID);

    //The wrapping mode when the texture coordinates are bigger than the range
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //The filtering mode when resizing the texture to match the texture coordinates
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Insert the pixel data into the texture buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, mode, GL_UNSIGNED_BYTE, this->localBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(data);
}
Texture::~Texture()
{
    glDeleteTextures(1, &this->texture_ID);
}

int Texture::GetWidth() const
{
    return this->width;
}
int Texture::GetHeight() const
{
    return this->height;
}
int Texture::GetBitsPerPixel() const
{
    return this->bitsPerPixel;
}

void Texture::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->texture_ID);
}
void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

