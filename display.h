#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <cstdint>

class TDisplay
{
public:
    virtual void init() = 0; 
    virtual void draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) = 0;
    virtual void update() = 0;
    virtual void deinit() = 0;
};

#endif
